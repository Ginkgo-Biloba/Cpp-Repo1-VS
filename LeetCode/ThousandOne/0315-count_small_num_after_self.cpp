#include "leetcode.hpp"

/* 315. 计算右侧小于当前元素的个数

给定一个整数数组 nums，按要求返回一个新数组 counts。
数组 counts 有该性质： counts[i] 的值是 nums[i] 右侧小于 nums[i] 的元素的数量。

示例:

输入: [5,2,6,1]
输出: [2,1,1,0]
解释:
5 的右侧有 2 个更小的元素 (2 和 1).
2 的右侧仅有 1 个更小的元素 (1).
6 的右侧有 1 个更小的元素 (1).
1 的右侧有 0 个更小的元素.
*/

// https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/138154/The-C%2B%2B-merge-sort-template-for-pairs-'i'-'j'-problem
// 抄的
class Solution
{
	typedef pair<int, int> elem;

	vector<elem> vidx, buf;
	vector<int> ans;

	// 左闭右开区间
	void sortCount(int L, int R)
	{
		if (L + 1 >= R)
			return;
		int i, a, b, m = (L + R) / 2;
		sortCount(L, m);
		sortCount(m, R);
		for (a = L, b = m; a < m; ++a)
		{
			while (b < R && vidx[a].first > vidx[b].first)
				++b;
			ans[vidx[a].second] += b - m;
		}

		for (i = a = L, b = m; a < m && b < R; ++i)
		{
			if (vidx[a].first < vidx[b].first)
			{
				buf[i] = vidx[a];
				++a;
			}
			else
			{
				buf[i] = vidx[b];
				++b;
			}
		}
		for (; a < m; ++i, ++a)
			buf[i] = vidx[a];
		for (; b < R; ++i, ++b)
			buf[i] = vidx[b];
		for (i = L; i < R; ++i)
			vidx[i] = buf[i];

		/*inplace_merge(
			vidx.begin() + L,
			vidx.begin() + m,
			vidx.begin() + R);*/
	}

public:
	vector<int> countSmaller(vector<int>& nums)
	{
		int len = static_cast<int>(nums.size());
		ans.assign(len, 0);
		buf.resize(len);
		vidx.clear();
		for (int i = 0; i < len; ++i)
			vidx.emplace_back(nums[i], i);
		sortCount(0, len);
		vector<int> R;
		R.swap(ans);
		return R;
	}
};


int main()
{
	vector<int> a = { 5, 2, 6, 1 };
	Solution s;
	output(s.countSmaller(a), "");
}
