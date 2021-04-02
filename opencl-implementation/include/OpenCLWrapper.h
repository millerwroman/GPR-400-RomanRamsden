#ifndef OPEN_CL_WRAPPER_H
#define OPEN_CL_WRAPPER_H

// STL Includes
#include <stdio.h>
#include <stdlib.h>

// OpenCL Includes
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

/// <summary>
/// A struct to hold the size and string of a kernel source
/// </summary>
struct SourceInfo
{
	char* str;
	size_t size;
};

/// <summary>
/// Info about the device OpenCL is being run in
/// </summary>
struct DeviceInfo
{
	cl_platform_id plat_id;
	cl_device_id dev_id;
	cl_uint num_dev;
	cl_uint num_plat;
};

// Generates kernel with directory, kinda redundant i guess
char* openKernel(char* fileName);

struct SourceInfo getSourceInfo(FILE* f);
struct DeviceInfo initDeviceInfo();

#endif // OPEN_CL_WRAPPER_H
