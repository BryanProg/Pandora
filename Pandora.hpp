#pragma once

#include <iostream>
#include <cstdint>
#include <cmath>
#include <array>
#include <initializer_list>
#include <cassert>
#include <type_traits>
#include "Utils.hpp"

namespace Pandora
{
    namespace Vec
    {
        template<std::size_t N, typename T>
        class vec;

        template<std::size_t Sz, typename U>
        constexpr inline bool operator== (const vec<Sz, U>&, const vec<Sz, U>&);

        template<std::size_t Sz, typename U>
        constexpr inline bool operator!= (const vec<Sz, U>&, const vec<Sz, U>&);

        template<std::size_t Sz, typename U>
        constexpr inline vec<Sz, U>& operator+ (vec<Sz, U>&, const vec<Sz, U>&);

        template<std::size_t Sz, typename U>
        constexpr inline vec<Sz, U>&& operator+ (vec<Sz, U>&&, const vec<Sz, U>&);

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

            template<std::size_t, typename> friend class vec;

            // Relational operators Friends
            friend constexpr bool operator== <N, T> (const vec<N, T>&, const vec<N, T>&);
            friend constexpr bool operator!= <N, T> (const vec<N, T>&, const vec<N, T>&);

            // Binary Operators Friends
            friend constexpr vec& operator+ <N, T> (vec&, const vec&);
            friend constexpr vec&& operator+ <N, T> (vec&&, const vec&);

            public:
                using value_type      = std::decay_t<T>;
                using size_type       = std::size_t;
                using reference       = value_type&;
                using const_reference = value_type const&;
                using pointer         = value_type*;
                using const_pointer   = const value_type*;
                using iterator        = typename std::array<T, N>::iterator;
                using const_iterator  = typename std::array<T, N>::const_iterator;
                using difference_type = typename std::iterator_traits<iterator>::difference_type;
            
            public:
                constexpr vec() = default;

                constexpr vec(const vec&) = default;
                constexpr vec(vec&&)      = default;

                constexpr vec& operator= (const vec&) = default;
                constexpr vec& operator= (vec&&)      = default;

                /*
                constexpr vec(std::initializer_list<T> list_arg)
                    : components{ }
                {
                    assert(list_arg.size() == N);
                    
                    for(auto sz{ 0ULL }; sz < N; ++sz)
                        components[sz] = *(list_arg.begin() + sz);
                }*/

                //to do(Bryan): Implement to initialize with up to 0 <element <= n
                // Taking restriction contains have the same size, ie being less than or equal.
                template<typename iter,
                         typename = std::enable_if_t<!std::is_same_v<iter, value_type>>,// The iterator should be different
                         typename = std::enable_if_t<is_iterator_v<iter, std::forward_iterator_tag>>>
                explicit constexpr vec(iter b, iter e)
                    : components{}
                {

                    Difference_iterator_t<iter> diff_it = std::distance(b, e);

                    assert(diff_it == N);
                    
                    for(decltype(diff_it) idx{}; idx < diff_it; ++idx)
                        components[idx] = *(b + idx);
                }

                explicit constexpr vec(const std::array<T, N>& arr)
                    : components{ arr }
                {
                }

                explicit constexpr vec(std::array<T, N>&& arr)
                    : components{ std::move(arr) }
                {
                }

                template<std::size_t Sz, typename U,
                         typename = std::enable_if_t<N == Sz>,
                         typename = std::enable_if_t<std::is_convertible_v<U, T>>>
                constexpr vec(const vec<Sz, U>& cont)
                    : components {}
                {
                    for(std::size_t idx{}; idx < N; ++idx)
                        components[idx] = cont.components[idx]; 
                }

                template<std::size_t Sz, typename U,
                         typename = std::enable_if_t<N == Sz>,
                         typename = std::enable_if_t<std::is_convertible_v<U, T>>>
                constexpr vec(const vec<Sz, U>&& cont)
                    : components {}
                {
                    for(std::size_t idx{}; idx < N; ++idx)
                        components[idx] = std::move(cont.components[idx]); 
                }

                template<typename ... Args,
                         typename = std::enable_if_t<sizeof...(Args) == N>,
                         typename = std::enable_if_t<is_all_convertible_v<T, Args...>>>
                constexpr vec(Args&&... args)
                    : components{ std::forward<T>(static_cast<T>(args))... }
                {
                }
                
                constexpr iterator begin() {return components.begin();}
                constexpr iterator end()   {return components.end();}

                constexpr const_iterator begin() const { return components.cbegin();}
                constexpr const_iterator end()   const { return components.cend();}

                template<std::size_t Sz, typename U, 
                         typename = std::enable_if_t<Sz == N>,
                         typename = std::enable_if_t<std::is_convertible_v<U, T>>>
                constexpr inline vec& operator+= (const vec<Sz, U>& obj);
            
                template<std::size_t Sz, typename U, 
                         typename = std::enable_if_t<Sz == N>,
                         typename = std::enable_if_t<std::is_convertible_v<U, T>>>
                constexpr inline vec& operator-= (const vec<Sz, U>& obj);

                template<typename = std::enable_if_t<is_fp_v<T> || is_uint_v<T> || is_int_v<T>>>
                constexpr inline vec& operator*= (const float);

                // operator []
            private:
                std::array<T, N> components;
        };

        // OPERATORS
        template<std::size_t N, typename T>
            template<std::size_t Sz, typename U, typename, typename>
        constexpr inline vec<N, T>& vec<N, T>::operator+= (const vec<Sz, U>& obj)
        {
            for(std::size_t count{}; count < N; ++count)
                this->components[count] += obj.components[count];
            
            return *this;
        }

        template<std::size_t N, typename T>
            template<std::size_t Sz, typename U, typename, typename>
        constexpr inline vec<N, T>& vec<N, T>::operator-= (const vec<Sz, U>& obj)
        {
            for(std::size_t count{}; count < N; ++count)
                this->components[count] -= obj.components[count];
            
            return *this;
        }

        template<std::size_t N, typename T>
            template<typename>
        constexpr inline vec<N, T>& vec<N, T>::operator*= (const float scl)
        {
            for (auto& elem : *this)
                elem *= scl;
            
            return *this;
        }

        // Functions friends
        template<std::size_t Sz, typename U>
        constexpr inline bool operator== (const vec<Sz, U>& lhs, const vec<Sz, U>& rhs)
        {
            for(std::size_t count{}; count < Sz; ++count)
                if (lhs.components[count] != rhs.components[count])
                    return false;
            
            return true;
        }

        template<std::size_t Sz, typename U>
        constexpr inline bool operator!= (const vec<Sz, U>& lhs, const vec<Sz, U>& rhs)
        {
            return !(lhs == rhs);
        }
    }
}