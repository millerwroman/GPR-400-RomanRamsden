__kernel void prime_factor(
	__global unsigned long long* in,
	__global unsigned long long* out,
	const unsigned int count)
{
	int id = get_global_id(0);

	if (id < count) {
		// Get the current index
		int n = in[id];

		if (n % 2 == 0) {
			// printf("2\t");
			in[id] = n / 2;
		}

		n = in[id];
		float sqr = powr(n, 0.5);

		for (int i = 3; i <= sqr; i = i + 2)
		{
			if (n % i == 0) {
				// printf("%lld\t", i);
				in[id] = n / i;
			}
		}

		n = in[id];

		if (in[id] > 2)
		{
			// printf("%lld\n", in[id]);
		}
	}
}