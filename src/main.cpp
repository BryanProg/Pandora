#include <iostream>
#include <pandora.hpp>

auto main(int, char**) -> int
{
	//Pandora::Vec::FastDefs::vec2fp vct(5.0);

	Pandora::Mat::Mat<3, 3, double> matriz(33.44f);

	std::cout << matriz;
	return EXIT_SUCCESS;
}
