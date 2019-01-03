#include <cstdio>

int func(int t, int K, int N)
{
	int ans = 0, r = 1;
	for (int i = 1; i <= K; ++i)
	{
		r *= t - i + 1;
		r /= i;
		ans += r;
		if (ans >= N) break;
	}
	return ans;
}

int superEggDrop(int K, int N)
{
	int low = 1, high = N;
	while (low < high)
	{
		int mid = (low + high) / 2;
		int upper = func(mid, K, N);
		if (upper < N)
			low = mid + 1;
		else
			high = mid;
	}
	return low;
}


int main()
{
	int const len = 4;
	int const KS[len] = { 1, 2, 3, 4 };
	int const NS[len] = { 2, 6, 14, 24 };
	for (int i = 0; i < len; i++)
	{
		printf("K = %3d, N = %3d, ", KS[i], NS[i]);
		printf("F=%3d\n", superEggDrop(KS[i], NS[i]));
	}
	return 0;
}
