/** https://msdn.microsoft.com/zh-cn/library/dd984038.aspx
下面的示例并行执行两项任务
第一项任务计算 nth 斐波纳契数；第二个任务将打印到控制台进度指示器

第一项任务使用递归分解计算斐波纳契数
也就是说，每个任务以递归方式创建多个子任务计算的总体结果
使用递归分解的任务可能会用尽所有可用的资源，并从而枯竭其他任务
在此示例中，输出的进度指示器的任务可能无法收到及时对计算资源的访问权

为了说明使用具有自定义策略的计划程序的优势，此示例执行整个任务两次
该示例首先使用默认计划程序计划这两项任务
然后，该示例使用默认计划程序安排第一个任务，并具有计划第二个任务的自定义策略的计划程序 */

#include <Windows.h>
#include <ppl.h>
#include <agents.h>
using namespace Concurrency;
#include <cstdint>
#include <iostream>
using std::wcout; using std::endl; using std::flush;

/** 函数需要执行长时间操作，因此故意不优化 */
unsigned fibonacci(unsigned n)
{
	if (n < 2u)
		return n;
	
	unsigned n1, n2;
	parallel_invoke(
		[n, &n1] { n1 = fibonacci(n - 1u); },
		[n, &n2] { n2 = fibonacci(n - 2u); });
	
	return n1 + n2;
}


uint64_t fastFibonacci(uint64_t n)
{
	uint64_t kp, k = 0, ks = (uint64_t)(-1); // 定义第 -1 项为 1
	uint64_t mask = (uint64_t(1) << 63);
	
	
	return k;
}


/** 计算的同时输出一个指示器 */
void progress(Scheduler& schd, unsigned n)
{
	// 使用任务组计算斐波那契数
	// 任务由当前计划完成
	structured_task_group tasks;
	auto ta1 = make_task([&n]() -> void { n = fibonacci(n); });
	tasks.run(ta1);

	// 创建一个调用对象，输出字符到控制台
	// 使用提供的计划来执行
	call<wchar_t> c(schd, [](wchar_t ch) { wcout << ch << flush; });

	// 连接调用对象到计时器。计时器每隔 100 毫秒发送一个信息
	// 使用提供的计划来执行
	timer<wchar_t> t(schd, 100, L'.', &c, true);
	t.start();

	tasks.wait();
	t.stop();
	wcout << L"done. n = " << n << endl;
}


int wmain()
{
	int const n = 38; // 计算第 38 个斐波那契数

	// 使用默认计划执行指示器，同时在背景计算斐波那契数
	wcout << L"Default scheduler:" << endl;
	progress(*(CurrentScheduler::Get()), n);

	// 现在使用一个新的计划，指示器具有自定义的的策略
	// 自定义策略指定线程优先级位最高
	SchedulerPolicy policy(1, ContextPriority, THREAD_PRIORITY_HIGHEST);
	Scheduler* schd = Scheduler::Create(policy);
	// 注册停止事件
	HANDLE hShutdown = CreateEventW(NULL, FALSE, FALSE, NULL);
	schd->RegisterShutdownEvent(hShutdown);

	wcout << L"Scheduler has a custom policy:" << endl;
	progress(*schd, n);
	
	// 释放最后的引用，这导致计划停止
	schd->Release();

	WaitForSingleObject(hShutdown, INFINITE);
	CloseHandle(hShutdown);
}
