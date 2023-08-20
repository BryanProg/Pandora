#pragma once

#include <iostream>
#include <utils.hpp>
#include <cstdint>
#include <type_traits>
#include <array>
namespace Pandora::Mat
{
	//Mat<row, column, type>

	template <uint8_t R, uint8_t C, typename T>
	class Mat;

	template <std::uint8_t R, std::uint8_t C, typename U>
    inline std::ostream& operator << (std::ostream&, const Mat<R, C, U>&);

	namespace FastDef
	{
		template <uint8_t C, typename T>
		using Mat1 = Mat<1, C, T>;
		template <uint8_t C, typename T>
		using Mat2 = Mat<2, C, T>;
		template <uint8_t C, typename T>
		using Mat3 = Mat<3, C, T>;
		template <uint8_t C, typename T>
		using Mat4 = Mat<4, C, T>;

		template <typename T>
		using Mat1x1 = Mat<1, 1, T>;
		template <typename T>
		using Mat2x2 = Mat<2, 2, T>;
		template <typename T>
		using Mat3x3 = Mat<3, 3, T>;
		template <typename T>
		using Mat4x4 = Mat<4, 4, T>;

		template <typename T>
		using Mat1x1i = Mat<1, 1, std::enable_if_t<Utils::is_int_v<T>, T>>;
		template <typename T>
		using Mat2x2i = Mat<2, 2, std::enable_if_t<Utils::is_int_v<T>, T>>;
		template <typename T>
		using Mat3x3i = Mat<3, 3, std::enable_if_t<Utils::is_int_v<T>, T>>;
		template <typename T>
		using Mat4x4i = Mat<4, 4, std::enable_if_t<Utils::is_int_v<T>, T>>;

		template <typename T>
		using Mat1x1u = Mat<1, 1, std::enable_if_t<Utils::is_uint_v<T>, T>>;
		template <typename T>
		using Mat2x2u = Mat<2, 2, std::enable_if_t<Utils::is_uint_v<T>, T>>;
		template <typename T>
		using Mat3x3u = Mat<3, 3, std::enable_if_t<Utils::is_uint_v<T>, T>>;
		template <typename T>
		using Mat4x4u = Mat<4, 4, std::enable_if_t<Utils::is_uint_v<T>, T>>;

		using Mat1x1f = Mat<1, 1, float>;
		using Mat2x2f = Mat<2, 2, float>;
		using Mat3x3f = Mat<3, 3, float>;
		using Mat4x4f = Mat<4, 4, float>;

		using Mat1x1df = Mat<1, 1, double>;
		using Mat2x2df = Mat<2, 2, double>;
		using Mat3x3df = Mat<3, 3, double>;
		using Mat4x4df = Mat<4, 4, double>;
	}
	template <uint8_t R, uint8_t C, typename T>
	class Mat
	{
		friend std::ostream& operator <<<R, C, T> (std::ostream& os, const Mat<R, C, T>& obj);

		public:
			constexpr Mat() = default;
			~Mat() = default;

			constexpr Mat( const Mat&) = default;
			constexpr Mat(Mat&&) = default;

			constexpr Mat& operator= (const Mat&) = default;
			constexpr Mat& operator= (Mat&&) = default;


			template <typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
			Mat(U&& init_value);

		// API Public
		public:
			void identity();
			void transpose();

		private:
			std::array<T, R * C> mat_;
	};

	template <uint8_t R, uint8_t C, typename T>
		template<typename U, typename>
	Mat<R, C, T>::Mat(U&& init_value)
		: mat_{}
	{
		mat_.fill(std::forward<U>(init_value));
	}

	template <std::uint8_t R, std::uint8_t C, typename U>
    inline std::ostream& operator << (std::ostream& os, const Mat<R, C, U>& obj)
	{

		os << "{\n";

		for(uint8_t count{1}; const auto& elems : obj.mat_)
		{
			os << "   " << elems << (((count % C) == 0) ? "\n" : ", ");
			++count;
		}
		return os << "}" << std::endl;
	}
}
