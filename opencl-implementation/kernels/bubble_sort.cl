// Basic OpenCL Bubblesort

__kernel void bubble_sort(
	__global int* in,
	__global int* out,
	const unsigned int count)
{
	// Get the thread ID we're currently on
	int id = get_global_id(0);

	// Handles out of bounds stuff
	if (id < count) {

		// Get two numbers, index and right of index
		int left = in[id];
		int right = in[id + 1];

		// Perform the swap
		if(left > right)
		{
			int temp = left;
			left = right;
			right = temp;
		}

		// Write the swapped values to the outbound vector
		out[id] = left;
		out[id+1] = right;
	}
}
