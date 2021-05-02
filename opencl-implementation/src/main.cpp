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

int main(void)
{
	// Initialize the timer for this experiment
	SetSeed(RANDOM_SEED);
	Timer* timer = new Timer();

	// Populate an array with random integers
	std::vector<int> arrayIn(LENGTH);
	
	for(int i = 0; i < LENGTH; ++i)
	{
		arrayIn[i] = static_cast<int>(GetRandomFloat32_Range(0, (5 * LENGTH)));
		std::cout << arrayIn[i] << std::endl;
	}
	
	try
	{
		// RunVectorAdd(timer);
		// RunPrimeFactor(timer);
		
		cl::Context context(DEVICE);
		cl::Program program(context, LoadKernel("bubble_sort.cl"));
		cl::CommandQueue commandQueue(context);
				
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
