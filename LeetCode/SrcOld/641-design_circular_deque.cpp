#include "leetcode.hpp"

/* 641. 设计循环双端队列

设计实现双端队列。
你的实现需要支持以下操作：
		MyCircularDeque(k)：构造函数,双端队列的大小为k。
		insertFront()：将一个元素添加到双端队列头部。 如果操作成功返回 true。
		insertLast()：将一个元素添加到双端队列尾部。如果操作成功返回 true。
		deleteFront()：从双端队列头部删除一个元素。 如果操作成功返回 true。
		deleteLast()：从双端队列尾部删除一个元素。如果操作成功返回 true。
		getFront()：从双端队列头部获得一个元素。如果双端队列为空，返回 -1。
		getRear()：获得双端队列的最后一个元素。 如果双端队列为空，返回 -1。
		isEmpty()：检查双端队列是否为空。
		isFull()：检查双端队列是否满了。

示例：

MyCircularDeque circularDeque = new MycircularDeque(3); // 设置容量大小为3
circularDeque.insertLast(1);			        // 返回 true
circularDeque.insertLast(2);			        // 返回 true
circularDeque.insertFront(3);			        // 返回 true
circularDeque.insertFront(4);			        // 已经满了，返回 false
circularDeque.getRear();  				// 返回 2
circularDeque.isFull();				        // 返回 true
circularDeque.deleteLast();			        // 返回 true
circularDeque.insertFront(4);			        // 返回 true
circularDeque.getFront();				// 返回 4

提示：
	所有值的范围为 [1, 1000]
	操作次数的范围为 [1, 1000]
	请不要使用内置的双端队列库。
*/

class MyCircularDeque
{
	int const K;
	int* ptr;
	int idx, size;

public:
	/** Initialize your data structure here. Set the size of the deque to be k. */
	MyCircularDeque(int k)
		: K(k)
		, ptr(nullptr)
		, idx(0)
		, size(0)
	{
		if (K)
			ptr = static_cast<int*>(malloc(K * sizeof(int)));
	}

	~MyCircularDeque()
	{
		if (K)
			free(ptr);
	}

	/** Adds an item at the front of Deque. Return true if the operation is successful. */
	bool insertFront(int value)
	{
		if (size == K)
			return false;
		idx = (idx - 1 + K) % K;
		ptr[idx] = value;
		++size;
		return true;
	}

	/** Adds an item at the rear of Deque. Return true if the operation is successful. */
	bool insertLast(int value)
	{
		if (size == K)
			return false;
		ptr[(idx + size) % K] = value;
		++size;
		return true;
	}

	/** Deletes an item from the front of Deque. Return true if the operation is successful. */
	bool deleteFront()
	{
		if (size == 0)
			return false;
		idx = (idx + 1) % K;
		--size;
		return true;
	}

	/** Deletes an item from the rear of Deque. Return true if the operation is successful. */
	bool deleteLast()
	{
		if (size == 0)
			return false;
		--size;
		return true;
	}

	/** Get the front item from the deque. */
	int getFront()
	{
		return size ? ptr[idx] : -1;
	}

	/** Get the last item from the deque. */
	int getRear()
	{
		return size ? ptr[(idx + size - 1) % K] : -1;
	}

	/** Checks whether the circular deque is empty or not. */
	bool isEmpty()
	{
		return size == 0;
	}

	/** Checks whether the circular deque is full or not. */
	bool isFull()
	{
		return size == K;
	}
};


int main()
{
	MyCircularDeque d(3);
	OutExpr(boolstr[d.insertLast(1)], "%s");
	OutExpr(boolstr[d.insertLast(2)], "%s");
	OutExpr(boolstr[d.insertFront(3)], "%s");
	OutExpr(boolstr[d.insertFront(4)], "%s");
	OutExpr(d.getRear(), "%d");
	OutExpr(boolstr[d.isFull()], "%s");
	OutExpr(boolstr[d.deleteLast()], "%s");
	OutExpr(boolstr[d.insertFront(4)], "%s");
	OutExpr(d.getFront(), "%d");
}
