// OpenCL Prime Factorization
__kernel void prime_factor(
	__global unsigned long long* in,
	__global unsigned long long* out,
	const unsigned int count)
{
	// Get the current thread index
	int id = get_global_id(0);

	if (id < count) {
		// Grab the integer (doing so in the statement breaks kernel)
		int n = in[id];

		if (n % 2 == 0) {
			// printf("2\t");
			in[id] = n / 2;
		}

		// Get the integer at the current id
		n = in[id];

		// Take the square root (sqrt crashes the kernel)
		float sqr = powr(n, 0.5);

		// Continue factoring down the line
		for (int i = 3; i <= sqr; i = i + 2)
		{
			if (n % i == 0) {
				// printf("%lld\t", i);
				in[id] = n / i;
			}
		}

		// Get the integer at current id again
		n = in[id];

		if (n > 2)
		{
			// printf("%lld\n", in[id]);
		}
	}
}