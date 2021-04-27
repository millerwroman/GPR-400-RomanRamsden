#pragma once

#include "OpenCLWrapper.h"
#include "Random.h"
#include "time.h"

static void RunBubbleSort(cl_context ctx, cl_int ret, cl_command_queue cmd_q,
                          SourceInfo srcInfo, DeviceInfo devInfo)
{
	
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
	cl_mem mem_obj = clCreateBuffer(ctx, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);

	// Copy the array to a memory buffer
	ret = clEnqueueWriteBuffer(cmd_q, mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), arr, 0, NULL, NULL);

	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(ctx, 1, (const char**)&srcInfo.str, (const size_t*)&srcInfo.size, &ret);

	// Build the program
	ret = clBuildProgram(program, 1, &devInfo.dev_id, NULL, NULL, NULL);

	// Create the OpenCL kernel;
	cl_kernel kernel = clCreateKernel(program, "bubble_sort", &ret);

	// set the argument of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&mem_obj);

	// Execute the OpenCL kernel on the list
	size_t global_item_size = LIST_SIZE; // process the entire list
	size_t local_item_size = 64; // Divide work items into groups of 64
	ret = clEnqueueNDRangeKernel(cmd_q, kernel, 1, NULL,
		&global_item_size, &local_item_size, 0, NULL, NULL);

	int* outArray = (int*)malloc(sizeof(int) * LIST_SIZE);
	ret = clEnqueueReadBuffer(cmd_q, mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), outArray, 0, NULL, NULL);

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
	free(arr);
}