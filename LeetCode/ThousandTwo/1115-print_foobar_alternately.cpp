#include "leetcode.hpp"

/* 1115. 交替打印FooBar

我们提供一个类：

class FooBar {
	public void foo() {
		for (int i = 0; i < n; i++) {
			print("foo");
		}
	}

	public void bar() {
		for (int i = 0; i < n; i++) {
			print("bar");
		}
	}
}

两个不同的线程将会共用一个 FooBar 实例。其中一个线程将会调用 foo() 方法，另一个线程将会调用 bar() 方法。

请设计修改程序，以确保 "foobar" 被输出 n 次。

示例 1:
输入: n = 1
输出: "foobar"
解释: 这里有两个线程被异步启动。其中一个调用 foo() 方法, 另一个调用 bar() 方法，"foobar" 将被输出一次。

示例 2:
输入: n = 2
输出: "foobarfoobar"
解释: "foobar" 将被输出两次。
*/


#include <condition_variable>
#include <mutex>
#include <thread>

class FooBar
{
private:
	int n, x;
	std::mutex lock;
	std::condition_variable cond;

public:
	FooBar(int _n)
	{
		this->n = _n;
		this->x = 0;
	}

	void foo(std::function<void()> printFoo)
	{
		std::unique_lock<std::mutex> dummy(lock);
		for (int i = 0; i < n; i++)
		{
			while (x != 0)
				cond.wait(dummy, [this]() { return x == 0; });
			// printSecond() outputs "second". Do not change or remove this line.
			printFoo();
			x = 1;
			cond.notify_one();
		}
	}

	void bar(std::function<void()> printBar)
	{
		std::unique_lock<std::mutex> dummy(lock);
		for (int i = 0; i < n; i++)
		{
			while (x != 1)
				cond.wait(dummy, [this]() { return x == 1; });
			// printBar() outputs "bar". Do not change or remove this line.
			printBar();
			x = 0;
			cond.notify_one();
		}
	}
};

int main()
{}
