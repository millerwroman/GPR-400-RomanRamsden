#define __CL_ENABLE_EXCEPTIONS

// Utility Libraries
#include <OpenCLWrapper.h>
#include <PerformanceTimer.h>
#include <Random.h>
#include "VectorAdd.h"
#include "PrimeFactor.h"
#include "BubbleSort.h"

// Some error handling for OpenCL
#include "err_code.h"

const unsigned int RANDOM_SEED = 2435345;
constexpr int len(10000);

int main(void)
{
	// Initialize the timer for this experiment
	SetSeed(RANDOM_SEED);
	Timer* timer = new Timer();

	// Create an array to hold integers
	std::vector<int> originVector(len);

	// Populate an array with random integers
	for (int i = 0; i < len; ++i)
	{
		originVector[i] = static_cast<int>(GetRandomFloat32_Range(0, (5 * len)));
	}

	try
	{
		// RunVectorAdd(timer);
		// RunPrimeFactor(timer);

		// return 0;
		cl::Buffer inputVector;
		cl::Buffer outputVector;

		cl::Context context(DEVICE);
				
		cl::Program program(context, LoadKernel("bubble_sort.cl"), true);

		cl::CommandQueue commandQueue(context);

		cl::make_kernel<cl::Buffer, cl::Buffer, int> bubbleSort(program, "bubble_sort");

		inputVector = cl::Buffer(context, originVector.begin(),
			originVector.end(), true);
		outputVector = cl::Buffer(context, CL_MEM_WRITE_ONLY,
			sizeof(int) * len);

		timer->StartTimer("Main");

		bubbleSort(
			cl::EnqueueArgs(
				commandQueue, cl::NDRange(len)),
			inputVector, outputVector, len);

		commandQueue.finish();

		timer->StopTimer("Main");

		std::cout << "\nThe kernels ran in " << std::to_string(timer->GetElapsedTime("Main"))
			<< " seconds\n" << std::endl;

		std::vector<int> destinationVector(len);

		cl::copy(commandQueue, outputVector, destinationVector.begin(), destinationVector.end());

		for(int i = 0; i < destinationVector.size(); ++i)
		{
			std::cout << originVector[i] << "\t";
			std::cout << destinationVector[i] << std::endl;
		}

		std::cout << "\nThe kernels ran in " << std::to_string(timer->GetElapsedTime("Main"))
			<< " seconds\n" << std::endl;
	}
	catch (cl::Error err)
	{
		std::cout << "Exception\n";
		std::cerr
			<< "ERROR: "
			<< err.what()
			<< "("
			<< err_code(err.err())
			<< ")"
			<< std::endl;
	}

	// Clean up timer
	delete(timer);
	timer = nullptr;

	return 0;
}
