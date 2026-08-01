#pragma once

#include "IErrorDecoderSchema.h"

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields/PolynomialsOverFieldAlgorithms.h"
#include "finite-fields-extensions/GaussianElimination.h"
#include "reed-solomon-codes/Codeword.h"
#include "reed-solomon-codes/ReedSolomonBlockCodeParameters.h"
#include "reed-solomon-codes/Schema.h"

#include <algorithm>
#include <optional>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class BerlekampWelchSchema : public IErrorDecoderSchema<BerlekampWelchSchema<n,k,Prime,Exponent>, n,k,Prime,Exponent>
{
    constexpr static std::size_t e{ GetReedSolomonParameters(n,k).e };

	Schema<n,k,Prime,Exponent> schema;

	struct LayoutLengths
	{
		const std::size_t e_coeff_count{};
		const std::size_t blank_entry_count{};
		const std::size_t q_coeff_count{};
		const std::size_t const_count{};

		LayoutLengths( std::size_t error_count_estimate )
			: e_coeff_count{ error_count_estimate }
			, blank_entry_count{ 2*( e - error_count_estimate ) }
			, q_coeff_count{ error_count_estimate + k }
			, const_count{ 1 }
		{}
	};
	struct Layout
	{
		std::size_t q_first_index{};
		std::size_t q_boundary_index{};
		std::size_t e_first_index{};
		std::size_t e_boundary_index{};
		std::size_t blank_first_index{};
		std::size_t blank_boundary_index{};
		std::size_t const_index{};

		Layout( LayoutLengths& lengths )
			: q_first_index{ 0 }
			, q_boundary_index{ q_first_index + lengths.q_coeff_count }
			, e_first_index{ q_boundary_index }
			, e_boundary_index{ e_first_index + lengths.e_coeff_count }
			, blank_first_index{ e_boundary_index }
			, blank_boundary_index{ blank_first_index + lengths.blank_entry_count }
			, const_index{ blank_boundary_index }
		{}
	};
	// layout = e0, e1, ..., e(e-1), q0, ..., q(e+k-1), "const"
	//   ->
	// layout = q0, ..., q(e+k-1), e0, ..., e(e-1), "const"

	//   In particular as e=0 in this case:
	// layout = q0, ..., q(k-1), 0, ..., 0, 0, ..., 0, "const"


public:
    constexpr BerlekampWelchSchema( const Schema<n, k, Prime, Exponent>& defining_schema )
        : schema{ defining_schema }
    {}

    std::optional<PolynomialOverFiniteField<Prime, Exponent, k-1>> Decode( const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
    {
        ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>> matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

        for( std::size_t error_count_estimate{ e }; error_count_estimate != (std::size_t)-1; error_count_estimate-- )
        {
			const Layout indexes{ LayoutLengths{ error_count_estimate } };

            // 1.
            SetMatrixWithStartParameters( matrix, indexes, recieved_signal );

            // 2.
            const auto rows_for_leading_non_zeros{ GaussianElimination( matrix ) };

            // 3.
            // check is solved
            if( !SSEHasAtLeastOneSolution( matrix, indexes, rows_for_leading_non_zeros ) )
                continue;
            if( !SSEHasExpectedNumberOfSolvedRows( matrix, error_count_estimate, rows_for_leading_non_zeros ) )
                continue;

            // 4.
            const auto polys{ GetPolynomialsFromMatrix( matrix, indexes, rows_for_leading_non_zeros ) };

            // 5.
            // check is divisible
            auto longDivisionRes{ LongDivideBy( polys.generator, polys.error_polynomial ) };

			static_assert( e > 0, "As polynomial lengths are template parameters we restrict our use cases to well defined ones." );
            if( longDivisionRes.remainder.IsZero() )
            {
                return longDivisionRes.quotient.Downsize<k-1>();
            }
        }

        return std::nullopt;
    }

    void SetMatrixWithStartParameters( ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>& matrix, const Layout& indexes, const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
	{
		for( std::size_t row_index{ 0 }; row_index<matrix.RowCount(); row_index++ )
		{
			const auto& a{ schema.generating_elements.at( row_index ) };
			auto& row{ matrix.Row( row_index ) };


			// q entries

			auto running_product{ ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient() };
			for( std::size_t q_index{ indexes.q_first_index }; q_index < indexes.q_boundary_index; q_index++ )
			{
				row.at( q_index ) = running_product;
				running_product = running_product * a;
			}

			// blank entries

			for( std::size_t blank_index{ indexes.blank_first_index }; blank_index < indexes.blank_boundary_index; blank_index++ )
			{
				row.at( blank_index ) = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient();
			}
			
			// e entries

			running_product = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() - ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient();
			running_product = running_product * recieved_signal.at( row_index );
			for( std::size_t e_index{ indexes.e_first_index }; e_index < indexes.e_boundary_index; e_index++ )
			{
				row.at( e_index ) = running_product;
				running_product = running_product * a;
			}
			
			// const entry

			row.at( indexes.const_index ) = running_product;
		}
	}

    
    struct PolynomialDeductionResult
    {
        PolynomialOverFiniteField<Prime, Exponent, k-1 + e> generator{};
        PolynomialOverFiniteField<Prime, Exponent, e> error_polynomial{};
    };

	PolynomialDeductionResult GetPolynomialsFromMatrix( ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>& matrix, const Layout& indexes, const std::array<std::size_t, n>& res ) const
	{
		const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

		PolynomialDeductionResult result{};

		//   In the solved case for each row we have:
		// a*q0 + "const" = 0
		// c*q1 + "const" = 0
		//   ...

		// a*q0 + "const" = 0
		//   =>
		// q0 = (0-"const")/a

		std::size_t row_index{ 0 };

		for( std::size_t q_index{ indexes.q_first_index }; q_index < indexes.q_boundary_index; q_index++ )
		{
			const std::size_t coeff_index{ q_index - indexes.q_first_index };
			result.generator.SetCoeff( 
				( 
					zero
					 - matrix.Row( res.at(row_index) ).at( indexes.const_index ) 
				) 
				/ matrix.Row( res.at(row_index) ).at( q_index ),
				coeff_index );
			
			row_index++;
		}

		std::size_t e_coeff_index{ 0 };
		for( std::size_t e_index{ indexes.e_first_index }; e_index < indexes.e_boundary_index; e_index++ )
		{
			result.error_polynomial.SetCoeff(
				( 
					zero
					 - matrix.Row( res.at(row_index) ).at( indexes.const_index ) 
				)
				/ matrix.Row( res.at(row_index) ).at( e_index ),
				e_coeff_index );

			row_index++;
			e_coeff_index++;
		}

		result.error_polynomial.SetCoeff( ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient(), e_coeff_index );

		return result;
	}


	bool SSEHasExpectedNumberOfSolvedRows( const ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>& matrix, std::size_t assumed_error_value, const std::array<std::size_t, n>& rows_for_leading_non_zeros ) const
	{
		const auto all_zero_row_count{ std::count( rows_for_leading_non_zeros.begin(), rows_for_leading_non_zeros.end(), (std::size_t)-1 ) };

		return all_zero_row_count == 2*(e - assumed_error_value);
	}
    
	bool SSEHasAtLeastOneSolution( const ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>& matrix, const Layout& indexes, const std::array<std::size_t, n>& rows_for_leading_non_zeros ) const
	{
		for( std::size_t row_index{ 0 }; row_index<rows_for_leading_non_zeros.size(); row_index++ )
		{
			if( false == array_contains( rows_for_leading_non_zeros, row_index ) )
			{
				if( matrix.Row( row_index ).at( indexes.const_index ) != ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() )
				{
					// no possible solution
					return false;
				}
			}
		}

		return true;
	}
};
