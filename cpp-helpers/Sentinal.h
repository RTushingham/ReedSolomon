#pragma once

// This adds another 3 ish seconds to whole program
template<typename ValueType, typename StorageType, StorageType sentinalValue>
class Sentinal
{
    ValueType m_value;

public:
    inline constexpr Sentinal( const ValueType& input ) noexcept
        : m_value{ input }
    {}
    inline constexpr Sentinal() noexcept
        : m_value{ ValueType{ sentinalValue } }
    {}

    inline constexpr bool has_value() const noexcept
    {
        constexpr ValueType checkValue{ sentinalValue };
        return m_value != checkValue;
    }

    inline constexpr ValueType value() const noexcept
    {
        return m_value;
    }
};

template<typename ValueType>
class DefaultSentinal
{
    ValueType m_value;

public:
    inline constexpr DefaultSentinal( const ValueType& input ) noexcept
        : m_value{ input }
    {}
    inline constexpr DefaultSentinal() noexcept
        : m_value{ ValueType{} }
    {}

    inline constexpr bool has_value() const noexcept
    {
        constexpr ValueType checkValue{};
        return m_value != checkValue;
    }

    inline constexpr ValueType value() const noexcept
    {
        return m_value;
    }
};

