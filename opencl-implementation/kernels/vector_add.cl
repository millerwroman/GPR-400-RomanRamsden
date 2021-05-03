__kernel void vector_add(__global float* A, __global float* B, __global float* C, const unsigned int count)
{
	// Get the index of the current element to be processed
	int i = get_global_id(0);

	// Do the operation
	if (i < count) {
		C[i] = A[i] + B[i];
	}
}
