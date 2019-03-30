#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

/* 两数之和为给定值
描述：给定一个整数数组和一个值target，求两个下标i、j，使得a[i] + a[j] = target，返回下标 */
std::vector<int> sum2(std::vector<int> const& nums, int target)
{
	int i, k, val, len = static_cast<int>(nums.size());
	std::vector<int> ans; ans.reserve(2u);
	std::vector<std::pair<int, int>> A;
	A.reserve(nums.size());
	for (i = 0; i < len; i++)
		A.emplace_back(nums[i], i);
	std::sort(A.begin(), A.end(), std::less<std::pair<int, int>>());

	i = 0; k = len - 1;
	while (i < k)
	{
		val = A[i].first + A[k].first;
		if (val == target)
		{
			ans.push_back(A[i].second);
			ans.push_back(A[k].second);
			break;
		}
		else if (val < target) i++;
		else k--;
	}
	return ans;
}

int main()
{
	std::vector<int> vec {3, 2, 4};
	std::vector<int> ans = sum2(vec, 6);
	std::cout << ans[0] << ", " << ans[1] << "\n";
	return 0;
}
