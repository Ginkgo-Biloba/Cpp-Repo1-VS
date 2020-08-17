#include "leetcode.hpp"

/*


*/

int minSwaps(vector<vector<int>>& grid)
{
	int len = static_cast<int>(grid.size());
	vector<int> A(len);
	for (int h = 0; h < len; ++h)
		for (int w = len - 1; w >= 0; --w)
		{
			if (grid[h][w])
				break;
			++(A[h]);
		}

	int ans = 0;
	for (int i = 0; i < len; ++i)
	{
		int need = len - 1 - i;
		if (A[i] >= need)
			continue;
		int j = i + 1;
		for (; j < len; ++j)
		{
			if (A[j] >= need)
				break;
		}
		if (j == len)
			return -1;
		ans += j - i;
		for (; j > i; --j)
			A[j] = A[j - 1];
	}
	return ans;
}

int main()
{
	vector<vector<int>>
		a = { { 0, 0, 1 }, { 1, 1, 0 }, { 1, 0, 0 } },
		b = { { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 } },
		c = { { 1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 } };
	OutExpr(minSwaps(a), "%d");
	OutExpr(minSwaps(b), "%d");
	OutExpr(minSwaps(c), "%d");
}
