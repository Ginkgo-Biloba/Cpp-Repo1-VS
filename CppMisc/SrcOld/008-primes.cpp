#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
// 32 位比 64 位快
// 不过 ullong 能存下的质数个数会超过 4G

typedef unsigned long long ullong;

void getPrimes(std::vector<ullong>& nums, ullong upper)
{
	if (upper < 2u) return;

	nums.clear(); nums.reserve(2048u);
	nums.push_back(2u);
	for (ullong cur = 3u; cur < upper; cur += 2u)
	{
		ullong sqrtCur = static_cast<ullong>(sqrt(cur)) + 1u;
		size_t count = static_cast<size_t>(
			std::lower_bound(nums.begin(), nums.end(), sqrtCur) - nums.begin());

		bool isPrime = true;
		for (size_t i = 0; isPrime && (i < count); ++i)
			isPrime = isPrime && (cur % nums[i]);

		if (isPrime)
			nums.push_back(cur);
	}
}


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	char const split[] = "----------------------------------------"
		"----------------------------------------\n";
	size_t const cols = 1000u; // 一次缓冲这么多个
	char buffer[25u * cols]; // ULLONG_MAX 最长 20 位
	std::vector<ullong> primes;
	ullong lower = 0, upper = 65536u;

	int t1 = static_cast<int>(clock());
	if (argc > 1)
		sscanf(argv[1], "%llu", &upper);
	getPrimes(primes, upper);

	int t2 = static_cast<int>(clock());
	std::cout << split;
	size_t const count = primes.size();
	size_t start, stop = 0;
	if (argc > 2) // 只输出大于等于这个数的质数
		sscanf(argv[2], "%llu", &lower);
	stop = static_cast<size_t>(
		std::lower_bound(primes.begin(), primes.end(), lower)
		- primes.begin());

	while (stop < count)
	{
		size_t pos = 0;

		start = stop; stop += cols;
		if (stop > count) stop = count;
		for (; start < stop; ++start)
		{
			int l = sprintf(buffer + pos, "%llu, ", primes[start]);
			if (l < 0) break; // 写入发生错误
			pos += static_cast<size_t>(l);
		}
		std::cout << buffer;
	}

	int t3 = static_cast<int>(clock());
	sprintf(buffer,
		"\n%s\n"
		"there exist %llu prime(s) in [2, %llu)\n"
		"getPrimes: %.3f ms; output: %.3f ms\n\n",
		split, static_cast<ullong>(count), upper,
		static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1e3,
		static_cast<double>(t3 - t2) / CLOCKS_PER_SEC * 1e3);
	std::cout << buffer;
}

