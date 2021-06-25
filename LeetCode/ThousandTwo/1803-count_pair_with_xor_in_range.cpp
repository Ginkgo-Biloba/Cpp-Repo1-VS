#include "leetcode.hpp"

/* 1803. 统计异或值在范围内的数对有多少

给你一个整数数组 nums （下标 从 0 开始 计数）以及两个整数：low 和 high ，请返回 漂亮数对 的数目。

漂亮数对 是一个形如 (i, j) 的数对，其中 0 <= i < j < nums.length 且 low <= (nums[i] XOR nums[j]) <= high 。

示例 1：

输入：nums = [1,4,2,7], low = 2, high = 6
输出：6
解释：所有漂亮数对 (i, j) 列出如下：
- (0, 1): nums[0] XOR nums[1] = 5
- (0, 2): nums[0] XOR nums[2] = 3
- (0, 3): nums[0] XOR nums[3] = 6
- (1, 2): nums[1] XOR nums[2] = 6
- (1, 3): nums[1] XOR nums[3] = 3
- (2, 3): nums[2] XOR nums[3] = 5

示例 2：

输入：nums = [9,8,4,2,1], low = 5, high = 14
输出：8
解释：所有漂亮数对 (i, j) 列出如下：
	​- (0, 2): nums[0] XOR nums[2] = 13
	- (0, 3): nums[0] XOR nums[3] = 11
	- (0, 4): nums[0] XOR nums[4] = 8
	- (1, 2): nums[1] XOR nums[2] = 12
	- (1, 3): nums[1] XOR nums[3] = 10
	- (1, 4): nums[1] XOR nums[4] = 9
	- (2, 3): nums[2] XOR nums[3] = 6
	- (2, 4): nums[2] XOR nums[4] = 5

提示：
	1 <= nums.length <= 2 * 10^4
	1 <= nums[i] <= 2 * 104
	1 <= low <= high <= 2 * 10^4
*/

class Solution
{
	int idx;
	vector<int> cnt;
	vector<array<int, 2>> trie;

	void insert(int x)
	{
		int p = 0;
		for (int i = 31; i >= 0; --i)
		{
			int b = (x >> i) & 1;
			if (!(trie[p][b]))
				trie[p][b] = ++idx;
			p = trie[p][b];
			cnt[p] += 1;
		}
	}

	int query(int x, int y)
	{
		int ans = 0, p = 0;
		for (int i = 31; i >= 0; --i)
		{
			int b = (x >> i) & 1;
			int c = (y >> i) & 1;
			if (c == 0)
				p = trie[p][b];
			else
			{
				ans += cnt[trie[p][b]];
				p = trie[p][!b];
			}
			/*if (b == 0 && c == 0)
				p = trie[p][0];
			else if (b == 0 && c == 1)
			{
				ans += cnt[trie[p][0]];
				p = trie[p][1];
			}
			else if (b == 1 && p == 0)
				p = trie[p][1];
			else
			{
				ans += cnt[trie[p][1]];
				p = trie[p][0];
			}*/
			if (!p)
				break;
		}
		return ans;
	}

public:
	int countPairs(vector<int>& A, int low, int high)
	{
		int len = static_cast<int>(A.size());
		int ans = idx = 0;
		cnt.assign(len * 32 + 1, 0);
		trie.resize(len * 32 + 1);
		memset(trie.data(), 0, trie.size() * sizeof(trie[0]));
		for (int i = 0; i < len; ++i)
		{
			ans += query(A[i], high + 1) - query(A[i], low);
			insert(A[i]);
		}
		return ans;
	}
};


int main()
{
	Solution s;
	vector<int>
		a = { 1, 4, 2, 7 },
		b = { 9, 8, 4, 2, 1 };
	OutExpr(s.countPairs(a, 2, 6), "%d");
	OutExpr(s.countPairs(b, 5, 14), "%d");
}
