#include "leetcode.hpp"

/* 703. 数据流中的第K大元素

设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。

你的 KthLargest 类需要一个同时接收整数 k 和整数数组nums 的构造器，它包含数据流中的初始元素。每次调用 KthLargest.add，返回当前数据流中第K大的元素。

示例:

int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8

说明:
	你可以假设 nums 的长度≥ k-1 且k ≥ 1。
*/

class KthLargest
{
	std::priority_queue<int, vector<int>, std::greater<int>> pq;
	size_t const K;

public:
	KthLargest(int k, vector<int>& nums)
		: K(k)
	{
		for (int i : nums)
			add(i);
	}

	int add(int val)
	{
		if (pq.size() < K)
			pq.push(val);
		else if (val > pq.top())
		{
			pq.pop();
			pq.push(val);
		}
		return pq.top();
	}
};


int main()
{
	vector<int> nums = { 4, 5, 8, 2 };
	KthLargest t(3, nums);
	OutExpr(t.add(3), "%d");
	OutExpr(t.add(5), "%d");
	OutExpr(t.add(10), "%d");
	OutExpr(t.add(9), "%d");
	OutExpr(t.add(4), "%d");
	OutExpr(t.add(3), "%d");
}
