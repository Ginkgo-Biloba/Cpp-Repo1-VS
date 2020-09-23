#include "leetcode.hpp"

/* 155. 最小栈

设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
	push(x) —— 将元素 x 推入栈中。
	pop() —— 删除栈顶的元素。
	top() —— 获取栈顶元素。
	getMin() —— 检索栈中的最小元素。

示例:

输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.

提示：
	pop、top 和 getMin 操作总是在 非空栈 上调用。
*/

class MinStack
{
	// a 放数据 b 单调栈
	vector<int> a, b;

public:
	/** initialize your data structure here. */
	MinStack()
	{}

	void push(int x)
	{
		a.push_back(x);
		if (b.empty() || x <= b.back())
			b.push_back(x);
	}

	void pop()
	{
		if (a.back() == b.back())
			b.pop_back();
		a.pop_back();
	}

	int top()
	{
		return a.back();
	}

	int getMin()
	{
		return b.back();
	}
};


int main()
{
	MinStack s;
	s.push(-2);
	s.push(0);
	s.push(-3);
	OutExpr(s.getMin(), "%d");
	s.pop();
	OutExpr(s.top(), "%d");
	OutExpr(s.getMin(), "%d");
}
