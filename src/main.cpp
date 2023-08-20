#include <iostream>
#include <pandora.hpp>

auto main(int, char**) -> int
{
	//Pandora::Vec::FastDefs::vec2fp vct(5.0);

	Pandora::Mat::Mat<4, 4, double> matriz(33.44f);


	auto mat2 = matriz;

	std::cout << mat2;
	return EXIT_SUCCESS;
}
