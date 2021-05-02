#pragma once

#include "OpenCLWrapper.h"
#include "PerformanceTimer.h"
#include "Random.h"
#include "time.h"

constexpr int count(10000);
typedef unsigned int uint;
typedef long long llong;


static void RunPrimeFactor(Timer* timer)
{
	std::vector<llong> primeArray(count);

	// Fill an array with 9223372036854775807
	for (int i = 0; i < count; ++i)
	{
		primeArray[i] = LLONG_MAX;
	}

	cl::Buffer inputVector;
	cl::Buffer outputVector;

	cl::Context context(DEVICE);

	cl::Program program(context, LoadKernel("prime_factor.cl"), true);

	cl::CommandQueue commandQueue(context);

	cl::make_kernel<cl::Buffer, cl::Buffer, int> primeFactor(program, "prime_factor");

	inputVector = cl::Buffer(context, primeArray.begin(), primeArray.end(), true);
	outputVector = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(llong) * count);

	timer->StartTimer("Main");

	primeFactor(
		cl::EnqueueArgs(
			commandQueue, cl::NDRange(count)),
		inputVector, outputVector, count);

	commandQueue.finish();

	timer->StopTimer("Main");

	std::cout << "\nThe kernels ran in "
		<< std::to_string(timer->GetElapsedTime("Main"))
		<< " seconds\n" << std::endl;

	std::vector<llong> outputArray(count);

	cl::copy(commandQueue, outputVector, outputArray.begin(), outputArray.end());
}
