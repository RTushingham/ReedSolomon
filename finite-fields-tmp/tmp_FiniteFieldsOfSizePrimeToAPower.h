#pragma once

#include "finite-fields/FiniteFieldsOfSizePrimeToAPower.h"

#include "cpp-helpers/Typedef.h"

#include <type_traits>

template<typename E, size_t MaxDegree, size_t Exponent>
class ElementOfFiniteField_Poly_Expression
{
public:
	//
	// // // "Virtual":
	//

    static constexpr bool Is_Leaf = false;

	constexpr ElementOfFiniteField<2,Exponent> GetCoeff( std::size_t index ) const
	{
		// TODO:
		//   - Check, if this isn't here and the parent class does not have this method, will this fail to compile?
		return static_cast<E const&>( *this ).GetCoeff( index );
	}

	//
	// // // "Concrete":
	//

	constexpr DefaultSentinal<ElementOfFiniteField<2,Exponent>> Coeff_Safe( Sentinal<size_t, size_t, (size_t)-1> degree ) const
	{
		if( degree.has_value() )
		{
			return { GetCoeff( degree.value() )};
		}
		
		return { DefaultSentinal<ElementOfFiniteField<2,Exponent>>{} };
	}

	static constexpr size_t GetCoeffCount()
	{
		return MaxDegree+1;
	}
	static constexpr size_t GetMaxDegree()
	{
		return MaxDegree;
	}

	constexpr ElementOfFiniteField<2,Exponent> operator()( const ElementOfFiniteField<2,Exponent>& eval_point ) const
	{
		auto running_result = GetCoeff( MaxDegree );

		for( size_t coeff_index = MaxDegree-1; coeff_index != (size_t)-1; coeff_index-- )
		{
			running_result = ( running_result * eval_point ) + GetCoeff( coeff_index );
		}

		return running_result;
	}
};

template<size_t NewMaxDegree, typename Left, size_t Exponent>
class ElementOfFiniteField_Poly_PassThrough : public ElementOfFiniteField_Poly_Expression<ElementOfFiniteField_Poly_PassThrough<NewMaxDegree,Left,Exponent>, NewMaxDegree, Exponent>
{
	typename std::conditional<Left::Is_Leaf, const Left&, const Left>::type lhs;

public:
	//
	// // // "Interface":
	//
    static constexpr bool Is_Leaf = false;

	constexpr ElementOfFiniteField<2,Exponent> GetCoeff( std::size_t index ) const
	{
		return lhs.GetCoeff( index );
	}

	//
	// // // Constructors:
	//

	constexpr ElementOfFiniteField_Poly_PassThrough( const Left& lhs )
		: lhs{ lhs }
	{}
};

template<size_t MaxDegree, size_t Exponent>
class ElementOfFiniteField_Poly : public ElementOfFiniteField_Poly_Expression<ElementOfFiniteField_Poly<MaxDegree, Exponent>, MaxDegree, Exponent>
{
	static constexpr size_t GetCoeffCount()
	{
		return MaxDegree+1;
	}

	std::array<ElementOfFiniteField<2,Exponent>, GetCoeffCount()> values;

public:
	//
	// // // "Interface":
	//
    static constexpr bool Is_Leaf = true;

	constexpr ElementOfFiniteField<2,Exponent> GetCoeff( std::size_t index ) const
	{
		return values.at( index );
	}
	
	//
	// // // Constructors:
	//

	constexpr ElementOfFiniteField_Poly( std::array<ElementOfFiniteField<2,Exponent>, GetCoeffCount()> Input )
		: values{ Input }
	{}

	constexpr ElementOfFiniteField_Poly()
		: values{}
	{}

	template<typename E>
	constexpr ElementOfFiniteField_Poly( const ElementOfFiniteField_Poly_Expression<E,MaxDegree,Exponent>& Input )
		: values{}
	{
		for( size_t coeff_index{ 0 }; coeff_index < GetCoeffCount(); coeff_index++ )
		{
			values.at( coeff_index ) = Input.GetCoeff( coeff_index );
		}
	}

	//
	// // // "Non-Interface":
	//

	constexpr void SetCoeff( const ElementOfFiniteField<2,Exponent>& value, std::size_t index )
	{
		values.at( index ) = value;
	}

	constexpr Sentinal<size_t, size_t, (size_t)-1> tmp_GetDegree() const
	{
		for( size_t reverse_index = 0; reverse_index < GetCoeffCount(); reverse_index++ )
		{
			if( ! GetCoeff( GetMaxDegree() - reverse_index ).IsZero() )
			{
				return (GetMaxDegree() - reverse_index);
			}
		}
		
		return (size_t)-1;
	}
	constexpr integer GetDegree() const
	{
		for( size_t reverse_index = 0; reverse_index < GetCoeffCount(); reverse_index++ )
		{
			if( ! GetCoeff( GetMaxDegree() - reverse_index ).IsZero() )
			{
				return (integer)(GetMaxDegree() - reverse_index);
			}
		}
		
		return -1;
	}
	
	constexpr bool operator==( const ElementOfFiniteField_Poly<MaxDegree, Exponent>& rhs ) const
	{
		return values == rhs.values;
	}
	constexpr bool operator!=(const ElementOfFiniteField_Poly<MaxDegree, Exponent>& a) const
	{
		return ! operator==(a);
	}

	constexpr static ElementOfFiniteField_Poly<MaxDegree, Exponent> GetAdditionInvarient()
	{
		return ElementOfFiniteField_Poly<MaxDegree, Exponent>{ std::array<ElementOfFiniteField<2,Exponent>, GetCoeffCount()>{ ElementOfFiniteField<2,Exponent>::GetAdditionInvarient() } };
	}
	constexpr bool IsZero() const
	{
		for( const auto& coef : values )
		{
			if( !coef.IsZero() )
			{
				return false;
			}
		}
		return true;
	}
	constexpr static ElementOfFiniteField_Poly<MaxDegree, Exponent> GetMultiplicativeInvarient()
	{
		auto addition_invarient = GetAdditionInvarient();
		addition_invarient.SetCoeff( ElementOfFiniteField<2,Exponent>::GetMultiplicativeInvarient(), 0 );
		return addition_invarient;
	}
	constexpr bool IsOne() const
	{
		if( ! GetCoeff( 0 ).IsOne() )
		{
			return false;
		}
		for( std::size_t index{ 1 }; index < GetCoeffCount(); index++ )
		{
			if( ! GetCoeff( index ).IsZero() )
			{
				return false;
			}
		}
		return true;
	}
	template<integer SmallerDegree>
	constexpr ElementOfFiniteField_Poly_PassThrough<SmallerDegree, ElementOfFiniteField_Poly<MaxDegree, Exponent>, Exponent> Downsize() const
	{
		static_assert( SmallerDegree <= GetMaxDegree() , "Downsize cannot increase the size of a polynomial." );
		
		return *this;
	}
	template<integer LargerDegree>
	constexpr ElementOfFiniteField_Poly<LargerDegree, Exponent> Oversize() const
	{
		static_assert( LargerDegree >= MaxDegree, "Oversize cannot decrease the size of a polynomial." );
	
		ElementOfFiniteField_Poly<LargerDegree, Exponent> oversized{};
	
		for( size_t coefficient_index{ 0 }; coefficient_index < GetCoeffCount(); coefficient_index++ )
		{
			oversized.SetCoeff( GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return oversized;
	}
	template<integer OtherDegree>
	constexpr ElementOfFiniteField_Poly<OtherDegree, Exponent> ToSize() const
	{
		ElementOfFiniteField_Poly<OtherDegree, Exponent> output{};
	
		// const size_t a{ GetCoeffCount() > output.GetCoeffCount() ? output.GetCoeffCount() : GetCoeffCount() };
		const size_t outputCoeffCount{ OtherDegree+1 };
		const size_t a{ GetCoeffCount() > outputCoeffCount ? outputCoeffCount : GetCoeffCount() };
	
		for( size_t coefficient_index{ 0 }; coefficient_index < a; coefficient_index++ )
		{
			output.SetCoeff( GetCoeff( coefficient_index ), coefficient_index );
		}
		
		return output;
	}
	template<>
	constexpr ElementOfFiniteField_Poly<MaxDegree, Exponent> ToSize() const
	{
		return *this;
	}
};


template<size_t MaxDegree, typename Left, typename Right, size_t Exponent>
class ElementOfFiniteField_Poly_Sum : public ElementOfFiniteField_Poly_Expression<ElementOfFiniteField_Poly_Sum<MaxDegree,Left,Right,Exponent>, MaxDegree, Exponent>
{
	typename std::conditional<Left::Is_Leaf, const Left&, const Left>::type lhs;
    typename std::conditional<Right::Is_Leaf, const Right&, const Right>::type rhs;

public:
	//
	// // // "Interface":
	//
    static constexpr bool Is_Leaf = false;

	constexpr ElementOfFiniteField<2,Exponent> GetCoeff( std::size_t index ) const
	{
		return lhs.GetCoeff( index ) + rhs.GetCoeff( index );
	}

	//
	// // // Constructors:
	//

	constexpr ElementOfFiniteField_Poly_Sum( const Left& lhs, const Right& rhs )
		: lhs{ lhs }
		, rhs{ rhs }
	{}
};

template<size_t MaxDegree, typename Left, typename Right, size_t Exponent>
constexpr ElementOfFiniteField_Poly_Sum<MaxDegree, Left, Right, Exponent> operator+( const ElementOfFiniteField_Poly_Expression<Left, MaxDegree, Exponent>& lhs, const ElementOfFiniteField_Poly_Expression<Right, MaxDegree, Exponent>& rhs )
{
	return ElementOfFiniteField_Poly_Sum<MaxDegree, Left, Right, Exponent>( *static_cast<const Left*>(&lhs), *static_cast<const Right*>(&rhs) );
}

template<size_t MaxDegree, typename Left, typename Right, size_t Exponent>
constexpr ElementOfFiniteField_Poly_Sum<MaxDegree, Left, Right, Exponent> operator-( const ElementOfFiniteField_Poly_Expression<Left, MaxDegree, Exponent>& lhs, const ElementOfFiniteField_Poly_Expression<Right, MaxDegree, Exponent>& rhs )
{
	return ElementOfFiniteField_Poly_Sum<MaxDegree, Left, Right, Exponent>( *static_cast<const Left*>(&lhs), *static_cast<const Right*>(&rhs) );
}


template<size_t MaxDegree, typename Left, size_t Exponent>
class ElementOfFiniteField_Poly_ScalarMul : public ElementOfFiniteField_Poly_Expression<ElementOfFiniteField_Poly_ScalarMul<MaxDegree,Left,Exponent>, MaxDegree, Exponent>
{
	typename std::conditional<Left::Is_Leaf, const Left&, const Left>::type lhs;
    ElementOfFiniteField<2,Exponent> scalar;

public:
	//
	// // // "Interface":
	//
    static constexpr bool Is_Leaf = false;

	constexpr ElementOfFiniteField<2,Exponent> GetCoeff( std::size_t index ) const
	{
		return lhs.GetCoeff( index ) * scalar;
	}

	//
	// // // Constructors:
	//

	constexpr ElementOfFiniteField_Poly_ScalarMul( const Left& lhs, ElementOfFiniteField<2,Exponent> scalar )
		: lhs{ lhs }
		, scalar{ scalar }
	{}
};

template<size_t MaxDegree, typename Left, size_t Exponent>
constexpr ElementOfFiniteField_Poly_ScalarMul<MaxDegree, Left, Exponent> ScalarMultiplication( const ElementOfFiniteField_Poly_Expression<Left, MaxDegree, Exponent>& lhs, ElementOfFiniteField<2,Exponent> rhs )
{
	return ElementOfFiniteField_Poly_ScalarMul<MaxDegree, Left, Exponent>( *static_cast<const Left*>(&lhs), rhs );
}


template<size_t MaxDegree, typename Left, typename Right, size_t Exponent>
constexpr ElementOfFiniteField_Poly<MaxDegree, Exponent> MultiplyUpToSameDegree( const ElementOfFiniteField_Poly_Expression<Left, MaxDegree, Exponent>& lhs, const ElementOfFiniteField_Poly_Expression<Right, MaxDegree, Exponent>& rhs )
{
	auto return_value{ ElementOfFiniteField_Poly<MaxDegree, Exponent>::GetAdditionInvarient() };
	
	for( size_t rhs_index{ 0 }; rhs_index < rhs.GetCoeffCount(); rhs_index++ )
	{
		for( size_t lhs_index{ 0 }; lhs_index < lhs.GetCoeffCount() - rhs_index; lhs_index++ )
		{
			return_value.SetCoeff( return_value.GetCoeff( rhs_index + lhs_index ) + ( rhs.GetCoeff( rhs_index ) * lhs.GetCoeff( lhs_index ) ), rhs_index + lhs_index );
		}
	}

	return return_value;
}
template<size_t MaxDegree, typename Left, typename Right, size_t Exponent>
constexpr ElementOfFiniteField_Poly<MaxDegree-1, Exponent> MultiplicationExcessTerms( const ElementOfFiniteField_Poly_Expression<Left, MaxDegree, Exponent>& lhs, const ElementOfFiniteField_Poly_Expression<Right, MaxDegree, Exponent>& rhs )
{
	auto return_value{ ElementOfFiniteField_Poly<MaxDegree-1, Exponent>::GetAdditionInvarient() };
	
	for( size_t rhs_index{ 1 }; rhs_index < rhs.GetCoeffCount(); rhs_index++ )
	{
		for( size_t lhs_index{ lhs.GetCoeffCount() - rhs_index }; lhs_index < lhs.GetCoeffCount(); lhs_index++ )
		{
			return_value.SetCoeff( return_value.GetCoeff( rhs_index + lhs_index - GetCoeffCount() ) + ( rhs.GetCoeff( rhs_index ) * lhs.GetCoeff( lhs_index ) ), rhs_index + lhs_index - GetCoeffCount() );
		}
	}

	return return_value;
}

template<size_t MaxDegree, size_t OtherMaxDegree, typename Left, typename Right, size_t Exponent>
constexpr ElementOfFiniteField_Poly<MaxDegree+OtherMaxDegree, Exponent> operator*( const ElementOfFiniteField_Poly_Expression<Left, MaxDegree, Exponent>& lhs, const ElementOfFiniteField_Poly_Expression<Right, OtherMaxDegree, Exponent>& rhs )
{
	auto return_value{ ElementOfFiniteField_Poly<MaxDegree+OtherMaxDegree, Exponent>::GetAdditionInvarient() };
		
	for( size_t rhs_index = 0; rhs_index < rhs.GetCoeffCount(); rhs_index++ )
	{
		for( size_t lhs_index = 0; lhs_index < lhs.GetCoeffCount(); lhs_index++ )
		{
			return_value.SetCoeff( return_value.GetCoeff( rhs_index + lhs_index ) + ( rhs.GetCoeff( rhs_index ) * lhs.GetCoeff( lhs_index ) ), rhs_index + lhs_index );
		}
	}
	
	return return_value;
}

