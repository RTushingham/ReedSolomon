#pragma once

#include "container-helpers/ArrayExtensions.h"
#include "finite-fields-extensions/GaussianElimination.h"
#include "reed-solomon-codes/Code.h"
#include "reed-solomon-codes/Codeword.h"

#include <algorithm>

template<std::size_t n, std::size_t k, integer Prime, integer Exponent>
class BerklekampWelchDecoder
{
private:
    const Code<n, k, Prime, Exponent> schema;
    constexpr static std::size_t e{ GetReedSolomonParameters(n,k).e };

	static_assert( GetReedSolomonParameters(n,k).d % 2 == 1, "Only decoders for guaranteed solutions are allowed" );

public:
    constexpr BerklekampWelchDecoder( const Code<n, k, Prime, Exponent>& defining_schema )
        : schema{ defining_schema }
    {}

    Codeword<n, k, Prime, Exponent> Decode( const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
    {
        ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>> matrix{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

        for( std::size_t error_count_estimate{ e }; error_count_estimate != 0; error_count_estimate-- )
        {
            // 1.
            SetMatrixWithStartParameters( matrix, error_count_estimate, recieved_signal );

            // 2.
            const auto rows_for_leading_non_zeros{ GaussianElimination( matrix ) };

            // 3.
            // check is solved
            if( !SSEHasAtLeastOneSolution( matrix, rows_for_leading_non_zeros ) )
                break;
            if( !SSEHasFiniteNumberOfSolutions( matrix, error_count_estimate, rows_for_leading_non_zeros ) )
                break;

            // 4.
            const auto polys{ GetPolynomialsFromMatrix( matrix, error_count_estimate, rows_for_leading_non_zeros ) };

            // 5.
            // check is divisible
            auto longDivisionRes{ polys.generator.LongDivideBy( polys.error_polynomial ) };

			static_assert( e > 0, "As polynomial lengths are template parameters we restrict our use cases to well defined ones." );
            if( longDivisionRes.remainder == PolynomialOverFiniteField<Prime,Exponent, e-1>::GetAdditionInvarient() )
            {
                return schema.GenerateCodeword( longDivisionRes.quotient );
            }
        }

        return recieved_signal;
    }

    void SetMatrixWithStartParameters( ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>& matrix, std::size_t assumed_error_value, const Codeword<n, k, Prime, Exponent>& recieved_signal ) const
	{
		// layout = e0, e1, ..., e(e-1), q0, ..., q(e+k-1), "const"
		//   ->
		// layout = q0, ..., q(e+k-1), e0, ..., e(e-1), "const"

		//   In particular as e=0 in this case:
		// layout = q0, ..., q(k-1), 0, ..., 0, 0, ..., 0, "const"

		for( std::size_t row_index{ 0 }; row_index<matrix.RowCount(); row_index++ )
		{
			const auto& a{ schema.generating_elements.at( row_index ) };
			auto& row{ matrix.Row( row_index ) };
			
			std::size_t coeff_count{ 0 };
			auto running_product{ ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient() };
			while( coeff_count <= k + assumed_error_value - 1 )
			{
				row.at( coeff_count ) = running_product;
				running_product = running_product * a;
				coeff_count++;
			}

			running_product = ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() - ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient();
			running_product = running_product * recieved_signal.blocks.at( row_index );

			coeff_count = e + k;
			// so that const is at end
			coeff_count += e - assumed_error_value;
			while( coeff_count <= e + k + e )
			{
				row.at( coeff_count ) = running_product;
				running_product = running_product * a;
				coeff_count++;
			}
		}
	}

    
    struct PolynomialDeductionResult
    {
        PolynomialOverFiniteField<Prime, Exponent, k-1 + e> generator{};
        PolynomialOverFiniteField<Prime, Exponent, e> error_polynomial{};
    };

	PolynomialDeductionResult GetPolynomialsFromMatrix( ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>& matrix, std::size_t error_value, const std::array<std::size_t, n>& res ) const
	{
		const auto zero{ ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() };

		PolynomialDeductionResult result{};
		// layout = e0, e1, ..., e(e-1), q0, ..., q(e+k-1), "const"
		//   ->
		// layout = q0, ..., q(e+k-1), e0, ..., e(e-1), "const"

		//   In particular as e=0 in this case:
		// layout = q0, ..., q(k-1), 0, ..., 0, 0, ..., 0, "const"

		//   In the solved case for each row we have:
		// a*q0 + "const" = 0
		// c*q1 + "const" = 0
		//   ...

		// a*q0 + "const" = 0
		//   =>
		// q0 = (0-"const")/a

		std::size_t coeff_count{ 0 };
		while( coeff_count <= k + error_value - 1 )
		{
			result.generator.Coeff( coeff_count ) = ( zero - matrix.Row( res.at(coeff_count) ).at( matrix.ColumnCount()-1 ) ) / matrix.Row( res.at(coeff_count) ).at( coeff_count );
			coeff_count++;
		}

		coeff_count = e + k;
		// so that const is at end
		coeff_count += e - error_value;
		std::size_t e_coeff_index{ 0 };
		while( coeff_count <= e + k - 1 + e )
		{
			result.error_polynomial.Coeff( e_coeff_index ) = ( zero - matrix.Row( res.at(coeff_count) ).at( matrix.ColumnCount()-1 ) ) / matrix.Row( res.at(coeff_count) ).at( coeff_count );
			coeff_count++;
			e_coeff_index++;
		}
		result.error_polynomial.Coeff( e_coeff_index ) = ElementOfFiniteField<Prime,Exponent>::GetMultiplicativeInvarient();

		return result;
	}


	bool SSEHasFiniteNumberOfSolutions( const ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>& matrix, std::size_t assumed_error_value, const std::array<std::size_t, n>& rows_for_leading_non_zeros ) const
	{
		const auto all_zero_row_count{ std::count( rows_for_leading_non_zeros.begin(), rows_for_leading_non_zeros.end(), (std::size_t)-1 ) };

		return all_zero_row_count == 2*(e - assumed_error_value);
	}
    
	bool SSEHasAtLeastOneSolution( const ElementaryMatrix<n, n+1, ElementOfFiniteField<Prime,Exponent>>& matrix, const std::array<std::size_t, n>& rows_for_leading_non_zeros ) const
	{
		for( std::size_t row_index{ 0 }; row_index<rows_for_leading_non_zeros.size(); row_index++ )
		{
			if( false == array_contains( rows_for_leading_non_zeros, row_index ) )
			{
				// wrong - you check this for all of the things no in here...
				if( matrix.Row( row_index ).at( matrix.ColumnCount()-1 ) != ElementOfFiniteField<Prime,Exponent>::GetAdditionInvarient() )
				{
					// no possible solution
					return false;
				}
			}
		}

		return true;
	}
};
