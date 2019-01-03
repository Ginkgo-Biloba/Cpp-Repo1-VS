#include <cstdio>
#include <cstdlib>
#include <cstring>

int findRotArray(int const* nums, int const& n, int const& val)
{
	if (n <= 0) return -1;
	int iL = 0, iR = n - 1, iM;
	while (iL < iR)
	{
		iM = iL + ((iR - iL) >> 1); /* 累不累 */
		if (nums[iM] == val) return iM;

		/* [iL, iM] 有序，普通查找，iM 向下取整，可能等于 iL */
		if (nums[iL] <= nums[iM])
		{
			/* (在 / 不在) [iL, iM] 内 */
			if (nums[iL] <= val && val < nums[iM])
				iR = iM - 1;
			else
				iL = iM + 1;
		}
		else /* 无序，说明 [iM, iR] 有序 */
		{
			/* (在 / 不在) [iM, iR] 内 */
			if (nums[iM] < val && val <= nums[iR])
				iL = iM + 1;
			else
				iR = iM - 1;
		}
	}
	if (nums[iL] == val) return iL;
	else return -1;
}

int main()
{
	int nums[10] = { 3, 1 };
	int ans = findRotArray(nums, 2, 1);
	fprintf(stdout, "%d\n", ans);
	return 0;
}