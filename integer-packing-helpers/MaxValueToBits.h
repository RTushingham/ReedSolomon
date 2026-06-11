#include "elementary-mathematical-functions/DiscreteLog.h"

constexpr unsigned max_value_to_bits( unsigned max_value )
{
    return discrete_log_ceiling( max_value, 2 );
}
