#include "leetcode.hpp"

/* 410. 分割数组的最大值

给定一个非负整数数组和一个整数 m，你需要将这个数组分成 m 个非空的连续子数组。设计一个算法使得这 m 个子数组各自和的最大值最小。

注意:
数组长度 n 满足以下条件:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)

示例:

输入:
nums = [7,2,5,10,8]
m = 2
输出:
18

解释:
一共有四种方法将nums分割为2个子数组。
其中最好的方式是将其分为[7,2,5] 和 [10,8]，
因为此时这两个子数组各自的和的最大值为 18，在所有情况中最小。
*/

// 抄的
class Solution
{
	int* ptr;
	int len, seg;
	int64_t left, right;

	bool canSplit(int64_t mid)
	{
		int count = 1;
		int64_t acml = ptr[0];
		for (int i = 1; i < len; ++i)
		{
			acml += ptr[i];
			if (acml > mid)
			{
				++count;
				if (count > seg)
					return false;
				acml = ptr[i];
			}
		}
		return true;
	}

public:
	int splitArray(vector<int>& nums, int m)
	{
		ptr = nums.data();
		len = static_cast<int>(nums.size());
		if (len == 0) return 0;
		if (len == 1) return nums[0];

		seg = m;
		left = right = 0;
		for (int i = 0; i < len; ++i)
		{
			int64_t cur = nums[i];
			left = std::max(left, cur);
			right += cur;
		}

		if (seg < 1)
			return static_cast<int>(right);
		if (seg >= len)
			return static_cast<int>(left);

		while (left < right)
		{
			int64_t mid = (left + right) / 2;
			if (canSplit(mid))
				right = mid;
			else
				left = mid + 1;
		}

		return static_cast<int>(left);
	}
};


int main()
{
	vector<int> nums = { 7, 2, 5, 10, 8 };
	OutExpr(Solution().splitArray(nums, 2), "%d");
}

