#include "leetcode.hpp"

/* 295. 数据流的中位数

中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：
	void addNum(int num) - 从数据流中添加一个整数到数据结构中。
	double findMedian() - 返回目前所有元素的中位数。

示例：

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2

进阶:
	如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
	如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？
*/

// https://leetcode.com/problems/find-median-from-data-stream/discuss/74163/My-C%2B%2B-priority_queue-based-solution-(140-ms)
// 当初是抄的
class MedianFinder
{
	priority_queue<int> a;
	priority_queue<int, vector<int>, std::greater<int>> b;

public:
	/** initialize your data structure here. */
	MedianFinder()
	{}

	void addNum(int num)
	{
		if (a.empty() || num <= a.top())
		{
			a.push(num);
			if (a.size() > b.size() + 1)
			{
				b.push(a.top());
				a.pop();
			}
		}
		else
		{
			b.push(num);
			if (a.size() < b.size())
			{
				a.push(b.top());
				b.pop();
			}
		}
	}

	double findMedian()
	{
		if (a.size() > b.size())
			return a.top();
		else
			return 0.5 * a.top() + 0.5 * b.top();
	}
};


int main()
{
	MedianFinder m;
	m.addNum(1);
	m.addNum(2);
	OutExpr(m.findMedian(), "%f");
	m.addNum(3);
	OutExpr(m.findMedian(), "%f");
	m.addNum(1);
	m.addNum(1);
	m.addNum(1);
	OutExpr(m.findMedian(), "%f");
}
