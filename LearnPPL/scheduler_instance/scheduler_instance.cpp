/* https://msdn.microsoft.com/zh-cn/library/ee513829.aspx
 * 第一个示例使用 concurrency::CurrentScheduler 类创建计划程序实例
 * 并将该实例与当前上下文关联
 * 第二个示例使用 concurrency::Scheduler 类执行相同任务
 * 通常，CurrentScheduler 类用于处理当前计划程序
 * 如果您希望控制计划程序与当前上下文关联的时间
 * 或者希望将特定计划程序与特定任务关联
 * 则第二个示例（使用 Scheduler 类）很有用 */

#include <Windows.h>
#include <ppl.h>
using namespace Concurrency;
#include <iostream>
using std::wcout; using std::endl;


/** 输出当前计划的标识符 */
void runTask()
{
	task_group tasks;
	// 以组运行任务，当前计划执行任务
	tasks.run_and_wait([]() -> void
	{ wcout << L"Current scheduler id: " << CurrentScheduler::Id() << endl; });
}


/** 使用 CurrentScheduler 管理计划实例 */
void currentScheduler()
{
	// 运行任务，输出默认计划的 id
	runTask();

	// 为了演示，创建计划对象，使用默认策略
	wcout << L"Create and attach scheduler..." << endl;
	CurrentScheduler::Create(SchedulerPolicy());
	
	// 注册事件，当计划结束的时候通知
	HANDLE hShutdown = CreateEventW(NULL, FALSE, FALSE, NULL);
	CurrentScheduler::RegisterShutdownEvent(hShutdown);

	// 再次运行任务，输出当前计划的 id
	runTask();

	// 分离当前计划，这会恢复前一个计划
	wcout << L"Detach scheduler..." << endl;
	CurrentScheduler::Detach();

	// 等待计划任务结束并自动销毁
	WaitForSingleObject(hShutdown, INFINITE);

	// 关闭事件
	CloseHandle(hShutdown);
	
	// 再次运行任务，输出当前计划的 id
	runTask();
}


/** 使用 Scheduler 管理计划实例 */
void explicitScheduler()
{
	// 运行任务，输出默认计划的 id
	runTask();

	// 为了演示，创建计划对象，使用默认策略
	wcout << L"Create scheduler..." << endl;
	Scheduler* schd = Scheduler::Create(SchedulerPolicy());

	// 注册事件，当计划结束的时候通知
	HANDLE hShutdown = CreateEventW(NULL, FALSE, FALSE, NULL);
	schd->RegisterShutdownEvent(hShutdown);
	
	// 关联计划到当前线程
	wcout << L"Attach scheduler..." << endl;
	schd->Attach();

	// 再次运行任务，输出新计划的 id
	runTask();

	// 分离当前计划，这会恢复前一个计划
	wcout << L"Detach scheduler..." << endl;
	CurrentScheduler::Detach();

	// 释放最终到 schd 的引用，这会使 schd 在所有任务完成后停止
	schd->Release();

	// 等待计划任务结束并自动销毁
	WaitForSingleObject(hShutdown, INFINITE);

	// 关闭事件
	CloseHandle(hShutdown);

	// 再次运行任务，显示当前计划的 id
	runTask();
}


int wmain()
{
	wcout << L"===== Using CurrentScheduler class =====" << endl;
	currentScheduler();

	wcout << "\n" << endl;

	wcout << L"===== Using Scheduler class =====" << endl;
	explicitScheduler();
}


