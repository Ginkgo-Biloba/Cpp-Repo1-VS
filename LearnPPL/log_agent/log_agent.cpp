#include <Windows.h>
#include <agents.h>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace Concurrency;
using std::wstring;
using std::wofstream; using std::wostream;
using std::wstringstream;

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


/** 定义信息类型 */
enum LogMessageType
{
	Log_Info = 0x1,
	Log_Warning = 0x2,
	Log_Error = 0x4,
};


/** 异步日志代理，写日志到文件和控制台 */
class LogAgent : public agent
{
	struct LogMessage
	{
		wstring message;
		LogMessageType type;
	};

public:
	LogAgent(wstring const& filePath, LogMessageType fileType, LogMessageType consoleType)
		: file(filePath, std::wios::trunc), filetype(fileType), contype(consoleType), active(0u)
	{
		if (file.bad())
			throw std::invalid_argument("can not open log file");
	}

	/** 写信息到 log */
	void log(wstring const& message, LogMessageType type)
	{
		active.addCount();
		LogMessage msg = { message, type };
		send(logbuf, msg);
	}

	void close()
	{
		closed.set();
	}

private:
	void writeToStream(LogMessage const& msg, std::wostream& wos)
	{
		wstringstream wss;
		switch (msg.type)
		{
		case Log_Info: 
			wss << L"Info:    "; break;
		case Log_Warning: 
			wss << L"Warning: "; break;
		case Log_Error:
			wss << L"Error:   "; // break;
		}
		wss << msg.message << std::endl;
		wos << wss.str();
	}

protected:
	void run()
	{
		/// 创建数据流

		// 写日志到文件
		call<LogMessage> writer([this](LogMessage const& msg) -> void
		{
			if (msg.type & filetype)
				writeToStream(msg, file);
			if (msg.type & contype)
				writeToStream(msg, std::wcout);

			active.signal();
		});

		// 连接缓冲区到网络中的数据流
		logbuf.link_target(&writer);
		closed.wait();
		active.wait();

		file.close();
		std::wcout.flush();

		done();
	}

private:
	wofstream file;
	LogMessageType filetype;
	LogMessageType contype;
	unbounded_buffer<LogMessage> logbuf;
	CountDownEvent active;
	event closed;
};


int wmain()
{
	LogMessageType logAll = LogMessageType(Log_Info | Log_Warning | Log_Error);

	LogAgent logger(L"log.txt", Log_Error, logAll);
	logger.start();

	logger.log(L"This is a sample warning message", Log_Warning);
	logger.log(L"This is a sample error message", Log_Error);
	logger.log(L"===== Logging finished =====", Log_Info);

	logger.close();
	agent::wait(&logger);
}
