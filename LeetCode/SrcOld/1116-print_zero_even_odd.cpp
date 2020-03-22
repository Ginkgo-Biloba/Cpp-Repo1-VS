#include "leetcode.hpp"

/* 1116. 打印零与奇偶数

假设有这么一个类：

class ZeroEvenOdd {
	public ZeroEvenOdd(int n) { ... }      // 构造函数
	public void zero(printNumber) { ... }  // 仅打印出 0
	public void even(printNumber) { ... }  // 仅打印出 偶数
	public void odd(printNumber) { ... }   // 仅打印出 奇数
}

相同的一个 ZeroEvenOdd 类实例将会传递给三个不同的线程：
	线程 A 将调用 zero()，它只输出 0 。
	线程 B 将调用 even()，它只输出偶数。
	线程 C 将调用 odd()，它只输出奇数。

每个线程都有一个 printNumber 方法来输出一个整数。
请修改给出的代码以输出整数序列 010203040506... ，其中序列的长度必须为 2n。

示例 1：

输入：n = 2
输出："0102"
说明：三条线程异步执行，其中一个调用 zero()，另一个线程调用 even()，最后一个线程调用odd()。
正确的输出为 "0102"。

示例 2：

输入：n = 5
输出："0102030405"
*/


#include <atomic>
#include <thread>

class ZeroEvenOdd
{
private:
	int n;
	std::atomic<int> x;

public:
	ZeroEvenOdd(int _n)
	{
		this->n = _n * 2;
		x.store(0, std::memory_order_relaxed);
	}

	// printNumber(x) outputs "x", where x is an integer.
	void zero(std::function<void(int)> printNumber)
	{
		for (;;)
		{
			int cur = x.load(std::memory_order_acquire);
			if (cur >= n)
				break;
			else if ((cur & 1) == 0)
			{
				printNumber(0);
				x.fetch_add(1, std::memory_order_acq_rel);
			}
			std::this_thread::yield();
		}
	}

	void even(std::function<void(int)> printNumber)
	{
		for (;;)
		{
			int cur = x.load(std::memory_order_acquire);
			if (cur >= n)
				break;
			if ((cur & 3) == 3)
			{
				printNumber((cur + 1) >> 1);
				x.fetch_add(1, std::memory_order_acq_rel);
			}
			std::this_thread::yield();
		}
	}

	void odd(std::function<void(int)> printNumber)
	{
		for (;;)
		{
			int cur = x.load(std::memory_order_acquire);
			if (cur >= n)
				break;
			else if ((cur & 3) == 1)
			{
				printNumber((cur + 1) >> 1);
				x.fetch_add(1, std::memory_order_acq_rel);
			}
			std::this_thread::yield();
		}
	}
};


void printNumber(int x)
{
	printf("%d", x);
}

int main()
{
	std::function<void(int)> f(printNumber);
	ZeroEvenOdd z(9);
	std::thread
		a(&ZeroEvenOdd::zero, &z, f),
		b(&ZeroEvenOdd::odd, &z, f),
		c(&ZeroEvenOdd::even, &z, f);
	std::this_thread::yield();
	a.join();
	b.join();
	c.join();
}
