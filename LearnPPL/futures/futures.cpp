// https://msdn.microsoft.com/zh-cn/library/dd764564.aspx
/* 下面的示例演示了完整 async_future 类和其用法的示例
 * wmain 函数创建 std::vector 对象，其中包含 10000 随机整数值
 * 然后，它使用 async_future 对象查找中包含的最小和最大值 vector 对象 */

#include <ppl.h>
#include <ppltasks.h>
#include <agents.h>
using namespace Concurrency;
#include <vector> 
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>
using std::vector;
using std::wcout; using std::endl;


template<class T> class AsyncFuture
{
public:
	template<class Functor>
	explicit AsyncFuture(Functor&& fn)
	{
		// 在任务组中执行工作函数，并存储结果到 single_assignment 对象中
		_tasks.run([fn, this]() -> void { send(_value, fn()); });
	}

	~AsyncFuture()
	{
		// 等待任务完成
		_tasks.wait();
	}

	T get()
	{
		// 等待结果完成
		// wait 方法可以重新抛出生成的工作函数引发的异常信息
		// 如果不加这一句，在没有异常的情况下，结果是一样的
		// 在有异常发生时，程序会一直等待，不输出结果
		_tasks.wait();

		return receive(_value);
	}

private:
	task_group _tasks; // 执行异步工作函数
	single_assignment<T> _value; // 存储异步工作函数的结果
};


int wmain()
{
	unsigned const upper = 10000u;
	std::mt19937 gen(1u);

	// 创建数组，每个元素都在 [0, upper) 之内
	vector<unsigned> values(upper);
	std::generate(values.begin(), values.end(), \
		[&gen, upper]() -> unsigned { return gen() % upper; });

	// 创建异步对象，寻找数组中的最小值
	AsyncFuture<unsigned> minval([&values]() -> unsigned
	{
		unsigned ans = INT_MAX;
		std::for_each(values.begin(), values.end(), \
			[&ans](unsigned val) -> void { if (val < ans) ans = val; });
		return ans;
	});

	// 创建异步对象，寻找数组中的最小值
	AsyncFuture<unsigned> maxval([&values]() -> unsigned
	{
		unsigned ans = 0u;
		std::for_each(values.begin(), values.end(), \
			[&ans](unsigned val) -> void { if (val > ans) ans = val; });
		return ans;
	});

	// 计算数组的平均值，同时异步对象在后台运行
	unsigned sum = std::accumulate(values.begin(), values.end(), 0u);
	unsigned average = sum / (unsigned)(values.size());

	// 输出结果
	wcout << L"minval = " << minval.get() << endl << \
		L"maxval = " << maxval.get() << endl << \
		L"average = " << average << endl;

	// 创建一个异步对象，工作函数中抛出异常
	AsyncFuture<unsigned> afex(
		[]() -> unsigned { throw std::exception("afex - error"); });

	// 尝试读取异步结果
	try
	{
		unsigned val = afex.get();
		wcout << L"afex return value: " << val << endl;
	}
	catch (std::exception const& e)
	{
		wcout << L"caught exception: " << e.what() << endl;
	}
}
