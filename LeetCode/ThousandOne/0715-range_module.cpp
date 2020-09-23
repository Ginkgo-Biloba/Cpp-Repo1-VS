#include "leetcode.hpp"

/* 715. Range 模块

Range 模块是跟踪数字范围的模块。你的任务是以一种有效的方式设计和实现以下接口。
	addRange(int left, int right) 添加半开区间 [left, right)，跟踪该区间中的每个实数。添加与当前跟踪的数字部分重叠的区间时，应当添加在区间 [left, right) 中尚未跟踪的任何数字到该区间中。
	queryRange(int left, int right) 只有在当前正在跟踪区间 [left, right) 中的每一个实数时，才返回 true。
	removeRange(int left, int right) 停止跟踪区间 [left, right) 中当前正在跟踪的每个实数。

示例：
addRange(10, 20): null
removeRange(14, 16): null
queryRange(10, 14): true （区间 [10, 14) 中的每个数都正在被跟踪）
queryRange(13, 15): false （未跟踪区间 [13, 15) 中像 14, 14.03, 14.17 这样的数字）
queryRange(16, 17): true （尽管执行了删除操作，区间 [16, 17) 中的数字 16 仍然会被跟踪）

提示：
	半开区间 [left, right) 表示所有满足 left <= x < right 的实数。
	对 addRange, queryRange, removeRange 的所有调用中 0 < left < right < 10^9。
	在单个测试用例中，对 addRange 的调用总数不超过 1000 次。
	在单个测试用例中，对  queryRange 的调用总数不超过 5000 次。
	在单个测试用例中，对 removeRange 的调用总数不超过 1000 次。
*/

// https://leetcode.com/problems/range-module/discuss/108912/C%2B%2B-vector-O(n)-and-map-O(logn)-compare-two-solutions
// 抄的
class RangeModule
{
	vector<pair<int, int>> cur, tmp;

public:
	RangeModule()
	{}

	void addRange(int left, int right)
	{
		size_t n = cur.size();
		tmp.clear();
		tmp.reserve(n);
		for (size_t i = 0; i <= n; ++i)
		{
			if (i == n || cur[i].first > right)
			{
				tmp.emplace_back(left, right);
				for (; i < n; ++i)
					tmp.push_back(cur[i]);
			}
			else if (cur[i].second < left)
				tmp.push_back(cur[i]);
			else
			{
				left = std::min(left, cur[i].first);
				right = std::max(right, cur[i].second);
			}
		}
		cur.swap(tmp);
	}

	bool queryRange(int left, int right)
	{
		size_t L = 0, R = cur.size();
		while (L < R)
		{
			size_t M = (L + R) / 2;
			if (cur[M].first >= right)
				R = M;
			else if (cur[M].second <= left)
				L = M + 1;
			else
				return (cur[M].first <= left && right <= cur[M].second);
		}
		return false;
	}

	void removeRange(int left, int right)
	{
		size_t n = cur.size();
		tmp.clear();
		tmp.reserve(n);
		for (size_t i = 0; i < n; ++i)
		{
			if (cur[i].second <= left || cur[i].first >= right)
				tmp.push_back(cur[i]);
			else
			{
				if (cur[i].first < left)
					tmp.emplace_back(cur[i].first, left);
				if (cur[i].second > right)
					tmp.emplace_back(right, cur[i].second);
			}
		}
		cur.swap(tmp);
	}
};


int main()
{
	RangeModule rm;
	rm.addRange(10, 20);
	rm.removeRange(14, 16);
	OutBool(rm.queryRange(10, 14));
	OutBool(rm.queryRange(12, 15));
	OutBool(rm.queryRange(16, 17));
}
