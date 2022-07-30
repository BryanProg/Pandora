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
        template <std::size_t N, typename T>
        class vec;

        template <std::size_t Sz, typename U>
        constexpr inline bool operator== (const vec<Sz, U>&, const vec<Sz, U>&);

        template <std::size_t Sz, typename U>
        constexpr inline bool operator!= (const vec<Sz, U>&, const vec<Sz, U>&);

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator+ (vec<Sz, U>, const vec<Sz, U>&);

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator- (vec<Sz, U>, const vec<Sz, U>&);

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator* (vec<Sz, U>, const float);

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator* (const float, vec<Sz, U>);

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator/ (vec<Sz, U>, const float);

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator/ (const float, vec<Sz, U>);

        template <std::size_t Sz, typename U>
        inline std::ostream& operator << (std::ostream&, const vec<Sz, U>);

        // Definitions
        namespace FastDefs
        {
                                            /* # using templates # */

            // Settings for integers signed
            template <typename T>
            using vec1i = vec<1ULL, std::enable_if_t<Utils::is_int_v<T>, T>>;

            template <typename T>
            using vec2i = vec<2ULL, std::enable_if_t<Utils::is_int_v<T>, T>>;

            template <typename T>
            using vec3i = vec<3ULL, std::enable_if_t<Utils::is_int_v<T>, T>>;

            template <typename T>
            using vec4i = vec<4ULL, std::enable_if_t<Utils::is_int_v<T>, T>>;

            // Settings for integers unsigned
            template <typename T>
            using vec1u = vec<1ULL, std::enable_if_t<Utils::is_uint_v<T>, T>>;

            template <typename T>
            using vec2u = vec<2ULL, std::enable_if_t<Utils::is_uint_v<T>, T>>;

            template <typename T>
            using vec3u = vec<3ULL, std::enable_if_t<Utils::is_uint_v<T>, T>>;

            template <typename T>
            using vec4u = vec<4ULL, std::enable_if_t<Utils::is_uint_v<T>, T>>;


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
            static_assert(!std::is_reference_v<T>, "[ERROR] Type \"T\" can't be reference");
            static_assert(!std::is_pointer_v<T>, "[ERROR] Type \"T\" can't be pointer");
            static_assert( N > 0ULL, "[ERROR] The component number needs to be greater than zero");

            template<std::size_t, typename> friend class vec;

            // Relational operators Friends
            friend constexpr bool operator== <N, T> (const vec<N, T>&, const vec<N, T>&);
            friend constexpr bool operator!= <N, T> (const vec<N, T>&, const vec<N, T>&);

            // Binary Operators Friends
            friend constexpr vec operator+ <N, T> (vec, const vec&);
            friend constexpr vec operator- <N, T> (vec, const vec&);
            friend constexpr vec operator* <N, T> (vec, const float);
            friend constexpr vec operator* <N, T> (const float, vec);
            friend constexpr vec operator/ <N, T> (vec, const float);
            friend constexpr vec operator/ <N, T> (const float, vec);

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
            
                //////////////////////////////////////////// Constructors /////////////////////////////////////////////

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

                constexpr vec()
                :   components{}
                {
                }
                //to do(Bryan): Implement to initialize with up to 0 <element <= n
                // Taking restriction contains have the same size, ie being less than or equal.
                template <typename iter,
                         typename = std::enable_if_t<!std::is_same_v<iter, value_type>>,// The iterator should be different
                         typename = std::enable_if_t<Utils::is_iterator_v<iter, std::forward_iterator_tag>>>
                explicit constexpr vec(iter b, iter e)
                    : components{}
                {

                   Utils:: Difference_iterator_t<iter> diff_it = std::distance(b, e);

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

                template <std::size_t Sz, typename U,
                         typename = std::enable_if_t<N == Sz>,
                         typename = std::enable_if_t<std::is_convertible_v<U, T>>>
                constexpr vec(const vec<Sz, U>& cont)
                    : components {}
                {
                    for(std::size_t idx{}; idx < N; ++idx)
                        components[idx] = cont.components[idx]; 
                }

                template <std::size_t Sz, typename U,
                         typename = std::enable_if_t<N == Sz>,
                         typename = std::enable_if_t<std::is_convertible_v<U, T>>>
                constexpr vec(const vec<Sz, U>&& cont)
                    : components {}
                {
                    for(std::size_t idx{}; idx < N; ++idx)
                        components[idx] = std::move(cont.components[idx]); 
                }

                template <typename ... Args,
                         typename = std::enable_if_t<sizeof...(Args) == N>,
                         typename = std::enable_if_t<Utils::is_all_convertible_v<T, Args...>>>
                constexpr vec(Args&&... args)
                    :components{ std::forward<T>(static_cast<T>(args))... } 
                {
                }
                
                //////////////////////////////////////// Functions in Class ///////////////////////////////////////////

                constexpr iterator begin() {return components.begin();}
                constexpr iterator end()   {return components.end();}

                constexpr const_iterator begin() const { return components.cbegin();}
                constexpr const_iterator end()   const { return components.cend();}

                //////////////////////////////////////// Functions Outside Class //////////////////////////////////////
                template <std::size_t Sz, typename U, 
                         typename = std::enable_if_t<Sz == N>,
                         typename = std::enable_if_t<std::is_convertible_v<U, T>>>
                constexpr inline vec& operator+= (const vec<Sz, U>& obj);
            
                template <std::size_t Sz, typename U, 
                         typename = std::enable_if_t<Sz == N>,
                         typename = std::enable_if_t<std::is_convertible_v<U, T>>>
                constexpr inline vec& operator-= (const vec<Sz, U>& obj);

                template <typename = std::enable_if_t<Utils::is_fp_v<T> || Utils::is_uint_v<T> || Utils::is_int_v<T>>>
                constexpr inline vec& operator*= (const float);

                template <typename = std::enable_if_t<std::is_convertible_v<T, float>>> 
                constexpr inline vec& operator /= (const float);

                constexpr inline T& operator[] (const std::size_t idx);
                constexpr inline const T& operator[] (const std::size_t idx) const;

            public:
                constexpr inline vec &negative();

                template <typename = std::enable_if_t<Utils::is_fp_v<T> || Utils::is_uint_v<T> || Utils::is_int_v<T>>>
                constexpr inline bool is_zero_vec() const;

                template <typename = std::enable_if_t<std::is_convertible_v<T, float>>>
                constexpr inline float magnitude() const;
              
                template <typename = std::enable_if_t<Utils::is_fp_v<T> || Utils::is_uint_v<T> || Utils::is_int_v<T>>,
                         typename = std::enable_if_t<(N > 0ULL)>>
                constexpr inline vec& normalize();

                template <typename = std::enable_if_t<Utils::is_fp_v<T> || Utils::is_uint_v<T> || Utils::is_int_v<T>>,
                         typename = std::enable_if_t<(N > 0ULL)>>
                constexpr inline vec copy_normalized() const;

                template <std::size_t Sz, typename U,
                          typename = std::enable_if_t<Sz == N>,
                          typename = std::enable_if_t<std::is_convertible_v<T, float>>,
                          typename = std::enable_if_t<std::is_convertible_v<U, float>>>
                constexpr inline float distance(const vec<Sz, U>&) const;

                template <std::size_t Sz, typename U,
                         typename = std::enable_if_t<Sz == N>,
                         typename = std::enable_if_t<std::is_convertible_v<T, float>>,
                         typename = std::enable_if_t<std::is_convertible_v<U, float>>>
                constexpr inline float dot(const vec<Sz, U>&) const;

                template <std::size_t Sz, typename U,
                          typename = std::enable_if_t<Sz == N>,
                          typename = std::enable_if_t<Utils::is_R2_v<N, Sz> || Utils::is_R3_v<N, Sz>>,
                          typename = std::enable_if_t<std::is_convertible_v<T, float>>,
                          typename = std::enable_if_t<std::is_constructible_v<U, float>>>
                constexpr inline float dot(const vec<Sz, U>&, float) const;

                template <std::size_t Sz, typename U,
                          typename = std::enable_if_t<Sz == N>,
                          typename = std::enable_if_t<Utils::is_R2_v<N, Sz> || Utils::is_R3_v<N, Sz>>,
                          typename = std::enable_if_t<std::is_convertible_v<T, float>>,
                          typename = std::enable_if_t<std::is_constructible_v<U, float>>>
                constexpr inline float angle_between(const vec<Sz, U>&, float) const;

                template <std::size_t Sz, typename U,
                          typename = std::enable_if_t<Sz == N>,
                          typename = std::enable_if_t<Utils::is_R3_v<N, Sz>>,
                          typename = std::enable_if_t<std::is_constructible_v<U, T>>>
                constexpr inline vec<N, T> cross_product(const vec<Sz, U>&) const;

            private:
                std::array<T, N> components;
        };

        //////////////////////////////////////////// Operators //////////////////////////////////////////////////////

        template <std::size_t N, typename T>
            template <std::size_t Sz, typename U, typename, typename>
        constexpr inline vec<N, T>& vec<N, T>::operator+= (const vec<Sz, U>& obj)
        {
            for(std::size_t count{}; count < N; ++count)
                this->components[count] += obj.components[count];
            
            return *this;
        }

        template <std::size_t N, typename T>
            template <std::size_t Sz, typename U, typename, typename>
        constexpr inline vec<N, T>& vec<N, T>::operator-= (const vec<Sz, U>& obj)
        {
            for(std::size_t count{}; count < N; ++count)
                this->components[count] -= obj.components[count];
            
            return *this;
        }

        template <std::size_t N, typename T>
            template <typename>
        constexpr inline vec<N, T>& vec<N, T>::operator*= (const float scl)
        {
            for (auto& elem : *this)
                elem *= scl;
            
            return *this;
        }

        template <std::size_t N, typename T>
            template <typename> 
        constexpr inline vec<N, T>& vec<N, T>::operator /= (const float scl)
        {
            for (auto& elem : *this)
                elem /= scl;
            
            return *this;
        }

        template <std::size_t N, typename T>
        constexpr inline const T& vec<N, T>::operator[] (const std::size_t idx) const
        {
            assert(idx < N); //"[ERROR] Invalid index");

            return components[idx];
        }

        template <std::size_t N, typename T>
        constexpr inline T& vec<N, T>::operator[] (const std::size_t idx)
        {
            assert(idx < N); //"[ERROR] Invalid index");

            return components[idx];
        }

        //////////////////////////////////////////// Functions friends ////////////////////////////////////////////////
    
        template <std::size_t Sz, typename U>
        constexpr inline bool operator== (const vec<Sz, U>& lhs, const vec<Sz, U>& rhs)
        {
            for(std::size_t count{}; count < Sz; ++count)
                if (lhs.components[count] != rhs.components[count])
                    return false;
            
            return true;
        }

        template <std::size_t Sz, typename U>
        constexpr inline bool operator!= (const vec<Sz, U>& lhs, const vec<Sz, U>& rhs)
        {
            return !(lhs == rhs);
        }

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator+ (vec<Sz, U> lhs, const vec<Sz, U>& rhs)
        {
            lhs += rhs;

            return lhs;
        }

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator- (vec<Sz, U> lhs, const vec<Sz, U>& rhs)
        {
            lhs -= rhs;

            return lhs;
        }

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator* (vec<Sz, U> obj, const float scl)
        {
            obj *= scl;

            return obj;
        }

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator* (const float scl, vec<Sz, U> obj)
        {
            return obj * scl;
        }

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator/ (vec<Sz, U> obj, const float scl)
        {
            obj /= scl;

            return obj;
        }

        template <std::size_t Sz, typename U>
        constexpr inline vec<Sz, U> operator/ (const float scl, vec<Sz, U> obj)
        {
            return obj / scl;
        }

        template <std::size_t Sz, typename U>
        inline std::ostream& operator << (std::ostream& os, const vec<Sz, U> vobj)
        {
            return os << "[" << vobj[0] << ", "
                      << vobj[1] << ", "
                      << vobj[2] << "]" << std::endl;
        }

        //////////////////////////////////////////// Member Functions /////////////////////////////////////////////////

        template <std::size_t N, typename T>
        constexpr inline vec<N, T>& vec<N, T>::negative()
        {
            (*this) *= -1;

            return *this;
        }

        template <std::size_t N, typename T>
            template <typename>
        constexpr inline bool vec<N, T>::is_zero_vec() const
        {
            const value_type temp{};

            for (const auto& elem : this->components)
                if (elem != temp)
                    return false;
            
            return true;
        }

        template <std::size_t N, typename T>
            template <typename>
        constexpr inline float vec<N, T>::magnitude() const
        {
            if (this->is_zero_vec())
                return 0.0f;

            float mag{};

            for(auto elem : components)
                mag += (elem * elem);

            return Utils::sqrt<float>{}(mag);
        }

        template <std::size_t N, typename T>
            template <typename, typename>
        constexpr inline vec<N, T>& vec<N, T>::normalize()
        {
            if (this->is_zero_vec())
                return  *this;

            return *this /= this->magnitude();
        }

        template <std::size_t N, typename T>
            template <typename,typename>
        constexpr inline vec<N, T> vec<N, T>::copy_normalized() const
        {
            auto temp = *this;

            return temp.normalize();
        }

        template <std::size_t N, typename T>
            template <std::size_t Sz, typename U, typename, typename, typename>
        constexpr inline float vec<N, T>::distance(const vec<Sz, U>& obj) const
        {
            float dist{};

            for(size_type idx{}; idx < N; ++idx)
                dist += POW2(obj.components[idx] - this->components[idx]);

            return Utils::sqrt<float>{}(dist);
        }

        template <std::size_t N, typename T>
            template <std::size_t Sz, typename U, typename, typename, typename>
        constexpr inline float vec<N, T>::dot(const vec<Sz, U>& obj) const
        {
            float dot_product{};

            for (std::size_t idx{}; idx < N; ++idx)
                dot_product += this->components[idx] * obj.components[idx];
            
            return dot_product;
        }

        template <std::size_t N, typename T>
            template <std::size_t Sz, typename U, 
                      typename, typename, 
                      typename, typename>
        constexpr inline float vec<N,T>::dot(const vec<Sz, U>& obj, float degrees) const
        {
            if (this->is_zero_vec() || obj.is_zero_vec())
                return float{};

            return this->magnitude() * obj.magnitude() * cos(degrees * M_PI/180.f);
        }

        template <std::size_t N, typename T>
            template <std::size_t Sz, typename U,
                    typename,typename,
                    typename,typename>
        constexpr inline float vec<N, T>::angle_between(const vec<Sz, U>& obj, float dot_product) const
        {
            if (this->is_zero_vec() || obj.is_zero_vec())
                return float{};
            
            float v_cos = dot_product/(this->magnitude() * obj.magnitude());

            return acos(v_cos) * 180.f/M_PI;
        }

        template<std::size_t N, typename T>
            template <std::size_t Sz, typename U, typename, typename,typename>
        constexpr inline vec<N, T> vec<N, T>::cross_product(const vec<Sz, U>& obj) const
        {
            auto intern = *this;

            return vec<N, T>{ intern[1] * obj[2] - intern[2] * obj[1],
                              -1 * (intern[0] * obj[2] - intern[2] * obj[0]),
                              intern[0] * obj[1] - intern[1] * obj[0]};
        }
    }
}