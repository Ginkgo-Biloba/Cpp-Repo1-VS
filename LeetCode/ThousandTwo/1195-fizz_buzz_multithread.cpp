#include "leetcode.hpp"

/* 1195. 交替打印字符串

编写一个可以从 1 到 n 输出代表这个数字的字符串的程序，但是：
	如果这个数字可以被 3 整除，输出 "fizz"。
	如果这个数字可以被 5 整除，输出 "buzz"。
	如果这个数字可以同时被 3 和 5 整除，输出 "fizzbuzz"。

例如，当 n = 15，输出： 1, 2, fizz, 4, buzz, fizz, 7, 8, fizz, buzz, 11, fizz, 13, 14, fizzbuzz。

假设有这么一个类：

class FizzBuzz {
	public FizzBuzz(int n) { ... }               // constructor
	public void fizz(printFizz) { ... }          // only output "fizz"
	public void buzz(printBuzz) { ... }          // only output "buzz"
	public void fizzbuzz(printFizzBuzz) { ... }  // only output "fizzbuzz"
	public void number(printNumber) { ... }      // only output the numbers
}

请你实现一个有四个线程的多线程版  FizzBuzz， 同一个 FizzBuzz 实例会被如下四个线程使用：
	线程A将调用 fizz() 来判断是否能被 3 整除，如果可以，则输出 fizz。
	线程B将调用 buzz() 来判断是否能被 5 整除，如果可以，则输出 buzz。
	线程C将调用 fizzbuzz() 来判断是否同时能被 3 和 5 整除，如果可以，则输出 fizzbuzz。
	线程D将调用 number() 来实现输出既不能被 3 整除也不能被 5 整除的数字。
*/

#include <atomic>
#include <chrono>
#include <thread>

class FizzBuzz
{
private:
	int n;
	std::atomic<int> i;
	std::chrono::milliseconds dur;
	std::memory_order acqrel;

public:
	FizzBuzz(int _n)
		: n(_n)
		, dur(10)
		, acqrel(std::memory_order_acq_rel)
	{
		i.store(1, std::memory_order_relaxed);
	}

	// printFizz() outputs "fizz".
	void fizz(std::function<void()> printFizz)
	{
		int k = 0;
		while (k <= n)
		{
			k = i.load(acqrel);
			if (k <= n && k % 3 == 0 && k % 5 != 0)
			{
				printFizz();
				i.fetch_add(1, acqrel);
			}
			std::this_thread::sleep_for(dur);
		}
	}

	// printBuzz() outputs "buzz".
	void buzz(std::function<void()> printBuzz)
	{
		int k = 0;
		while (k <= n)
		{
			k = i.load(acqrel);
			if (k <= n && k % 3 != 0 && k % 5 == 0)
			{
				printBuzz();
				i.fetch_add(1, acqrel);
			}
			std::this_thread::sleep_for(dur);
		}
	}

	// printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(std::function<void()> printFizzBuzz)
	{
		int k = 0;
		while (k <= n)
		{
			k = i.load(acqrel);
			if (k <= n && k % 3 == 0 && k % 5 == 0)
			{
				printFizzBuzz();
				i.fetch_add(1, acqrel);
			}
			std::this_thread::sleep_for(dur);
		}
	}

	// printNumber(x) outputs "x", where x is an integer.
	void number(std::function<void(int)> printNumber)
	{
		int k = 0;
		while (k <= n)
		{
			k = i.load(acqrel);
			if (k <= n && k % 3 != 0 && k % 5 != 0)
			{
				printNumber(k);
				i.fetch_add(1, acqrel);
			}
			std::this_thread::sleep_for(dur);
		}
	}
};


int main()
{
	FizzBuzz fb(30);
	std::function<void(void)>
		fizz = []() { puts("fizz"); },
		buzz = []() { puts("buzz"); },
		fbzz = []() { puts("fizzbuzz"); };
	std::function<void(int)> nums = [](int i)
	{
		char buf[16];
		sprintf(buf, "%d", i);
		puts(buf);
	};
	std::thread
		a(&FizzBuzz::fizz, &fb, fizz),
		b(&FizzBuzz::buzz, &fb, buzz),
		c(&FizzBuzz::fizzbuzz, &fb, fbzz),
		d(&FizzBuzz::number, &fb, nums);
	a.join();
	b.join();
	c.join();
	d.join();
}
