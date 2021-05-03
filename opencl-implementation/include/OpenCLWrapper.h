#ifndef OPENCL_WRAPPER_H
// Utility Library for Connor Ramsden's OpenCL implementations
#define OPENCL_WRAPPER_H

// OpenCL core include
#include <CL/cl.hpp>

// Standard C++ includes
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>

// We'll be using the default device, since we only have one (my GPU)
#ifndef DEVICE
#define DEVICE CL_DEVICE_TYPE_DEFAULT
#endif

std::string LoadKernel(std::string input);

#endif
