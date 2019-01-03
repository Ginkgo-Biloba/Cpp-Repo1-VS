// https://msdn.microsoft.com/zh-cn/library/hh873170.aspx
/* 下面的示例多次计算范围[0, 100000] 内质数的计数
 * 如果在给定时间限制内没有完成，则操作失败
 * countPrimes 函数演示如何使用 cancelAfterTimeout 函数
 * 它会对给定范围内的质数进行计数，而且如果任务未在提供的时间内完成，则会失败
 * wmain 函数多次调用 count_primes 函数。 每次将时间限制减半
 * 当操作未在当前时间限制内完成后，程序结束 */

#include <iostream>
using std::wcout; using std::endl;

#include <ppl.h>
#include <ppltasks.h>
#include <agents.h>
using namespace Concurrency;


/** 创建一个任务，在给定的时间内完成 */
task<void> completeAfter(unsigned timeout)
{
	// 任务完成时间，当计时器触发时被置位
	task_completion_event<void> tce;

	// 创建一个不重复的计时器
	timer<int>* fireOnce = new timer<int>(timeout, 0, nullptr, false);
	// 创建一个调用对象，在计时器触发时设置完成事件
	call<int>* callback = new call<int>([tce](int) -> void { tce.set(); });

	// 链接计时器到回调函数，然后启动计时器
	fireOnce->link_target(callback);
	fireOnce->start();

	// 创建一个任务，在任务事件设置之后完成
	task<void> eventSet(tce);

	// 创建一个连续的任务，清理资源并返回自身
	return eventSet.then([fireOnce, callback]() -> void
	{
		delete callback; delete fireOnce;
	});
}


/** 在指定的延时之后，如果给定的任务没有完成，则取消它 */
template<class T>
task<T> cancelAfterTimeout(task<T> t, cancellation_token_source cts, unsigned timeout)
{
	// 创建任务，如果指定的任务完成了，返回 true 
	task<bool> successTask = t.then([](T) -> bool { return true; });
	// 创建任务，在指定的时间之后，返回 false
	task<bool> failureTask = completeAfter(timeout).then([]() -> bool { return false; });

	// 创建连续任务，如果超时先结束，则取消整体任务
	return (failureTask || successTask).then([t, cts](bool flag) -> task<T>
	{
		// 设置取消标志。作为参数 t 传递的任务应该响应取消标志，并尽快停止
		if (!flag) cts.cancel();
		return t;
	});
}


/** 判断一个数是不是质数 */
bool isPrime(unsigned n)
{
	if (n == 2u) return true;
	if (n < 2u) return false;
	if (!(n & 1u)) return false;
	for (unsigned i = 3u; i < n; i += 2u)
	{
		if (!(n % i))
			return false;
	}
	return true;
}


/** 统计区间 [0, maxval] 内质数的数量。如果超时，操作失败 */
bool countPrimes(unsigned maxval, unsigned timeout)
{
	cancellation_token_source cts;

	// 创建一个任务，计算质数的数量。在给定的超时之后取消
	task<size_t> t = cancelAfterTimeout(task<size_t>([maxval, timeout]() -> size_t
	{
		combinable<size_t> counts;
		parallel_for(0u, maxval + 1u, [&counts](unsigned n) -> void
		{
			// 如果全局任务因为取消当前任务而取消，则响应
			if (is_task_cancellation_requested())
				cancel_current_task();

			if (isPrime(n))
				++(counts.local());
		});
		// 返回所有线程的计数和
		return counts.combine(std::plus<size_t>());
	}, cts.get_token()), cts, timeout);

	try	// 输出结果
	{
		size_t count = t.get();
		wcout << L"Found " << count << L" prime numbers within " << \
			timeout << L" ms." << endl;
		return true;
	}
	catch (task_canceled& e)
	{
		wcout << L"The task timed out." << endl;
		wcout << e.what() << endl;
		return false;
	}
}


/* 在给定的时间内计算区间 [0, maxval] 内的质数个数，直到失败
 * 每次成功之后，超时减半 */
int wmain()
{
	unsigned maxval = 100000u;
	unsigned timeout = 5000u;

	bool flag = true; do
	{
		flag = countPrimes(maxval, timeout);
		timeout = (timeout + 1u) / 2u;
	} while (flag);
}



