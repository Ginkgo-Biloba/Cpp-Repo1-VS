#include "leetcode.hpp"

/* 1. 两数之和

给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。
但是，数组中同一个元素不能使用两遍。

示例:
给定 nums = [2, 7, 11, 15], target = 9
因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]
*/

vector<int> twoSum(vector<int>& A, int T)
{
	int len = static_cast<int>(A.size());
	vector<pair<int, int>> idx;
	vector<int> R(2);
	for (int i = 0; i < len; ++i)
		idx.emplace_back(A[i], i);
	sort(idx.begin(), idx.end());
	for (int h = 0, i = len - 1; h < i;)
	{
		int d = idx[h].first + idx[i].first - T;
		if (d == 0)
		{
			R[0] = idx[h].second;
			R[1] = idx[i].second;
			break;
		}
		else if (d > 0)
			--i;
		else
			++h;
	}
	return R;
}


int main()
{
	vector<int>
		a = { 7, 2, 11, 15 };
	output(twoSum(a, 9), "Two Sum");
}
