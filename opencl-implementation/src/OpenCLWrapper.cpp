#include "OpenCLWrapper.h"

std::string LoadKernel(std::string input)
{
	std::string kernelName = "kernels/" + input;
	std::ifstream stream(kernelName.c_str());
	if (!stream.is_open()) {
		std::cout << "Cannot open file: " << kernelName << std::endl;
		exit(1);
	}

	return std::string(
		std::istreambuf_iterator<char>(stream),
		(std::istreambuf_iterator<char>()));
}