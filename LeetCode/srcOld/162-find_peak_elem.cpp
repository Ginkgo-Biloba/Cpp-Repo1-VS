#include "leetcode.hpp"

/** 假定 nums[-1] = nums[n] = -\infinify */
int findPeakElement(vector<int>& nums)
{
	int const len = static_cast<int>(nums.size());
	if (len == 1) return 0;
	if (len == 2) return (nums[0] > nums[1] ? 0 : 1);

	int l = 0, r = len - 1;
	while (l < r)
	{
		int m = (l + r) / 2;
		if (m != 0)
		{
			if (nums[m - 1] < nums[m] && nums[m] > nums[m + 1])
				l = r = m; // 出循环
			else if (nums[m - 1] < nums[m] && nums[m] < nums[m + 1])
				l = m + 1;
			else
				r = m;
		}
		else
		{
			if (nums[0] < nums[1])
				l = r = 1; // 出循环
			else
				l = r = 0; // 出循环
		}
	}

	return l;
}


/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	vector<int> nums = { 1, 2, 1, 3, 5, 6, 4 };
	int ans = findPeakElement(nums);
	printf("%1s = %d (idx = %d)\n",
		"findPeakElement", nums[ans], ans);
}
