void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

// Basic sort comparator
void sort(int* x, int* y)
{
	if((*x > *y) swap(x, y);
}

// Basic OpenCL Bubblesort
__kernel void BubbleSort(__global int* arr, __global int size)
{
	int index = get_global_id(0) << 1;
	if(index + 1 >= size) return;

	sort(&arr[index], &arr[index+1]);
}
