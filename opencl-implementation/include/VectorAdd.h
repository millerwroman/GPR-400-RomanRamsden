#pragma once

#include "OpenCLWrapper.h"

static void RunVectorAdd(cl_context ctx, cl_int ret, cl_command_queue cmd_q,
	SourceInfo srcInfo, DeviceInfo devInfo)
{
	/// KERNEL SPECIFIC

	// Create the two input vectors
	int i;

	const int LIST_SIZE = 1024;

	int* A = (int*)malloc(sizeof(int) * LIST_SIZE);
	int* B = (int*)malloc(sizeof(int) * LIST_SIZE);

	for (i = 0; i < LIST_SIZE; i++) {
		A[i] = i;
		B[i] = LIST_SIZE - i;
	}


	// Create memory buffers on the device for each vector 
	cl_mem a_mem_obj = clCreateBuffer(ctx, CL_MEM_READ_ONLY,
		LIST_SIZE * sizeof(int), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(ctx, CL_MEM_READ_ONLY,
		LIST_SIZE * sizeof(int), NULL, &ret);
	cl_mem c_mem_obj = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY,
		LIST_SIZE * sizeof(int), NULL, &ret);

	// Copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(cmd_q, a_mem_obj, CL_TRUE, 0,
		LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(cmd_q, b_mem_obj, CL_TRUE, 0,
		LIST_SIZE * sizeof(int), B, 0, NULL, NULL);

	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(ctx, 1,
		(const char**)&srcInfo.str, (const size_t*)&srcInfo.size, &ret);

	// Build the program
	ret = clBuildProgram(program, 1, &devInfo.dev_id, NULL, NULL, NULL);

	// Create the OpenCL kernel
	cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);

	// Set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_mem_obj);

	// Execute the OpenCL kernel on the list
	size_t global_item_size = LIST_SIZE; // Process the entire lists
	size_t local_item_size = 64; // Divide work items into groups of 64
	ret = clEnqueueNDRangeKernel(cmd_q, kernel, 1, NULL,
		&global_item_size, &local_item_size, 0, NULL, NULL);

	// Read the memory buffer C on the device to the local variable C
	int* C = (int*)malloc(sizeof(int) * LIST_SIZE);
	ret = clEnqueueReadBuffer(cmd_q, c_mem_obj, CL_TRUE, 0,
		LIST_SIZE * sizeof(int), C, 0, NULL, NULL);

	// Display the result to the screen
	for (i = 0; i < LIST_SIZE; i++)
		printf("%d + %d = %d\n", A[i], B[i], C[i]);

	// Clean up
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj);
	ret = clReleaseMemObject(c_mem_obj);
	free(A);
	free(B);
	free(C);
}