#include "OpenCLWrapper.h"
#include "VectorAdd.h"
#include "BubbleSort.h"
#include <stdio.h>

int main(void) {
	// GENERIC OPENCL
	// Load the kernel source code into the array source_str
	FILE* fp;

	// Find the local kernel to open and read info from it
	// NOTE: This is program-specific
	// char* kernelToOpen = openKernel("bubble_sort.cl");
	char* kernelToOpen = openKernel("prime_factor.cl");
	fp = fopen(kernelToOpen, "r");

	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}

	// Wrapper for char* and size_t read from kernel
	SourceInfo srcInfo = getSourceInfo(fp);

	fclose(fp);

	DeviceInfo devInfo = ctorDeviceInfo();

	cl_int ret = clGetPlatformIDs(1, &devInfo.plat_id, &devInfo.num_plat);
	ret = clGetDeviceIDs(devInfo.plat_id, CL_DEVICE_TYPE_GPU, 1,
		&devInfo.dev_id, &devInfo.num_dev);

	// Create an OpenCL context
	cl_context context = clCreateContext(NULL, 1, &devInfo.dev_id, NULL, NULL, &ret);

	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, devInfo.dev_id, 0, &ret);

	// Basic Vector Addition via Kernel
	// RunVectorAdd(context, ret, command_queue, srcInfo, devInfo);

	// Basic BubbleSort via Kernel
	// RunBubbleSort(context, ret, command_queue, srcInfo, devInfo);

	// Basic Prime Factorization via Kernel
	printf("Please input your number to factorize: ");
	int input;
	scanf("%d", &input);
	
	printf("Got %d\n", input);

	int* A = (int*)malloc(sizeof(int) * input);
	int* B = (int*)malloc(sizeof(int) * 1);
	
	// Create a memory buffer for our PF Number
	cl_mem mem_factor = clCreateBuffer(context, CL_MEM_READ_WRITE, input * sizeof(int), NULL, &ret);
	cl_mem mem_num = clCreateBuffer(context, CL_MEM_READ_ONLY, 1 * sizeof(int), NULL, &ret);
	
	// Copy the number to the memory buffer
	ret = clEnqueueWriteBuffer(command_queue, mem_factor, CL_TRUE, 0, input * sizeof(int), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, mem_num, CL_TRUE, 0, 1 * sizeof(int), B, 0, NULL, NULL);
	
	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&srcInfo.str, (const size_t*)&srcInfo.size, &ret);

	// Build the program
	ret = clBuildProgram(program, 1, &devInfo.dev_id, NULL, NULL, NULL);

	// Create the OpenCL kernel
	cl_kernel kernel = clCreateKernel(program, "prime_factor", &ret);

	// Set the argument(s) of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&mem_factor);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&mem_num);

	// Execute the OpenCL kernel on the num to factor
	size_t global_item_size = input;
	size_t local_item_size = 64;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
		&global_item_size, &local_item_size, 0, NULL, NULL);

	int * C = (int*)malloc(sizeof(int) * input);
	ret = clEnqueueReadBuffer(command_queue, mem_factor, CL_TRUE, 0, input * sizeof(int), C, 0, NULL, NULL);

	printf("%d", C);
	
	// Clean up Prime Factorization Objects
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(mem_factor);
	ret = clReleaseMemObject(mem_num);
	free(A);
	free(B);
	// GENERIC OPEN CL CLOSE
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	return 0;
}