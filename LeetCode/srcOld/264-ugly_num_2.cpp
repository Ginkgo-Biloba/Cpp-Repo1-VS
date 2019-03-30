#include "../srcOld/utility.hpp"

int nthUglyNumber(int n)
{
	// 抄的
	if (n == 1) return 1;
	int t2 = 0, t3 = 0, t5 = 0;
	std::vector<int> k(n);
	k[0] = 1;
	for (int i = 1; i < n; i++)
	{
		int u2 = k[t2] * 2, u3 = k[t3] * 3, u5 = k[t5] * 5;
		k[i] = std::min(std::min(u2, u3), u5);
		if (k[i] == u2) t2++;
		if (k[i] == u3) t3++;
		if (k[i] == u5) t5++;
	}
	return k[n - 1];
}

int main()
{
	int n = nthUglyNumber(10);
	printf("nthUglyNumber: %d\n", n);
}
