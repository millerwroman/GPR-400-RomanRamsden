#include <time.h>

#include "OpenCLWrapper.h"
#include "VectorAdd.h"
#include "Random.h"

int main(void) {
	// GENERIC OPENCL
	// Load the kernel source code into the array source_str
	FILE* fp;

	// Find the local kernel to open and read info from it
	// NOTE: This is program-specific
	char* kernelToOpen = openKernel("bubble_sort.cl");
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
	int i;
	const int LIST_SIZE = 10000;
	int* arr = (int*)malloc(sizeof(int) * LIST_SIZE);

	time_t t;
	srand((unsigned)time(&t));

	for (i = 0; i < LIST_SIZE; ++i)
	{
		arr[i] = (int)GetRandomFloat32_Range(0, (5 * LIST_SIZE));
	}

	// Create memory buffer for the array
	cl_mem mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);

	// Copy the array to a memory buffer
	ret = clEnqueueWriteBuffer(command_queue, mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), arr, 0, NULL, NULL);

	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&srcInfo.str, (const size_t*)&srcInfo.size, &ret);

	// Build the program
	ret = clBuildProgram(program, 1, &devInfo.dev_id, NULL, NULL, NULL);

	// Create the OpenCL kernel;
	cl_kernel kernel = clCreateKernel(program, "bubble_sort", &ret);

	// set the argument of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&mem_obj);

	// Execute the OpenCL kernel on the list
	size_t global_item_size = LIST_SIZE; // process the entire list
	size_t local_item_size = 64; // Divive work items into groups of 64
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
		&global_item_size, &local_item_size, 0, NULL, NULL);

	int* outArray = (int*)malloc(sizeof(int) * LIST_SIZE);
	ret = clEnqueueReadBuffer(command_queue, mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), outArray, 0, NULL, NULL);

	for (i = 0; i < LIST_SIZE; ++i)
	{
		printf("%i , ", arr[i]);
		if (i % 15 == 0)
		{
			printf("\n");
		}
	}

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(mem_obj);

	// GENERIC OPEN CL CLOSE
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(arr);
	return 0;
}