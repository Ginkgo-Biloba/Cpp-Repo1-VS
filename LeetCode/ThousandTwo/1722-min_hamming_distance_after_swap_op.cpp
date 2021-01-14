#include "leetcode.hpp"

/* 1722. 执行交换操作后的最小汉明距离

给你两个整数数组 source 和 target ，长度都是 n 。
还有一个数组 allowedSwaps ，其中每个 allowedSwaps[i] = [ai, bi] 表示你可以交换数组 source 中下标为 ai 和 bi（下标从 0 开始）的两个元素。
注意，你可以按 任意 顺序 多次 交换一对特定下标指向的元素。

相同长度的两个数组 source 和 target 间的 汉明距离 是元素不同的下标数量。
形式上，其值等于满足 source[i] != target[i] （下标从 0 开始）的下标 i（0 <= i <= n-1）的数量。

在对数组 source 执行 任意 数量的交换操作后，返回 source 和 target 间的 最小汉明距离 。

示例 1：
输入：source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
输出：1
解释：source 可以按下述方式转换：
- 交换下标 0 和 1 指向的元素：source = [2,1,3,4]
- 交换下标 2 和 3 指向的元素：source = [2,1,4,3]
source 和 target 间的汉明距离是 1 ，二者有 1 处元素不同，在下标 3 。

示例 2：
输入：source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
输出：2
解释：不能对 source 执行交换操作。
source 和 target 间的汉明距离是 2 ，二者有 2 处元素不同，在下标 1 和下标 2 。

示例 3：
输入：source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
输出：0

提示：
	n == source.length == target.length
	1 <= n <= 10^5
	1 <= source[i], target[i] <= 10^5
	0 <= allowedSwaps.length <= 10^5
	allowedSwaps[i].length == 2
	0 <= ai, bi <= n - 1
	ai != bi
*/

class Solution
{
	int len;
	vector<int> par, buf;

	int find(int x)
	{
		while (x != par[x])
		{
			buf.push_back(x);
			x = par[x];
		}
		for (int i : buf)
			par[i] = x;
		buf.clear();
		return x;
	}

	void merge(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x != y)
			par[max(x, y)] = min(x, y);
	}

	int proc(vector<int>& A, vector<int>& B, vector<int>& C)
	{
		int num = static_cast<int>(C.size());
		int ans = 0, ia = 0, ib = 0;
		vector<int> a, b;
		for (int i : C)
		{
			a.push_back(A[i]);
			b.push_back(B[i]);
		}
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		for (; ia < num; ++ia)
		{
			while (ib < num && b[ib] < a[ia])
				++ib;
			if (ib < num && a[ia] == b[ib])
				++ib;
			else
				++ans;
		}
		return ans;
	}

public:
	int minimumHammingDistance(vector<int>& A, vector<int>& B, vector<vector<int>>& S)
	{
		vector<vector<int>> C;
		len = static_cast<int>(A.size());
		par.resize(len);
		buf.reserve(len);
		C.resize(len);
		for (int i = 0; i < len; ++i)
			par[i] = i;
		for (auto& s : S)
			merge(s[0], s[1]);
		for (int i = 0; i < len; ++i)
		{
			int j = find(i);
			C[j].push_back(i);
		}
		int dist = 0;
		for (auto& c : C)
		{
			if (c.size())
				dist += proc(A, B, c);
		}
		return dist;
	}
};


int main()
{
	vector<int>
		a = { 1, 2, 3, 4 },
		b = { 2, 1, 4, 5 },
		c = { 1, 2, 3, 4 },
		d = { 1, 3, 2, 4 },
		e = { 5, 1, 2, 4, 3 },
		f = { 1, 5, 4, 2, 3 };
	vector<vector<int>>
		A = { { 0, 1 }, { 2, 3 } },
		B,
		C = { { 0, 4 }, { 4, 2 }, { 1, 3 }, { 1, 4 } };
	Solution s;
	OutExpr(s.minimumHammingDistance(a, b, A), "%d");
	OutExpr(s.minimumHammingDistance(c, d, B), "%d");
	OutExpr(s.minimumHammingDistance(e, f, C), "%d");
}
