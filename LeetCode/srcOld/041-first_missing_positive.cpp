#include <cstdio>
#include <cstdlib>
#include <cmath>

/* 让 O(N) 时间发现，使用位置置换 */
int firstMissingPositive(int* nums, int len)
{
	int val, i, l1 = len + 1;
	/* 处理非正数和大于 len 的数，因为答案肯定不是它们 */
	for (i = 0; i < len; i++)
	{
		if (nums[i] < 1 || nums[i] > len)
			nums[i] = l1;
	}
	/* 把每个整数应该在的位置上的数设为负数 */
	for (i = 0; i < len; i++)
	{
		val = abs(nums[i]);
		if(val == l1) continue;
		if (nums[val - 1] > 0) nums[val - 1] = -nums[val - 1];
	}
	/* 最后没有被设为负数的索引对应的数就是缺少的数 */
	for (i = 0; i < len; i++)
		if (nums[i] > 0)
			break;

	return (i + 1);
}

int main()
{
	int nums[] = { 3, 4, -1, 1 };
	int len = (int)(sizeof(nums) / sizeof(nums[0]));
	int ans = firstMissingPositive(nums, len);
	fprintf(stdout, "%d\n", ans);
	return 0;
}