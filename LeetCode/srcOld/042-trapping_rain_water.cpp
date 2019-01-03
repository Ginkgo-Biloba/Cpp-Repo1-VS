#include <cstdlib>
#include <cstdio>
#include <cstring>

int trap(int* hs, int sz)
{
	int ans = 0;
	if (sz < 2) return ans;
	int iL = 0, iR = sz - 1, maxL = 0, maxR = 0;
	while (iL < iR)
	{
		/* 左边小，先算左边的 */
		if (hs[iL] <= hs[iR])
		{
			/* 等于的时候没有落差，不能存水 */
			if (hs[iL] >= maxL) maxL = hs[iL];
			else ans += (maxL - hs[iL]);
			iL++;
		}
		else
		{
			if (hs[iR] >= maxR) maxR = hs[iR];
			else ans += (maxR - hs[iR]);
			iR--;
		}
	}
	return ans;
}



int main()
{
	int hs[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
	int sz = (int)(sizeof(hs) / sizeof(hs[0]));
	int ans = trap(hs, sz);
	fprintf(stdout, "%d\n", ans);
	return 0;
}