#include "leetcode.hpp"

/* 60. 第k个排列

给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。

按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
	"123"
	"132"
	"213"
	"231"
	"312"
	"321"

给定 n 和 k，返回第 k 个排列。

说明：
	给定 n 的范围是 [1, 9]。
	给定 k 的范围是[1,  n!]。

示例 1:
输入: n = 3, k = 3
输出: "213"

示例 2:
输入: n = 4, k = 9
输出: "2314"
*/

// https://leetcode.com/problems/permutation-sequence/discuss/22507/%22Explain-like-I'm-five%22-Java-Solution-in-O(n)
// 抄的
string getPermutation(int n, int k)
{
	vector<int> A(n), frac(n + 1);
	string s;

	frac[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		A[i - 1] = i;
		frac[i] = frac[i - 1] * i;
	}

	--k;
	for (int i = n - 1; i >= 0; --i)
	{
		int p = k / frac[i];
		k -= p * frac[i];
		s.push_back(static_cast<char>(A[p] + '0'));
		A.erase(A.begin() + p);
	}
	return s;
}


int main()
{
	OutString(getPermutation(3, 3));
	OutString(getPermutation(4, 9));
	OutString(getPermutation(9, 234));
}
