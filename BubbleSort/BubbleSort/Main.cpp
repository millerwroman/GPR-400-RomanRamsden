#pragma once
#include <cstdio>
#include <iostream>

#include "PreformaceTimer.h"
#include "Random.h"
#include "GameOfLife.h"
#include  "vector"

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

void Print(std::vector<int> vec)
{
	for (auto i : vec)
	{
		printf("%i", i);
	}
}

void PopulateArray(int arr[], int sizeToPopulate)
{
	for (int i = 0; i < sizeToPopulate; ++i)
	{
		arr[i] = (int)GetRandomFloat32_Range(0, (5 * sizeToPopulate));
	}
}

//Implementation of the "Vishwas Garg" method
//Known as the simplest implementation of a prime factorization algorithms 
std::vector<int> FactorPrimes(long long n)
{
	std::vector<int>::iterator it;
	std::vector<int> primes;

	while (n % 2 == 0)
	{
		it = primes.end();
		primes.insert(it, 2);
		n = n / 2;
	}

	for (int i = 3; i <= sqrt(n); i = i + 2)
	{
		while (n % i == 0)
		{
			it = primes.end();
			primes.insert(it, 2);
			n = n / i;
		}
	}

	if (n > 2)
	{
		it = primes.end();
		primes.insert(it, n);
	}
	return primes;
}



int main()
{
	Timer* timer = new Timer();
	const int runTimes = 1000000;
	RunInfo info = RunInfo();

	std::cout << COLOR_GREEN;
	clearScreen();
	bool gridOne[gridSize+1][gridSize+1] = {};
	const int numCells = 5;
	int x, y, n;
	std::string start;

	for(int i = 0; i < numCells; ++i)
	{
		std::cout << numCells << "Enter the coordinates of cell " << i+1 << " : ";
		std::cin >> x >> y;
		gridOne[x][y] = true;
		printGrid(gridOne);
	}

	std::cout << "Grid setup is done. Start the game ? (y/n)" << std::endl;
	printGrid(gridOne);
	std::cin >> start;

	if(start == "y" || start == "Y")
	{
		while(true)
		{
			printGrid(gridOne);
			determineState(gridOne);
			Sleep(1500);
			clearScreen();
		}
	}

	std::cout << COLOR_RESET;
	clearScreen();
	return 0;

	system("pause");
	return 0;
	
	/* Bubble Sort
	const int size = 10000;
	int numberArray[size];
	for (int i = 0; i < runTimes; ++i)
	{
		SetRandomSeed(64 * i);
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
	*/
	const long long numberToFactor = (long long)GetRandomFloat32_Range(4 * 10000000, (6 * 10000000));
	std::vector<int> finalRun;
	for (int i = 0; i < runTimes; ++i)
	{
		timer->StartTimer("Prime");
		finalRun = FactorPrimes(9223372036854775807);
		float timeTaken = timer->StopTimer("Prime");
		info.averageTime += timeTaken;
		info.minTime = (timeTaken < info.minTime ? timeTaken : info.minTime);
		info.maxTime = (timeTaken > info.maxTime ? timeTaken : info.maxTime);
	}
	info.averageTime /= runTimes;

	printf("\n\nRuntime Info: \n");
	printf("Number Factored: %u \n", (unsigned int)numberToFactor);
	printf("Max Time: %f \n", info.maxTime);
	printf("Min Time: %f \n", info.minTime);
	printf("Average Time: %f \n", info.averageTime);
	printf("Sample Size: %i \n", runTimes);
	Print(finalRun);
	
	system("pause");
	return 0;
}