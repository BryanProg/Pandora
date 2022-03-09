#pragma once

#include <iostream>
#include <cstdint>
#include <cmath>
#include <type_traits>
#include "Utils.hpp"

namespace Pandora
{
    namespace Vector
    {
        template<std::size_t N, typename T>
        class vec;

        // Definitions
        namespace
        {
                                            /* # using templates # */

            // Settings for integers signed
            template<typename T>
            using vec1i = vec<1ULL, std::enable_if_t<is_int_v<T>, T>>;

            template<typename T>
            using vec2i = vec<2ULL, std::enable_if_t<is_int_v<T>, T>>;

            template<typename T>
            using vec3i = vec<3ULL, std::enable_if_t<is_int_v<T>, T>>;

            template<typename T>
            using vec4i = vec<4ULL, std::enable_if_t<is_int_v<T>, T>>;

            // Settings for integers unsigned
            template<typename T>
            using vec1u = vec<1ULL, std::enable_if_t<is_uint_v<T>, T>>;

            template<typename T>
            using vec2u = vec<2ULL, std::enable_if_t<is_uint_v<T>, T>>;

            template<typename T>
            using vec3u = vec<3ULL, std::enable_if_t<is_uint_v<T>, T>>;

            template<typename T>
            using vec4u = vec<4ULL, std::enable_if_t<is_uint_v<T>, T>>;


                                        /* # using no-templates # */

            // Settings for floating points
            using vec1fp = vec<1ULL, float>;
            using vec2fp = vec<2ULL, float>;
            using vec3fp = vec<3ULL, float>;
            using vec4fp = vec<4ULL, float>;

            // Settings for double floating points
            using vec1dp = vec<1ULL, double>;
            using vec2dp = vec<2ULL, double>;
            using vec3dp = vec<3ULL, double>;
            using vec4dp = vec<4ULL, double>;

            // Settings for long double floating points
            using vec1ldp = vec<1ULL, long double>;
            using vec2ldp = vec<2ULL, long double>;
            using vec3ldp = vec<3ULL, long double>;
            using vec4ldp = vec<4ULL, long double>;
        }

        template<std::size_t N, typename T>
        class vec
        {
            static_assert(!std::is_reference_v<T>, "[ERROR] Type \"T\" can't be reference\n");
            static_assert(!std::is_pointer_v<T>, "[ERROR] Type \"T\" can't be pointer\n");

            public:
                using value_type = std::decay_t<T>;

        };

    }
}