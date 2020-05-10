#include "leetcode.hpp"

/* 97. 交错字符串

给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。

示例 1:
输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出: true

示例 2:
输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
输出: false
*/

class Solution
{
	vector<char> buffer;
	int dim;

	char& dp(int a, int b)
	{
		return buffer[a * dim + b];
	}

public:
	bool isInterleave(string s1, string s2, string s3)
	{
		int n1 = static_cast<int>(s1.length());
		int n2 = static_cast<int>(s2.length());
		int n3 = static_cast<int>(s3.length());
		if (n1 + n2 != n3)
			return false;
		dim = n2 + 1;
		buffer.assign((n1 + 1) * dim, 0);
		char(*view)[6] = reinterpret_cast<char(*)[6]>(buffer.data());
		(void)(view);
		dp(0, 0) = 1;
		for (int b = 1; b <= n2; ++b)
			dp(0, b) = dp(0, b - 1) && (s2[b - 1] == s3[b - 1]);
		for (int a = 1; a <= n1; ++a)
		{
			dp(a, 0) = dp(a - 1, 0) && (s1[a - 1] == s3[a - 1]);
			for (int b = 1; b <= n2; ++b)
			{
				if (s3[a + b - 1] == s1[a - 1])
					dp(a, b) = dp(a, b) || dp(a - 1, b);
				if (s3[a + b - 1] == s2[b - 1])
					dp(a, b) = dp(a, b) || dp(a, b - 1);
			}
		}
		return static_cast<bool>(dp(n1, n2));
	}
};


int main()
{
	Solution s;
	OutBool(s.isInterleave("aabcc", "dbbca", "aadbbcbcac"));
	OutBool(s.isInterleave("aabcc", "dbbca", "aadbbbaccc"));
}
