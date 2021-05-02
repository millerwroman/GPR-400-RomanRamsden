#pragma once
#include "OpenCLWrapper.h"
#include "PerformanceTimer.h"

// Vector length, used in a test program
#define LENGTH (1024)
// Float tolerance handling
#define TOL    (0.001)

void RunVectorAdd(Timer* timer)
{
	// Create some vectors of size 1024
	std::vector<float> hA(LENGTH);
	std::vector<float> hB(LENGTH);
	std::vector<float> hC(LENGTH);

	// Fill vectors with random float values
	int count = LENGTH;

	for (int i = 0; i < count; ++i)
	{
		hA[i] = rand() / static_cast<float>(RAND_MAX);
		hB[i] = rand() / static_cast<float>(RAND_MAX);
	}

	// Start doing OpenCL stuff

	// Create some memory buffers for input, input, and output
	cl::Buffer dA;
	cl::Buffer dB;
	cl::Buffer dC;
	
	// Create a context on the GPU
	cl::Context context(DEVICE);

	// Load the kernel and create a program
	cl::Program program(context, LoadKernel("vector_add.cl"), true);

	// Create a queue to perform operations on
	cl::CommandQueue commandQueue(context);

	// Create the kernel functor
	cl::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer, int> vectorAdd(program, "vector_add");

	dA = cl::Buffer(context, hA.begin(), hA.end(), true);
	dB = cl::Buffer(context, hB.begin(), hB.end(), true);
	dC = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * LENGTH);

	timer->StartTimer("Main");

	// Run the kernel program
	vectorAdd(
		cl::EnqueueArgs(
			commandQueue, cl::NDRange(count)),
		dA, dB, dC, count);

	// Wait for the kernel program to finish
	commandQueue.finish();

	timer->StopTimer("Main");

	std::cout << "The kernels ran in "
		<< std::to_string(timer->GetElapsedTime("Main"))
		<< " seconds\n" << std::endl;

	cl::copy(commandQueue, dC, hC.begin(), hC.end());

	int correct = 0;
	float tmp;

	for (int i = 0; i < count; ++i)
	{
		tmp = hA[i] + hB[i];
		tmp -= hC[i];
		if (tmp * tmp < TOL * TOL)
		{
			correct++;
		}
		else
		{
			printf("tmp %f hA %f hB %f hC %f \n",
				tmp,
				hA[i],
				hB[i],
				hC[i]);
		}
	}


	printf(
		"vector add to find C = A+B: %d out of %d results were correct.\n",
		correct,
		count);
}