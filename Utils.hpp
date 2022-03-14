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

    
    template <typename iter>
	using iter_category_t = typename std::iterator_traits<iter>::iterator_category;

	template <typename iter, typename category = std::input_iterator_tag>
	constexpr inline bool is_iterator_v = std::is_convertible_v<iter_category_t<std::decay_t<iter>>, category>;

    template<typename T>
    using Difference_iterator_t = typename std::iterator_traits<T>::difference_type;

    template<typename T, typename ... Args>
    constexpr inline bool is_all_convertible_v = (std::is_convertible_v<T, Args> && ...);
}