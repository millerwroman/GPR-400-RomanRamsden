__kernel void prime_factor(
	__global unsigned int* in,
	__global unsigned int* out,
	const unsigned int count)
{
	int i = get_global_id(0);

	if (i < count) {
		out[i] = in[i];
	}
}