#include "../src/utility.hpp"

int core(vector<int>& hs, int n)
{
	if (n == 0 || n == 1)
		return 1;
	if (hs[n] != -1)
		return hs[n];
	int res = 0;
	for (int i = 0; i < n; i++)
	{
		res += core(hs, i) * core(hs, n - i - 1);
	}
	hs[n] = res;
	return res;
}

int numTrees(int n)
{
	vector<int> hs(n + 1, -1);
	return core(hs, n);
}


int main()
{
	for (int i = 1; i < 20; ++i)
	{
		int ans = numTrees(i);
		printf("%1s: %2d = %d\n", "numTrees", i, ans);
	}
}
