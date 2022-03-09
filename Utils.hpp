#pragma once

#include <type_traits>

namespace Pandora
{
    template<typename T>
    constexpr bool is_int_v = std::is_same_v<std::decay_t<T>, int8_t>  || 
                              std::is_same_v<std::decay_t<T>, int16_t> ||
                              std::is_same_v<std::decay_t<T>, int32_t> || 
                              std::is_same_v<std::decay_t<T>, int64_t>;
    
    template<typename T>
    constexpr bool is_uint_v = std::is_same_v<std::decay_t<T>, uint8_t>  || 
                               std::is_same_v<std::decay_t<T>, uint16_t> ||
                               std::is_same_v<std::decay_t<T>, uint32_t> ||
                               std::is_same_v<std::decay_t<T>, uint64_t>;
    
}