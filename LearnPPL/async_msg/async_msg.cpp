// https://msdn.microsoft.com/zh-cn/library/dd504833.aspx

#include <agents.h>
#include <ppl.h>
using namespace Concurrency;

#include <iostream>
using std::wcout; using std::flush; using std::endl;

/** 函数需要执行长时间操作，因此故意不优化 */
unsigned fibonacci(unsigned n)
{
	if (n < 2u)
		return n;
	unsigned ans = fibonacci(n - 1u) + fibonacci(n - 2u);
	return ans;
}


/** 使用 concurrency::make_choice 函数来创建 choice 对象，它在三个消息块之间选择对象
 * 然后计算几个斐波那契数字，并将每个结果存储在不同的消息块中
 * 然后根据首先完成该的操作，向控制台显示一条消息 */
void msg_choice()
{
	/* 虽然下面的信息块仅仅写一次信息
	* 但是后面显示 choice 类可以与不同的信息块类型工作 */

	// 几个斐波那契数列和一半
	single_assignment<unsigned> fib35, fib37;
	single_assignment<float> half_fib42;

	// 创建一个 choice 对象，选择第一个 single_assignment 对象接收结果
	auto select1 = make_choice(&fib35, &fib37, &half_fib42);

	parallel_invoke(
		[&fib35]() -> void { send(fib35, fibonacci(35u)); },
		[&fib37]() -> void { send(fib37, fibonacci(37u)); },
		[&half_fib42]() -> void { send(half_fib42, fibonacci(42u) * 0.5f); }
	);

	// 根据首先执行完成的操作，打印消息
	switch (receive(select1))
	{
	case 0:
		wcout << L"fib35: " << receive(fib35) << "\n";
		break;
	case 1:
		wcout << L"fib37: " << receive(fib37) << "\n";
		break;
	case 2:
		wcout << L"half_fib42: " << receive(half_fib42) << "\n";
		break;
	default:
		wcout << L"error" << "\n";
		break;
	}
	wcout << L"----- function: " __FUNCTIONW__ L"\n" << endl;
}


/** 使用 concurrency::make_join 函数来创建 join 对象
* 与 choice 不同，它等待所有源消息块 */
void msg_join()
{
	/* 虽然下面的信息块仅仅写一次信息
	* 但是后面显示 choice 类可以与不同的信息块类型工作 */

	// 几个斐波那契数列和一半
	single_assignment<unsigned> fib35, fib37;
	single_assignment<float> half_fib42;

	// 创建一个 choice 对象，选择第一个 single_assignment 对象接收结果
	auto joinAll = make_join(&fib35, &fib37, &half_fib42);

	parallel_invoke(
		[&fib35]() -> void { send(fib35, fibonacci(35u)); },
		[&fib37]() -> void { send(fib37, fibonacci(37u)); },
		[&half_fib42]() -> void { send(half_fib42, fibonacci(42u) * 0.5f); }
	);

	auto result = receive(joinAll);
	wcout << L"fib35: " << std::get<0>(result) << L"\n";
	wcout << L"fib37: " << std::get<1>(result) << L"\n";
	wcout << L"half_fib42: " << std::get<2>(result) << L"\n";
	wcout << L"----- function: " __FUNCTIONW__ L"\n" << endl;
}


/** 使用 timer 对象估计要进行的长时间操作的消耗的时间 */
void msg_timer()
{
	// 创建一个 call 对象，当接收消息时，向控制台打印字符
	call<wchar_t> printer([](wchar_t c) -> void
	{ wcout << c << std::flush; });

	// 创建计时器，每 100 毫秒发送一个 . 到 call 对象
	timer<wchar_t> progress(100u, L'.', &printer, true);

	// 启动计时器，计算
	wcout << L"computer fibonacci(42)";
	progress.start();
	unsigned fib42 = fibonacci(42u);

	progress.stop();
	wcout << L"\n result is " << fib42 << "\n";
	wcout << L"----- function: " __FUNCTIONW__ L"\n" << endl;
}


/** 过滤消息，只接收偶数 */
void msg_filter()
{
	unbounded_buffer<unsigned> evens([](unsigned n) -> bool { return !(n & 1u); });

	// 发送几个数字 
	unsigned count = 0u;
	for (unsigned u = 0u; u < 10u; ++u)
	{
		// asend 方法只有当目标接收信息时彩返回 true
		// 这使得我们可以确定有多少元素存储在缓冲区中
		if (asend(evens, u))
			++count;
	}

	// 输出缓冲区的每个数
	while (count--) { wcout << receive(evens) << L"; "; }
	wcout << L"\b\b.\n";
	wcout << L"----- function: " __FUNCTIONW__ L"\n" << endl;
}


int wmain()
{
	msg_choice();
	msg_join();
	msg_timer();
	msg_filter();
}
