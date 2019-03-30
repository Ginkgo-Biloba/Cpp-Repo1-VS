#include "../srcOld/utility.hpp"

/* 设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。
 * - push(x) -- 将元素 x 推入栈中。
 * - pop() -- 删除栈顶的元素。
 * - top() -- 获取栈顶元素。
 * - getMin() -- 检索栈中的最小元素。
 **/

// https://leetcode.com/problems/min-stack/discuss/49014/Java-accepted-solution-using-one-stack
// 抄的
class MinStack
{
	int minval;
	vector<int> stack;
public:
	MinStack()
		: minval(INT_MAX)
	{}

	void push(int x)
	{
		// 如果新值不大，把旧的最小值放入栈
		if (x <= minval)
		{
			stack.push_back(minval); // 这个数被存了两次
			minval = x;
		}
		stack.push_back(x);
	}

	void pop()
	{
		// 如果 pop 会改变当前的最小值，那么 pop 两次
		// 把最小值改成上一次的最小值
		if (stack.back() == minval)
		{
			stack.pop_back();
			minval = stack.back(); // 这个数被存了两次
		}
		stack.pop_back();
	}

	int top()
	{
		return stack.back();
	}

	int getMin()
	{
		return minval;
	}
};


int main()
{
	MinStack minStack;
	minStack.push(-2);
	minStack.push(0);
	minStack.push(-3);
	printf("%d, ", minStack.getMin()); // -3
	minStack.pop();
	printf("%d, ", minStack.top()); // 0
	printf("%d, ", minStack.getMin()); // -2
	printf("\n");
}
