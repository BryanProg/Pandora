#pragma once

#include <type_traits>

#define POW2(X) ((X) * (X))

namespace Pandora
{
    namespace Utils
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

        template<typename T>
        constexpr bool is_fp_v = std::is_same_v<std::decay_t<T>, float>       || 
                                std::is_same_v<std::decay_t<T>, double>      ||
                                std::is_same_v<std::decay_t<T>, long double>;
        
        template <typename iter>
        using iter_category_t = typename std::iterator_traits<iter>::iterator_category;

        template <typename iter, typename category = std::input_iterator_tag>
        constexpr inline bool is_iterator_v = std::is_convertible_v<iter_category_t<std::decay_t<iter>>, category>;

        template <typename T>
        using Difference_iterator_t = typename std::iterator_traits<T>::difference_type;

        template <typename T, typename ... Args>
        constexpr inline bool is_all_convertible_v = (std::is_convertible_v<T, Args> && ...);

        template <std::size_t V, std::size_t W>
        constexpr inline bool is_R2_v = (V == 2u && W == 2u) ? true : false;

        template <std::size_t V, std::size_t W>
        constexpr inline bool is_R3_v = (V == 3u && W == 3u) ? true : false;

        template <std::size_t N, ::size_t V, std::size_t W>
        constexpr inline bool is_RN_v = (V == N && W == N) ? true : false;

        /* template <std::size_t, std::size_t, size_t>
        static inline bool is_equal */

        template<typename T>
        struct sqrt
        {
            static_assert(!std::is_reference_v<T>, "[ERROR] Type \"T\" can't be reference\n");
            static_assert(!std::is_pointer_v<T>, "[ERROR] Type \"T\" can't be pointer\n");
            static_assert(is_fp_v<T>, "[ERROR] Type \"T\" need a floating point\n");

            constexpr inline T operator() (T val)
            {
                return std::sqrt(val);
            }
            
            /*constexpr inline T&& inverse (T&& val) const
            {
                return std::forward<T>(std::sqrt(val));
            }*/
        };
    }
}