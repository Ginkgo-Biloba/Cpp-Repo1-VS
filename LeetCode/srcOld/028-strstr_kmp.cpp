#include <cstring>
#include <cstdlib>
#include <cstdio>

/* 暴力匹配，在 src 中发现 dst */
int StrStr(char const* src, char const* dst)
{
	int ld = (int)(strlen(dst)), ls = (int)(strlen(src));
	if (ld == 0) return 0; /* 不知道 0 是为什么 */
	int lsd = ls - ld;
	int i, k, ans = -1;
	for (i = 0; i <= lsd; i++)
	{
		if (src[i] == dst[0])
		{
			for (k = 1; k < ld; k++)
			{
				if (src[i + k] != dst[k])
					break;
			}
			if (k == ld)
			{ ans = i; break; }
		}
	}
	return ans;
}

/* kmp (Knuth-Morris-Pratt) 算法，参考
 * Ref: http://www.cnblogs.com/yjiyjige/p/3263858.html
 * Ref: http://blog.csdn.net/v_july_v/article/details/7041827 */
int kmp(char const* src, char const* dst)
{
	int ld = (int)(strlen(dst)), ls = (int)(strlen(src));
	if (ld == 0) return 0; /* 不知道 0 是为什么*/
	if (ls < ld) return -1;

	/* dst 的 next 数组 */
	int* nextd = (int*)(malloc(sizeof(int) * ld));
	int iL = -1, iR = 0;
	nextd[0] = -1;
	while (iR < ld - 1)
	{
		/* 短路求值不会比较 dst[-1] */
		if (iL == -1 || dst[iL] == dst[iR])
		{
			iL++; iR++;
			nextd[iR] = iL;
		}
		else
			iL = nextd[iL];
	}

	/* 匹配 */
	int iS = 0, iD = 0;
	while (iS < ls && iD < ld)
	{
		/* 有相同字符串或匹配为空，都前移 */
		if (iD == -1 || src[iS] == dst[iD])
		{ ++iS; ++iD; }
		else
			iD = nextd[iD]; /* 只回溯到 iD */
	}

	free(nextd);
	if (iD == ld) return (iS - iD);
	else return -1;
}

int main()
{
	char const* src = "Hello, world!";
	char const* dst1 = "wo";
	char const* dst2 = "wr";
	int d1 = kmp(src, dst1);
	int d2 = kmp(src, dst2);
	fprintf(stdout, "src1: %s\ndst1: %s\ndst2: %s\n", src, dst1, dst2);
	fprintf(stdout, "%d, %d\n", d1, d2);
	return 0;
}