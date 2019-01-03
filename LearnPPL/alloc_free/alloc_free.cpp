/** https://msdn.microsoft.com/zh-cn/library/dd998050.aspx
 * Alloc 和 Free 函数在多个线程频繁调用 Alloc 和 Free 时非常有用
 * 由于运行时为每个线程保留单独的内存缓存
 * 因此无需使用锁或内存屏障即可管理内存 */
#include <ppl.h>
#include <Windows.h>
#include <iostream>
using std::wcout; using std::flush; using std::endl;
using namespace Concurrency;

/** 重载 new 和 delete 运算符，调用全局版本 */
class NewDelete
{
public:
	static void* operator new(size_t size)
	{
		return ::operator new(size);
	}

		static void operator delete(void* p)
	{
		return ::operator delete(p);
	}

	int data;
};


/** 重载 new 和 delete 运算符，调用 C 运行时的 malloc 和 free */
class MallocFree
{
public:
	static void* operator new(size_t size)
	{
		return std::malloc(size);
	}

		static void operator delete(void* p)
	{
		return std::free(p);
	}

	int data;
};


/** 重载 new 和 delete 运算符，调用并发运行时的 Alloc 和 Free */
class AllocFree
{
public:
	static void* operator new(size_t size)
	{
		return Concurrency::Alloc(size);
	}

		static void operator delete(void* p)
	{
		return Concurrency::Free(p);
	}

	int data;
};


/** swap 函数将交换指定索引处的数组的内容
 * 此函数将为临时变量分配堆中的内存 */
template<class T>
void swap(T* ptr, int l, int r)
{
	// 为了展示效果，从堆收集内存。当 sizeof(T) 很大时这很有用
	T* t = new T;
	*t = ptr[l]; ptr[l] = ptr[r]; ptr[r] = *t;
	delete t;
}


template<class Func>
uint32_t timeCall(Func&& func)
{
	uint32_t begin = GetTickCount();
	func();
	return GetTickCount() - begin;
}


/** 计算反转大数组中元素花费的时间 */
template<class T>
uint32_t reverseArray()
{
	int const sz = 5000000;
	int const repeat = 11;
	T* ptr = new T[sz];
	uint32_t total = 0;

	for (int i = 0; i < repeat; ++i)
	{
		total += timeCall([ptr, sz]() -> void
		{
			parallel_for(0, sz / 2, [ptr, sz](int l) -> void
			{ swap(ptr, l, sz - l - 1); });
		});
	}

	delete[] ptr;
	return total;
}


int wmain()
{
	wcout << L"new/delete took " << reverseArray<NewDelete>() << "ms" << endl;
	wcout << L"malloc/free took " << reverseArray<MallocFree>() << "ms" << endl;
	wcout << L"Alloc/Free took " << reverseArray<AllocFree>() << "ms" << endl;
}



