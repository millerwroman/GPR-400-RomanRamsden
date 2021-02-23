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
	const int size = 10000;
	const int runTimes = 100;
	int numberArray[size];
	
	RunInfo info = RunInfo();
	for (int i = 0; i < runTimes; ++i)
	{
		SetRandomSeed(64*i);
		PopulateArray(numberArray, size);
		timer->StartTimer("Bubble Sort");
		BubbleSort(numberArray, size);
		float timeTaken = timer->StopTimer("Bubble Sort");

		info.averageTime += timeTaken;
		info.minTime = (timeTaken < info.minTime ? timeTaken : info.minTime);
		info.maxTime = (timeTaken > info.maxTime ? timeTaken : info.maxTime);
	}
	info.averageTime /= runTimes;

	Print(numberArray, size);
	printf("\n\nRuntime Info: \n");
	printf("Max Time: %f \n", info.maxTime);
	printf("Min Time: %f \n", info.minTime);
	printf("Average Time: %f \n", info.averageTime);
	printf("Sample Size: %i \n", runTimes);
	system("pause");
	return 0;
}