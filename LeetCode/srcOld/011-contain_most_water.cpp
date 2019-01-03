#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

/* 找到两条线，它们与 X 轴围成的面积最大 */
int maxArea(int* hs, int num)
{
	int i = 0, j = num - 1;
	int ans = 0, cur = 0;
	/* ????? */
	while (i < j)
	{
		if (hs[i] < hs[j])
		{
			cur = hs[i] * (j - i); i++;
			if (ans < cur) ans = cur;
		}
		else
		{
			cur = hs[j] * (j - i); j--;
			if (ans < cur) ans = cur;
		}
	}
	return ans;
}

int main()
{
	int num = 1, area;
	int* hs = (int*)(malloc(sizeof(int) * 1024));
	while (true)
	{
		fscanf(stdin, " %d", &num);
		if (num < 2 || 1023 < num) break;
		for (area = 0; area < num; area++)
			fscanf(stdin, " %d", hs + area);
		area = maxArea(hs, num);
		fprintf(stdout, "%d\n", area);
	}
	free(hs);
	return 0;
}