#define __CL_ENABLE_EXCEPTIONS

// Utility Libraries
#include <OpenCLWrapper.h>
#include <PerformanceTimer.h>
#include <Random.h>
#include "VectorAdd.h"

// Some error handling for OpenCL
#include "err_code.h"

const unsigned int RANDOM_SEED = 2435345;

constexpr int count (10000);
typedef unsigned int uint;

int main(void)
{
	// Initialize the timer for this experiment
	SetSeed(RANDOM_SEED);
	Timer* timer = new Timer();
	
	try
	{
		std::vector<uint> primeArray(count);
		for(int i = 0; i < count; ++i)
		{
			primeArray[i] = GetRandomUInt32();
		}

		cl::Buffer inputVector;
		cl::Buffer outputVector;

		cl::Context context(DEVICE);

		cl::Program program(context, LoadKernel("prime_factor.cl"), true);

		cl::CommandQueue commandQueue(context);

		cl::make_kernel<cl::Buffer, cl::Buffer, int> primeFactor(program, "prime_factor");

		inputVector = cl::Buffer(context, primeArray.begin(), primeArray.end(), true);
		outputVector = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(uint) * count);

		timer->StartTimer("Main");

		primeFactor(
		cl::EnqueueArgs(
		commandQueue, cl::NDRange(count)),
			inputVector, outputVector, count);

		commandQueue.finish();

		timer->StopTimer("Main");

		std::cout << "The kernels ran in "
		<< std::to_string(timer->GetElapsedTime("Main"))
		<< " seconds\n" << std::endl;

		std::vector<uint> outputArray(count);
		
		cl::copy(commandQueue, outputVector, outputArray.begin(), outputArray.end());
		
		for(int i = 0; i < count; ++i)
		{
			if(primeArray[i] == outputArray[i])
			{
				std::cout << "POG!" << std::endl;
			}
			else
			{
				std::cout << "NOT POG!" << std::endl;
			}
		}
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
