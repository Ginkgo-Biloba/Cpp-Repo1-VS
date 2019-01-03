// https://msdn.microsoft.com/zh-cn/library/dd492627.aspx

#include <agents.h>
using namespace Concurrency;

#include <string>
#include <iostream>
#include <sstream>
using std::wstring;
using std::wcout; using std::endl;
using std::wstringstream;


/** 代理 S 写字符串到目标，然后读回一个整数 */
class AgentS : public agent
{
public:
	explicit(AgentS(ISource<int>& source, ITarget<wstring>& target))
		: src(source), dst(target)
	{}

protected:
	void run()
	{
		// 发送请求
		wstringstream wss;
		wss << L"AgentS: sending wstring..." << endl;
		wcout << wss.str();
		send(dst, wstring(L"wstring"));

		// 读取回应
		int response = receive(src);
		wss.str(L"");
		wss << L"AgentS: received " << response << L"." << endl;
		wcout << wss.str();

		// 将代理设为完成状态
		done();
	}

private:
	ISource<int>& src;
	ITarget<wstring>& dst;
};


/** 代理 I 读取字符串，并发送整数 */
class AgentI : public agent
{
public:
	explicit(AgentI(ISource<wstring>& source, ITarget<int>& target))
		: src(source), dst(target)
	{}

protected:
	void run()
	{
		// 读取回应
		wstring response = receive(src);
		wstringstream wss;
		wss << L"AgentI: received " << response << L"." << endl;
		wcout << wss.str();

		// 发送请求
		wss.str(L"");
		wss << L"AgentI: sending int..." << endl;
		wcout << wss.str();
		send(dst, 42);

		// 将代理设为完成状态
		done();
	}


private:
	ISource<wstring>& src;
	ITarget<int>& dst;
};


int wmain()
{
	/* 1 创建两个消息缓冲，作为两个代理之间的通信管道 */

	// 第一个代理写消息到缓冲区，第二个代理从缓冲区读取消息
	unbounded_buffer<wstring> wsbuf;
	// 第一个代理从缓冲区读取消息，第二个代理写消息到缓冲区
	overwrite_buffer<int> intbuf;

	/* 2 创建代理 */
	AgentS agents(intbuf, wsbuf);
	AgentI agenti(wsbuf, intbuf);

	/* 3 启动代理，运行时调用每个代理上的 run 方法 */
	agents.start();
	agenti.start();

	/* 4 等待所有代理结束 */
	agent::wait(&agents);
	agent::wait(&agenti);
}



