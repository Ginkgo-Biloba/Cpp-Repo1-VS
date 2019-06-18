﻿#include "../srcOld/utility.hpp"

/* 352. 将数据流变为多个不相交区间

给定一个非负整数的数据流输入 a1，a2，…，an，…，
将到目前为止看到的数字总结为不相交的区间列表。

例如，假设数据流中的整数为 1，3，7，2，6，…，每次的总结为：
[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]

进阶：
如果有很多合并，并且与数据流的大小相比，不相交区间的数量很小，该怎么办?
*/

struct Interval
{
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};


// https://leetcode.com/problems/data-stream-as-disjoint-intervals/discuss/82557/Very-concise-c%2B%2B-solution.
// 抄的
bool operator <(Interval x, Interval y)
{
	return x.start < y.start;
}

class SummaryRanges
{
	vector<Interval> vec;

public:
	/** Initialize your data structure here. */
	SummaryRanges() {}

	void addNum(int val)
	{
		Interval rng(val, val);
		auto it = std::lower_bound(vec.begin(), vec.end(), rng);
		if (it != vec.begin() && (it - 1)->end + 1 >= val)
			--it;
		while (it != vec.end() && val + 1 >= it->start && val - 1 <= it->end)
		{
			rng.start = std::min(rng.start, it->start);
			rng.end = std::max(rng.end, it->end);
			it = vec.erase(it);
		}
		vec.insert(it, rng);
	}

	vector<Interval> getIntervals()
	{
		return vec;
	}
};


int main()
{}