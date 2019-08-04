#include "leetcode.hpp"


// dp[i] 存储的是 str[0:i) 能解码的方式数量
bool search(int* nums, int n, int val)
{
	if (n <= 0) return false;
	int iL = 0, iR = n - 1, iM;
	while (iL < iR)
	{
		iM = iL + ((iR - iL) / 2); /* 累不累 */
		if (nums[iM] == val) return true;

		/* [iL, iM] 有序，普通查找，iM 向下取整，可能等于 iL */
		if (nums[iL] < nums[iM])
		{
			/* (在 / 不在) [iL, iM] 内 */
			if (nums[iL] <= val && val < nums[iM])
				iR = iM - 1;
			else
				iL = iM + 1;
		}
		else if (nums[iM] < nums[iR]) /* [iM, iR] 有序 */
		{
			/* (在 / 不在) [iM, iR] 内 */
			if (nums[iM] < val && val <= nums[iR])
				iL = iM + 1;
			else
				iR = iM - 1;
		}
		else /* 不能判断，退化为 O(N) */
		{
			if (nums[iR] == val)
				return true;
			else
			--iR;
		}
	}
	if (nums[iL] == val) return true;
	else return false;
}

int main()
{
	int nums[] = { 1, 3, 1, 1, 1 };
	bool ans = search(nums, static_cast<int>(sizeof(nums) / sizeof(int)), 3);;
	printf("%1s = %s\n", "numDecodings", (ans ? "true" : "false"));
}
