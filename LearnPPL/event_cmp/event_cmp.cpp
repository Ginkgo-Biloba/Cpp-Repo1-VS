// https://msdn.microsoft.com/zh-cn/library/dd759350.aspx
/* 本示例使计划程序最多能够创建两个同时发生的任务
 * 然后调用使用 event 类和 Windows 手动重置事件的两个相似函数
 * 每个函数首先创建一些等待共享事件变为终止状态的任务
 * 接着，每个函数让位于正在运行的任务，并用信号通知该事件
 * 然后，每个函数将等待终止的事件 */

#include <Windows.h>
#include <concrtrm.h>
#include <ppl.h>
using namespace Concurrency;
using namespace std;

#include <iostream>
#include <sstream>


/** 展示协作事件的使用 */
void runCooperativeEvents()
{
	event e;

	// 创建任务组，执行 5 个任务，等待事件触发
	task_group tasks;
	for (int i = 0; i < 5; ++i)
	{
		tasks.run([&e]() -> void
		{
			wstringstream wss;
			wss << L"\tContext " << GetExecutionContextId() << \
				L": waiting on an event" << endl;
			wcout << wss.str();

			// 等待事件触发，然后输出消息
			e.wait(); 
			wss.str(L"");
			wss << L"\tContext " << GetExecutionContextId() << \
				L": received an event" << endl;
			wcout << wss.str();
		});
	}

	// 等待足够的时间，使得所有任务都进入等待状态
	Sleep(1000);

	// 设置事件
	wstringstream wss;
	wss << L"Setting the event" << endl;
	wcout << wss.str();
	e.set();

	tasks.wait();
}


/** 展示抢占事件的使用 */
void runWindowsEvents()
{
	HANDLE hEvent = CreateEventW(NULL, TRUE, FALSE, TEXT("Windows Event"));

	// 创建任务组，执行 5 个任务，等待事件触发
	task_group tasks;
	for (int i = 0; i < 5; ++i)
	{
		tasks.run([hEvent]() -> void
		{
			wstringstream wss;
			wss << L"\tContext " << GetExecutionContextId() << \
				L": waiting on an event" << endl;
			wcout << wss.str();

			// 等待事件触发，然后输出消息
			WaitForSingleObject(hEvent, INFINITE);
			wss.str(L"");
			wss << L"\tContext " << GetExecutionContextId() << \
				L": received an event" << endl;
			wcout << wss.str();
		});
	}

	// 等待足够的时间，使得所有任务都进入等待状态
	Sleep(1000);

	// 设置事件
	wstringstream wss;
	wss << L"Setting the event" << endl;
	wcout << wss.str();
	SetEvent(hEvent);

	tasks.wait();
	CloseHandle(hEvent);
}


int wmain()
{
	// 创建一个计划方式，允许同时最多两个任务
	SchedulerPolicy policy(1, MaxConcurrency, 2);
	// 附加方式到当前计划
	CurrentScheduler::Create(policy);

	wcout << L"Cooperative event: \n";
	runCooperativeEvents();

	wcout << L"Windows event: \n";
	runWindowsEvents();
}
