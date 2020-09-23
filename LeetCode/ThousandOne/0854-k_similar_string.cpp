#include "leetcode.hpp"

/* 854. 相似度为 K 的字符串

如果可以通过将 A 中的两个小写字母精确地交换位置 K 次得到与 B 相等的字符串，我们称字符串 A 和 B 的相似度为 K（K 为非负整数）。

给定两个字母异位词 A 和 B ，返回 A 和 B 的相似度 K 的最小值。

示例 1：
输入：A = "ab", B = "ba"
输出：1

示例 2：
输入：A = "abc", B = "bca"
输出：2

示例 3：
输入：A = "abac", B = "baca"
输出：2

示例 4：
输入：A = "aabc", B = "abca"
输出：2

提示：
	1 <= A.length == B.length <= 20
	A 和 B 只包含集合 {'a', 'b', 'c', 'd', 'e', 'f'} 中的小写字母。
*/

// https://leetcode.com/problems/k-similar-strings/discuss/140099/JAVA-BFS-32-ms-cleanconciseexplanationwhatever
// 抄的

string swap(string const& s, int i, int k)
{
	string t = s;
	t[i] = s[k];
	t[k] = s[i];
	return t;
}

int kSimilarity(string const& A, string const& B)
{
	if (A == B)
		return 0;
	int ans = 0;
	int len = static_cast<int>(A.size());
	vector<string> q;
	std::set<string> v; // 是否访问过
	q.push_back(A);
	v.insert(A);
	for (size_t idx = 0; idx < q.size();)
	{
		size_t ito = q.size();
		++ans;
		for (; idx < ito; ++idx)
		{
			string cur = q[idx];
			int i = 0;
			while (i < len && cur[i] == B[i])
				++i;
			for (int k = i + 1; k < len; ++k)
				if (cur[k] == B[i] && cur[k] != B[k])
				{
					string nxt = swap(cur, i, k);
					if (nxt == B)
						return ans;
					if (v.find(nxt) == v.end())
					{
						q.push_back(nxt);
						v.insert(nxt);
					}
				}
		}
	}
	return ans;
}


int main()
{
	OutExpr(kSimilarity("ab", "ba"), "%d");
	OutExpr(kSimilarity("abc", "bca"), "%d");
	OutExpr(kSimilarity("abac", "baca"), "%d");
	OutExpr(kSimilarity("aabc", "abca"), "%d");
}
