//Jeffrey Stoddard
//CECS 328
//Lab 1

#include <iostream>
#include <algorithm>
#include <chrono>

int *arr;
long int size = 0;


void InitArray()
{
	std::cout << "Please enter a positive integer for the array size: ";
	std::cin >> size;
	arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 2001 - 1000;
	}
}


int linearSearch(int a[], long int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (a[i] == key)
		{
			return i;
		}
	}
	return -1;
}


int binarySearch(int a[], long int size, int key)
{
	int low = 0;
	int high = size;
	int mid;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key == a[mid])
		{
			return mid;
		}
		else if (key < a[mid])
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}


int compare(const void* a, const void* b)
{
	const int* x = (int*)a;
	const int* y = (int*)b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;

	return 0;
}

int main()
{
	srand(time(NULL));

	std::chrono::time_point<std::chrono::steady_clock> begin;
	std::chrono::time_point<std::chrono::steady_clock> end;

	double deltaT;

	double linear = 0;
	double binary = 0;

	int key;

	long int iterations = 100;
	
	//Average Case Runtime
	std::cout << std::endl << "PART A: Average Time Complexity" << std::endl;

	InitArray();
	std::qsort(arr, size, sizeof(int), compare);

	for (int i = 0; i < iterations; i++)
	{
		key = arr[rand() % size];

		begin = std::chrono::high_resolution_clock::now();
		linearSearch(arr, size, key);
		end = std::chrono::high_resolution_clock::now();

		deltaT = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		linear += deltaT;

		begin = std::chrono::high_resolution_clock::now();
		binarySearch(arr, size, key);
		end = std::chrono::high_resolution_clock::now();

		deltaT = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		binary += deltaT;
	}

	//averaging of the summation
	linear /= iterations;
	binary /= iterations;

	std::cout << "Average Linear Search time (nanoseconds): " << linear << std::endl;
	std::cout << "Average Binary Search time (nanoseconds): " << binary << std::endl;

	linear = 0;
	binary = 0;

	//Worse Case Runtime
	std::cout << std::endl << "PART B: Worst Case Time Complexity" << std::endl;
	
	delete arr;
	InitArray();
	std::qsort(arr, size, sizeof(int), compare);

	key = 5000;

	begin = std::chrono::high_resolution_clock::now();
	linearSearch(arr, size, key);
	end = std::chrono::high_resolution_clock::now();

	deltaT = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
	linear += deltaT;

	begin = std::chrono::high_resolution_clock::now();
	binarySearch(arr, size, key);
	end = std::chrono::high_resolution_clock::now();

	deltaT = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
	binary += deltaT;

	std::cout << "Worst Case Linear Search time (nanoseconds): " << linear << std::endl;
	std::cout << "Worst Case Binary Search time (nanoseconds): " << binary << std::endl;

	//binaryTime = log(n) * stepTime
	//stepTime = binaryTime/log(n)
	std::cout << "\nBinary Search time of one step (nanoseconds): " << (binary / log2(size)) << std::endl;

	//linearTime = n * stepTime
	//stepTime = linearTime/n

	//T(n) = f(10^7) * stepTime
	std::cout << "\nWorst Case Linear Search time when size = 10^7 (nanoseconds): " << pow(10,7) * linear/size  << std::endl;
	std::cout << "Worst Case Binary Search time when size = 10^7 (nanoseconds): " << log2(pow(10,7)) * binary/log2(size) << std::endl;

	system("pause");
	return 0;
}