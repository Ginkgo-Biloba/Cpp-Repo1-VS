#include "../srcOld/utility.hpp"

/* 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
 * 返回符合要求的最少分割次数。。 */

 // https://leetcode.com/problems/palindrome-partitioning-ii/discuss/42212/Two-C%2B%2B-versions-given-(one-DP-28ms-one-Manancher-like-algorithm-10-ms)
 // 抄的
int minCut(string const& s)
{
	int const len = static_cast<int>(s.length());
	vector<int> cuts(len + 1);
	vector<string> ispalin(len, string(len, '\0'));

	for (int i = 0; i <= len; ++i) // 最坏情况每个字母都分割
		cuts[i] = i - 1;
	// 检查 [x, y] 是否回文
	for (int y = 1; y < len; ++y)
		for (int x = y; x >= 0; --x)
		{
			if (s[x] == s[y] && ((y - x < 2) || ispalin[x + 1][y - 1]))
			{
				ispalin[x][y] = 1;
				cuts[y + 1] = std::min(cuts[y + 1], 1 + cuts[x]);
			}
		}
	return cuts.back();
}


int main()
{
	string str = "abbab";
	int ans =minCut(str);
	printf("%s: %d\n", str.c_str(), ans);
}
