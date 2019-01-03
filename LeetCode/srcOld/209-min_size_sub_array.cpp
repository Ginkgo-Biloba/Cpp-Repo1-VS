#include "../src/utility.hpp"

int minSubArrayLen(int target, vector<int>& nums)
{
	int prev, minlen, val = 0, i = 0;
	int len = static_cast<int>(nums.size());

	for (; i < len; ++i)
	{
		val += nums[i];
		if (val >= target)
			break;
	}
	if (val < target)
		return 0;

	prev = 0; minlen = i + 1;
	val -= nums[i];
	for (; i < len; ++i)
	{
		int curval = val + nums[i];
		while (curval >= target)
		{
			curval -= nums[prev];
			++prev;
		}
		--prev;
		val = curval + nums[prev];
		int curlen = i - prev + 1;
		if (curlen < minlen)
			minlen = curlen;
	}
	return minlen;
}


/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	vector<int> nums = { 1, 2, 3, 4, 5 };
	int ans = minSubArrayLen(11, nums);
	printf("%1s: %d\n", "minSubArrayLen", ans);
}
