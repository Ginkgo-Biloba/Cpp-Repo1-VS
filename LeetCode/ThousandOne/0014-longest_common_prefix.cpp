#include "leetcode.hpp"

/* 14. 最长公共前缀

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

示例 1:
输入: ["flower","flow","flight"]
输出: "fl"

示例 2:
输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀。

说明:
所有输入只包含小写字母 a-z 。
*/

string longestCommonPrefix(vector<string>& A)
{
	int len = static_cast<int>(A.size());
	if (len < 1)
		return string();
	int ans = static_cast<int>(A[0].length());
	for (int i = 1; i < len; ++i)
	{
		int k = 0;
		ans = min(ans, static_cast<int>(A[i].length()));
		for (; k < ans; ++k)
		{
			if (A[0][k] != A[i][k])
				break;
		}
		ans = k;
	}
	return A[0].substr(0, ans);
}

int main()
{
	vector<string>
		a = { "flower", "flow", "flight" },
		b = { "dog", "racecar", "car" };
	OutString(longestCommonPrefix(a));
	OutString(longestCommonPrefix(b));
}
