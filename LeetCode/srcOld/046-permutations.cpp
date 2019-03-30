#include <vector>
#include <iostream>
#include <algorithm>
typedef std::vector<int> vecint;

std::vector<vecint> permutation(vecint& nums)
{
	int len = static_cast<int>(nums.size());
	std::sort(nums.begin(), nums.end());
	std::vector<vecint> ans;
	ans.reserve(len * len);  ans.push_back(nums);
	if (len < 1) return ans;
	int q, r; int c;

	while (true)
	{
		/* 从后往前找 nums[q - 1] < nums[q] */
		/* 没有则说明整个字符串倒序，所以全部反转 */
		for (q = len - 1; q > 0; q--)
		{
			if (nums[q - 1] < nums[q])
				break;
		}

		/* 找最后一个 r 使得 nums[r] > nums[q - 1] */
		if (q > 0)
		{
			c = nums[q - 1];
			for (r = len - 1; r > q; r--)
			{
				if (nums[r] > c)
					break;
			}
			/* 交换 */
			nums[q - 1] = nums[r]; nums[r] = c;
		}
		else break;

		/* 反转 [q, len - 1] */
		r = len - 1;
		while (q < r)
		{
			c = nums[q]; nums[q] = nums[r]; nums[r] = c;
			q++; r--;
		}

		/* 记录 */
		ans.push_back(nums);
	}
	return ans;
}


int main()
{
	vecint nums{1, 2, 3};
	std::vector<vecint> ans = permutation(nums);
	for (vecint const& vi : ans)
	{
		for (int const& i : vi)
			std::cout << i << ' ';
		std::cout << '\n';
	}
	return 0;
}
