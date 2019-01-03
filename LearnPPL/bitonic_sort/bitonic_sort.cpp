// https://msdn.microsoft.com/zh-cn/library/dd728066.aspx

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cstdint>

#include <Windows.h>
#include <ppl.h>
using namespace concurrency;

bool const increasing = true;
bool const decreasing = !increasing;


template<class Func>
uint32_t timeCall(Func&& func)
{
	uint32_t begin = GetTickCount();
	func();
	return GetTickCount() - begin;
}


// 比较函数，用于双调排序
template<class T>
void compare(T* ptr, int i, int j, bool dir)
{
	if (dir == (ptr[i] > ptr[j]))
		std::swap(ptr[i], ptr[j]);
}

// 合并一个序列，使用指定的顺序
template<class T>
void bitonicMerge(T* ptr, int low, int num, bool dir)
{
	if (num > 1)
	{
		int half = num / 2;
		for (int i = low; i < low + half; ++i)
			compare(ptr, i, i + half, dir);
		bitonicMerge(ptr, low, half, dir);
		bitonicMerge(ptr, low + half, half, dir);
	}
}

// 使用指定的顺序，排序给定的序列
template<class T>
void bitonicSort(T* ptr, int low, int num, bool dir)
{
	if (num > 1)
	{
		// 分割数组到两部分，并且使用不同的顺序排序它们
		int half = num / 2;
		bitonicSort(ptr, low, half, increasing);
		bitonicSort(ptr, low + half, half, decreasing);

		// 合并结果
		bitonicMerge(ptr, low, num, dir);
	}
}

// 对给定的数组递增排序
template<class T>
void bitonicSort(T* ptr, int size)
{
	bitonicSort(ptr, 0, size, increasing);
}


// 并行双调排序
template<class T>
void parallelBitonicMerge(T* ptr, int low, int num, bool dir)
{
	// 并行合并序列，如果任务量总够多
	if (num > 500)
	{
		int half = num / 2;
		for (int i = low; i < low + half; ++i)
			compare(ptr, i, i + half, dir);

		// 合并序列
		parallel_invoke(
			[&ptr, low, half, dir]() -> void { parallelBitonicMerge(ptr, low, half, dir); },
			[&ptr, low, half, dir]() -> void { parallelBitonicMerge(ptr, low + half, half, dir); }
		);
	}
	else if (num > 1)
		bitonicMerge(ptr, low, num, dir);
}

template<class T>
void parallelBitonicSort(T* ptr, int low, int num, bool dir)
{
	if (num > 1)
	{
		int half = num / 2;

		parallel_invoke(
			[&ptr, low, half]() -> void { parallelBitonicSort(ptr, low, half, increasing); },
			[&ptr, low, half]() -> void { parallelBitonicSort(ptr, low + half, half, increasing); }
		);

		parallelBitonicMerge(ptr, low, num, dir);
	}
}

template<class T>
void parallelBitonicSort(T* ptr, int size)
{
	parallelBitonicSort(ptr, 0, size, increasing);
}


int wmain()
{
	int const size = 0x200000; // 数量需要是 2 的幂

	unsigned* a1 = static_cast<unsigned*>(malloc(size * sizeof(unsigned)));
	unsigned* a2 = static_cast<unsigned*>(malloc(size * sizeof(unsigned)));

	uint32_t elapsed;
	std::mt19937 gen(42);
	for (int i = 0; i < size; ++i)
		a1[i] = a2[i] = gen();

	elapsed = timeCall([a2, size]() -> void { parallelBitonicSort(a2, size); });
	// elapsed = timeCall([a2, size]() -> void { parallel_sort(a2, a2 + size); });
	std::wcout << L"parallel time: " << elapsed << std::endl;

	elapsed = timeCall([a1, size]() -> void { bitonicSort(a1, size); });
	// elapsed = timeCall([a1, size]() -> void { std::sort(a1, a1 + size); });
	std::wcout << L"serial time: " << elapsed << std::endl;

	free(a1); free(a2);
}


