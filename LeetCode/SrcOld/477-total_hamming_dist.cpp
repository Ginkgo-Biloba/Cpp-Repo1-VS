#include "leetcode.hpp"

/* 477. 汉明距离总和

两个整数的 汉明距离 指的是这两个数字的二进制数对应位不同的数量。
计算一个数组中，任意两个数之间汉明距离的总和。

示例:
输入: 4, 14, 2
输出: 6
解释: 在二进制表示中，4表示为0100，14表示为1110，2表示为0010。（这样表示是为了体现后四位之间关系）
所以答案为：
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.

注意:
		数组中元素的范围为从 0到 10^9。
		数组的长度不超过 10^4。
*/


int totalHammingDistance(vector<int> const& nums)
{
	int len = static_cast<int>(nums.size());
	int hist[33];
	memset(hist, 0, sizeof(hist));
	for (int i = 0; i < len; ++i)
	{
		unsigned cur = nums[i];
		for (int b = 31; b >= 0; --b)
		{
			hist[b] += (cur & 1U);
			cur >>= 1;
		}
	}
	for (int b = 0; b < 32; ++b)
		hist[32] += (hist[b] * (len - hist[b]));
	return hist[32];
}


int main()
{
	vector<int> nums = { 4, 14, 2 };
	OutExpr(totalHammingDistance(nums), "%d");
}
