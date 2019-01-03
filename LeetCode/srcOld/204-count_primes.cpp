#include "../src/utility.hpp"


bool isPrime(vector<int> const& primes, int n)
{
	int upper = static_cast<int>(sqrt(n + 1.0));
	size_t len = primes.size();

	for (size_t i = 0; i < len; ++i)
	{
		int check = primes[i];
		if (check > upper) return true;
		if (n % check == 0) return false;
	}

	return true;
}

/** 看答案都用的 Eratosthenes 筛选法
 * 速度比这个快，但是费空间 */
int countPrimes(int n)
{
	if (n <= 2) return 0;
	if (n == 3) return 1;

	vector<int> primes;
	primes.push_back(2);
	for (int i = 3; i < n; ++i)
	{
		if (isPrime(primes, i))
			primes.push_back(i);
	}
	return static_cast<int>(primes.size());
}



/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	int ans = countPrimes(10);
	printf("%1s: %d\n", "countPrimes", ans);
}
