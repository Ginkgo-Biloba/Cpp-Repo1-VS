// https://msdn.microsoft.com/zh-cn/library/ff398051.aspx

#include <Windows.h>
#include <agents.h>
using namespace Concurrency;

#include <iostream>
#include <random>
using std::wcout; using std::flush; using std::endl;


/** 基本代理，使用控制流来调节程序的执行顺序
 * 代理从消息块中读取数字，并统计正数和负数的个数 */
class CtrlFlowAgent : public agent
{
public:
	explicit CtrlFlowAgent(ISource<int>& source)
		: src(source)
	{}

	// 检索正数和负数个数
	unsigned negatives() { return receive(neg); }
	unsigned positives() { return receive(pos); }

protected:
	void run()
	{
		unsigned posN = 0u, negN = 0u;

		int val;
		while ((val = receive(src)) != 0)
		{
			if (val < 0) ++negN;
			else ++posN;
		}

		send(pos, posN);
		send(neg, negN);

		done();
	}

private:
	ISource<int>& src;
	single_assignment<unsigned> pos;
	single_assignment<unsigned> neg;
};


/** 同步原语，当计数为 0 时接收到信号 */
class CountDownEvent
{
public:
	explicit CountDownEvent(unsigned count = 0u)
		: cur(static_cast<long>(count))
	{
		if (cur == 0l)
			event0.set();
	}


	void signal()
	{
		if (_InterlockedDecrement(&cur) == 0l)
			event0.set();
	}

	void addCount()
	{
		if (_InterlockedIncrement(&cur) == 1l)
			event0.reset();
	}

	void wait()
	{
		event0.wait();
	}

private:
	volatile long cur; // 当前数量
	event event0; // 当计数为 0 时事件被触发
	CountDownEvent(CountDownEvent const&) {}
	CountDownEvent& operator =(CountDownEvent const&) {}
};


/** 基本代理，类似 CtrlFlowAgent，当数据可用时使用数据流来执行计算 */
class DataFlowAgent : public agent
{
public:
	explicit DataFlowAgent(ISource<int>& source)
		: src(source)
	{}

	size_t negatives()
	{
		return receive(neg);
	}

	size_t positives()
	{
		return receive(pos);
	}

protected:
	void run()
	{
		// 计数接收到的正负数
		size_t posN = 0u, negN = 0u;

		// 跟踪计数事件
		CountDownEvent active;
		// 被哨兵设置的事件
		event receivedSentinel;

		/// 创建数据流网络

		// 递增活动计数
		transformer<int, int> increaseActive(
			[&active](int val) -> int { active.addCount(); return val; });

		// 递增负数
		call<int> negatives(
			[&negN, &active](int val) -> void { ++negN; active.signal(); },
			[](int val) -> bool { return val < 0; });

		// 递增正数
		call<int> positives(
			[&posN, &active](int val) -> void { ++posN; active.signal(); },
			[](int val) -> bool { return val > 0; });

		// 只有当哨兵值是 0 的时候才接收
		call<int> sentinel(
			[&active, &receivedSentinel](int val) -> void { active.signal(); receivedSentinel.set(); },
			[](int val) -> bool { return val == 0; });

		// 连接 src 信息缓冲到网络
		unbounded_buffer<int> connector;

		/// 连接到网络

		// 连接内部节点
		connector.link_target(&negatives);
		connector.link_target(&positives);
		connector.link_target(&sentinel);
		increaseActive.link_target(&connector);

		// 连接 src 缓冲到内部网络
		src.link_target(&increaseActive);

		// 等待哨兵事件，等待完成所有操作
		receivedSentinel.wait();
		active.wait();

		// 写入计数值到缓冲区
		send(neg, negN);
		send(pos, posN);

		// 设置代理状态
		done();
	}


private:
	ISource<int>& src;
	single_assignment<size_t> neg;
	single_assignment<size_t> pos;
};


/** 发送一定数量的随机数到提供的信息缓冲区 */
void sendValue(ITarget<int>& src, int sentinel, size_t count)
{
	std::mt19937 gen(42);
	for (size_t u = 0u; u < count; ++u)
	{
		int n;
		do { n = static_cast<int>(gen()); } while (n == sentinel);
		send(src, n);
	}
	send(src, sentinel);
}


int wmain()
{
	// 信号，没有更多数字可以处理了
	int const sentinel = 0;
	// 发送给每个代理的样本数量
	size_t const count = 1000000u;

	// 缓冲，应用往里写，代理从里面读
	unbounded_buffer<int> source;

	wcout << L"Control-flow agent: " << endl;

	// 创建并启动代理
	CtrlFlowAgent cfa(source);
	cfa.start();

	// 发送数字
	sendValue(source, sentinel, count);

	// 等待代理结束
	agent::wait(&cfa);

	// 输出正负数的个数
	wcout << L"Negative: " << cfa.negatives() << "\n";
	wcout << L"Positive: " << cfa.positives() << "\n";

	// 执行相同的任务，但这次使用数据代理
	wcout << L"Data-flow agent: " << endl;

	DataFlowAgent dfa(source);
	dfa.start();
	sendValue(source, sentinel, count);
	agent::wait(&dfa);
	wcout << L"Negative: " << dfa.negatives() << "\n";
	wcout << L"Positive: " << dfa.positives() << "\n";
}
