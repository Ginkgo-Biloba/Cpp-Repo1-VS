#include "leetcode.hpp"

/* 839. 相似字符串组

如果我们交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。

例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。

总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。

我们给出了一个不包含重复的字符串列表 A。列表中的每个字符串都是 A 中其它所有字符串的一个字母异位词。请问 A 中有多少个相似字符串组？

示例：
输入：["tars","rats","arts","star"]
输出：2

提示：
		A.length <= 2000
		A[i].length <= 1000
		A.length * A[i].length <= 20000
		A 中的所有单词都只包含小写字母。
		A 中的所有单词都具有相同的长度，且是彼此的字母异位词。
		此问题的判断限制时间已经延长。
备注：
	字母异位词[anagram]，一种把某个字符串的字母的位置（顺序）加以改换所形成的新词。
*/

bool is_similar(string const& x, string const& y)
{
	int d = 0;
	size_t slen = x.size();
	for (size_t i = 0; i < slen; ++i)
		if (x[i] != y[i])
		{
			++d;
			if (d > 2)
				return false;
		}
	return true;
}

int numSimilarGroups(vector<string>& A)
{
	int alen = static_cast<int>(A.size());
	if (alen < 2)
		return 0;
	vector<int> parent(alen, 0);
	for (int i = 0; i < alen; ++i)
		parent[i] = i;

	for (int x = 0; x < alen; ++x)
		for (int y = x + 1; y < alen; ++y)
			if (is_similar(A[x], A[y]))
			{
				int xp = parent[x];
				int yp = parent[y];
				while (parent[xp] != xp) xp = parent[xp];
				while (parent[yp] != yp) yp = parent[yp];
				int t = std::min(xp, yp);
				parent[x] = parent[y] = parent[xp] = parent[yp] = t;
			}

	int s = 0;
	for (int i = 0; i < alen; ++i)
	{
		if (parent[i] == i)
			++s;
	}
	return s;
}


int main()
{
	vector<string>
		a = { "tars", "rats", "arts", "star" },
		b =
	{
		"ufixvnxsdxalinayfaappbmmj",
		"nxpxiaauvyjxasbfmfinmdpla",
		"ujimiyxsaxpavnanfapmlbxdf",
		"ufimvyxsaxpainanfapdlbxmj",
		"nxpyajaumxixalbfvpdnmasfi",
		"nxpxiaauvyjxpsbfmfinmdala",
		"ufimvyxspxaainanfapdlbxmj",
		"nxpyaiaumxjxapbfvlanmdsfi",
		"ufimvyxspxapinanfaadlbxmj",
		"nxpyaaauvxjxasbfmfinmdpli",
		"nxpyajaumxixapbfvlanmdsfi",
		"nxpyaaaumxjxasbfvfinmdpli",
		"ufixvnbsdxalinayfamppxamj",
		"ujimvyxsaxpainanfapdlbxmf",
		"ufixvyxsdxalinanfaappbmmj",
		"nxpyaaaumxjxapbfvlinmdsfi",
		"ufixvyxspxalinanfaadpbmmj",
		"nxpyaaaumxjxasbfvlinmdpfi",
		"ufixvyxspxapinanfaadlbmmj",
		"ufixvnbsdxalinayfaappxmmj",
		"ufiavnbsdxxlinayfamppxamj",
		"nxpyajaumxixapbfvldnmasfi",
		"ufiavnbsdxxlinayfamppxajm",
		"nxpyiaauvxjxasbfmfinmdpla",
		"ujimiyxsaxpavnanfapdlbxmf",
	};
	OutExpr(numSimilarGroups(a), "%d");
	OutExpr(numSimilarGroups(b), "%d");
}
