#include "leetcode.hpp"

/* 1390. 四因数

给你一个整数数组 nums，请你返回该数组中恰有四个因数的这些整数的各因数之和。

如果数组中不存在满足题意的整数，则返回 0 。

示例：

输入：nums = [21,4,7]
输出：32
解释：
21 有 4 个因数：1, 3, 7, 21
4 有 3 个因数：1, 2, 4
7 有 2 个因数：1, 7
答案仅为 21 的所有因数的和。

提示：

	1 <= nums.length <= 10^4
	1 <= nums[i] <= 10^5
*/

class Solution
{
	int divNum(int& n)
	{
		int s = 0, c = 0;
		int q = static_cast<int>(::sqrt(n)) + 1;
		if (q * q > n)
			--q;
		for (int i = 1; i <= q; ++i)
		{
			int k = n / i;
			if (i * k == n)
			{
				++c;
				s += i;
				if (i != k)
				{
					++c;
					s += k;
				}
				if (c > 4)
				{
					c = 10;
					break;
				}
			}
		}
		n = c;
		return s;
	}

public:
	int sumFourDivisors(vector<int>& nums)
	{
		int sum = 0;
		for (int n : nums)
		{
			int s = divNum(n);
			if (n == 4)
				sum += s;
		}
		return sum;
	}
};


int main()
{
	vector<int> a = { 21, 4, 7 };
	Solution s;
	OutExpr(s.sumFourDivisors(a), "%d");
}
