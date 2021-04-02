#include "OpenCLWrapper.h"
#include "VectorAdd.h"

int main(void) {
	// GENERIC OPENCL
	// Load the kernel source code into the array source_str
	FILE* fp;

	// Find the local kernel to open and read info from it
	// NOTE: This is program-specific
	char* kernelToOpen = openKernel("vector_add.cl");
	fp = fopen(kernelToOpen, "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}

	// Wrapper for char* and size_t read from kernel
	struct SourceInfo srcInfo = getSourceInfo(fp);

	fclose(fp);

	struct DeviceInfo devInfo = ctorDeviceInfo();

	cl_int ret = clGetPlatformIDs(1, &devInfo.plat_id, &devInfo.num_plat);
	ret = clGetDeviceIDs(devInfo.plat_id, CL_DEVICE_TYPE_GPU, 1,
		&devInfo.dev_id, &devInfo.num_dev);

	// Create an OpenCL context
	cl_context context = clCreateContext(NULL, 1, &devInfo.dev_id, NULL, NULL, &ret);

	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, devInfo.dev_id, 0, &ret);

	// Basic Vector Addition via Kernels
	// RunVectorAdd(context, ret, command_queue, srcInfo, devInfo);

	// Basic BubbleSort via Kernels

	
	// GENERIC OPEN CL CLOSE
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	return 0;
}