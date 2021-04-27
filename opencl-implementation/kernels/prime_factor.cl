__kernel void prime_factor(__global const int A, __global const int i)
{
	if(i <= A)
	{
		if(A % i == 0)
			printf("%i ", i);
		prime_factor(A, i+1);
	}
}