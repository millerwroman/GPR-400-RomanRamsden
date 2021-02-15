#pragma once
#include <cstdio>
#include "Random.h"
#include <iostream>
#include "PreformaceTimer.h"
void Swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

//Basic Bubble sort O(n^2)
void BubbleSort(int arr[], int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

void Print(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%i , ", arr[i]);
		if (i % 15 == 0)
		{
			printf("\n");
		}
	}
}

void PopulateArray(int arr[], int sizeToPopulate)
{
	for (int i = 0; i < sizeToPopulate; ++i)
	{
		arr[i] = (int)GetRandomFloat32_Range(0, (5 * sizeToPopulate));
	}
}



int main()
{
	Timer* timer = new Timer();
	const int size = 20000;
	int numberArray[size];
	SetRandomSeed(5848582);


	PopulateArray(numberArray, size);

	timer->StartTimer("Bubble Sort");
	BubbleSort(numberArray, size);
	timer->StopTimer("Bubble Sort");

	Print(numberArray, size);
	printf("\n\n Runtime: %f \n\n", timer->GetElapsedTime("Bubble Sort"));
	system("pause");
	return 0;
}