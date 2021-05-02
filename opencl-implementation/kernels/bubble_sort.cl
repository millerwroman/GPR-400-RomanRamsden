// Basic OpenCL Bubblesort

// Swap helper method
// void swap(int* x, int* y)
// {
// 	int temp = *x;
// 	*x = *y;
// 	*y = temp;
// }
// 
// // Sorting helper method
// void sort(int* x, int* y, char dir)
// {
// 	if ((*x > *b) == dir)
// 		swap(x, y);
// }

__kernel void bubble_sort(
	__global int* in,
	__global int* out,
	const unsigned int count)
{
	int id = get_global_id(0);

	// Handles out of bounds stuff
	if (id < count) {

		// Get two numbers, index and right of index
		int left = in[id];
		int right = in[id + 1];

		if(left > right)
		{
			int temp = left;
			left = right;
			right = temp;
		}

		out[id] = left;
		out[id+1] = right;

		// return;
		// 
		// Sort(&left, &right, 1);
		// out[id] = left;
		// out[id + 1] = right;
	}
}
