#include "leetcode.hpp"

/* 923. 三数之和的多种可能

给定一个整数数组 A，以及一个整数 target 作为目标值，返回满足 i < j < k 且 A[i] + A[j] + A[k] == target 的元组 i, j, k 的数量。

由于结果会非常大，请返回 结果除以 10^9 + 7 的余数。

示例 1：
输入：A = [1,1,2,2,3,3,4,4,5,5], target = 8
输出：20
解释：
按值枚举（A[i]，A[j]，A[k]）：
(1, 2, 5) 出现 8 次；
(1, 3, 4) 出现 8 次；
(2, 2, 4) 出现 2 次；
(2, 3, 3) 出现 2 次。

示例 2：
输入：A = [1,1,2,2,2,2], target = 5
输出：12
解释：
A[i] = 1，A[j] = A[k] = 2 出现 12 次：
我们从 [1,1] 中选择一个 1，有 2 种情况，
从 [2,2,2,2] 中选出两个 2，有 6 种情况。

提示：
	3 <= A.length <= 3000
	0 <= A[i] <= 100
	0 <= target <= 300
*/

int threeSumMulti(vector<int>& A, int target)
{
	int64_t const Mod = 1e9 + 7;
	int64_t sum = 0;
	vector<pair<int, int>> B;
	pair<int, int> prev(-1, 0);

	sort(A.begin(), A.end());
	for (int a : A)
	{
		if (a == prev.first)
			prev.second += 1;
		else
		{
			B.push_back(prev);
			prev.first = a;
			prev.second = 1;
		}
	}
	B.push_back(prev);

	int len = static_cast<int>(B.size());
	// x = 1 跳过前面那个 -1
	for (int x = 1; x < len; ++x)
	{
		if (B[x].first * 2 > target)
			break;
		for (int y = x; y < len; ++y)
		{
			prev.first = target - B[x].first - B[y].first;
			prev.second = 0;
			if (prev.first < 0)
				break;
			auto it = lower_bound(B.begin() + y, B.end(), prev);
			int z = static_cast<int>(it - B.begin());
			if ((z < len) && (B[z].first == prev.first))
			{
				int64_t z64 = B[z].second;
				if (z != y)
				{
					// 1, 2, 3
					if (x != y)
						sum += z64 * B[x].second * B[y].second;
					// 1, 1, 2
					else
						sum += z64 * B[x].second * (B[x].second - 1) / 2;
				}
				else
				{
					// 1, 2, 2
					if (x != y)
						sum += z64 * (z64 - 1) * B[x].second / 2;
					// 1, 1, 1
					else
						sum += z64 * (z64 - 1) * (z64 - 2) / 6;
				}
				sum %= Mod;
			}
		}
	}

	return static_cast<int>(sum);
}

int main()
{
	vector<int>
		a = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 },
		b = { 1, 1, 2, 2, 2, 2 },
		c = { 0, 0, 0 },
		d = { 3, 3, 0, 0, 3, 2, 2, 3 };

	OutExpr(threeSumMulti(d, 6), "%d");
	OutExpr(threeSumMulti(a, 8), "%d");
	OutExpr(threeSumMulti(b, 5), "%d");
	OutExpr(threeSumMulti(c, 0), "%d");
}
