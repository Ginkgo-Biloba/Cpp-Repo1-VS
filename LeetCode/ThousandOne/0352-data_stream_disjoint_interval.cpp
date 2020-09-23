#include "leetcode.hpp"

/* 352. 将数据流变为多个不相交区间

给定一个非负整数的数据流输入 a1，a2，…，an，…，将到目前为止看到的数字总结为不相交的区间列表。

例如，假设数据流中的整数为 1，3，7，2，6，…，每次的总结为：

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]

进阶：
如果有很多合并，并且与数据流的大小相比，不相交区间的数量很小，该怎么办?

提示：
特别感谢 @yunhong 提供了本问题和其测试用例。
*/

// https://leetcode.com/problems/data-stream-as-disjoint-intervals/discuss/82557/Very-concise-c%2B%2B-solution.
// 抄的
class SummaryRanges
{
	struct Comp
	{
		bool operator()(vector<int>& a, vector<int>& b) const
		{
			return a[0] < b[0];
		}
	};

	vector<vector<int>> V;

public:
	/** Initialize your data structure here. */
	SummaryRanges()
	{}

	void addNum(int val)
	{
		vector<int> r(val, val);
		auto it = lower_bound(V.begin(), V.end(), r);
		if (it != V.begin() && (it - 1)->at(1) + 1 >= val)
			--it;
		while (it != V.end()
			&& val + 1 >= it->at(0)
			&& val - 1 <= it->at(1))
		{
			r[0] = min(r[0], it->at(0));
			r[1] = max(r[1], it->at(1));
			it = V.erase(it);
		}
		V.insert(it, r);
	}

	vector<vector<int>> getIntervals()
	{
		return V;
	}
};


int main()
{}
