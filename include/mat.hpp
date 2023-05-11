#pragma once

#include <iostream>
#include <utils.hpp>
#include <cstdint>
#include <type_traits>
namespace Pandora::Mat
{
	//Mat<row, column, type>

	template <uint8_t R, uint8_t C, typename T>
	class mat;
	namespace FastDef
	{
		template <uint8_t C, typename T>
		using mat1 = mat<1, C, T>;
		template <uint8_t C, typename T>
		using mat2 = mat<2, C, T>;
		template <uint8_t C, typename T>
		using mat3 = mat<3, C, T>;
		template <uint8_t C, typename T>
		using mat4 = mat<4, C, T>;

		template <typename T>
		using mat1x1 = mat<1, 1, T>;
		template <typename T>
		using mat2x2 = mat<2, 2, T>;
		template <typename T>
		using mat3x3 = mat<3, 3, T>;
		template <typename T>
		using mat4x4 = mat<4, 4, T>;

		template <typename T>
		using mat1x1i = mat<1, 1, std::enable_if_t<Utils::is_int_v<T>, T>>;
		template <typename T>
		using mat2x2i = mat<2, 2, std::enable_if_t<Utils::is_int_v<T>, T>>;
		template <typename T>
		using mat3x3i = mat<3, 3, std::enable_if_t<Utils::is_int_v<T>, T>>;
		template <typename T>
		using mat4x4i = mat<4, 4, std::enable_if_t<Utils::is_int_v<T>, T>>;

		template <typename T>
		using mat1x1u = mat<1, 1, std::enable_if_t<Utils::is_uint_v<T>, T>>;
		template <typename T>
		using mat2x2u = mat<2, 2, std::enable_if_t<Utils::is_uint_v<T>, T>>;
		template <typename T>
		using mat3x3u = mat<3, 3, std::enable_if_t<Utils::is_uint_v<T>, T>>;
		template <typename T>
		using mat4x4u = mat<4, 4, std::enable_if_t<Utils::is_uint_v<T>, T>>;

		using mat1x1f = mat<1, 1, float>;
		using mat2x2f = mat<2, 2, float>;
		using mat3x3f = mat<3, 3, float>;
		using mat4x4f = mat<4, 4, float>;

		using mat1x1df = mat<1, 1, double>;
		using mat2x2df = mat<2, 2, double>;
		using mat3x3df = mat<3, 3, double>;
		using mat4x4df = mat<4, 4, double>;
	}
	template <uint8_t R, uint8_t C, typename T>
	class mat
	{
	};
}
