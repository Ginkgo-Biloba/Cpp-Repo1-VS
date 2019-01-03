#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <queue>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

/* 单向链表 */
struct ListNode
{
	int val;
	ListNode* next;

	ListNode(int x) : val(x), next(nullptr) {};
};

struct LNCmpPtr
{
	/* 先出小的，即小的优先级高，所以是大于号 > */
	bool operator()(ListNode const* x, ListNode const* y)
	{ return (x->val > y->val); }
};

ListNode* genList(int x = 0, int y = 10, int step = 1)
{
	if ((step > 0 && y - step < x) || (step < 0 && y - step > x))
		return nullptr;
	int yh = (y - x + step - 1) / step * step + x;
	ListNode* head = new ListNode(x);
	fprintf(stdout, "%2d  ", head->val);
	ListNode* p = head, *q;
	for (x += step; x != yh; x += step)
	{
		q = new ListNode(x);
		fprintf(stdout, "%2d  ", q->val);
		p->next = q;
		p = q;
	}
	fprintf(stdout, "\n");
	return head;
}

void delList(ListNode* head)
{
	ListNode* p;
	while (head != nullptr)
	{
		p = head->next;
		fprintf(stdout, "%2d  ", head->val);
		delete head;
		head = p;
	}
	fprintf(stdout, "\n");
}

/* 不带参数个数检查，自己保证吧 */
ListNode* mergekSortedList(int sz, ...)
{
	ListNode* ans, *z;
	std::priority_queue<ListNode*, std::vector<ListNode*>, LNCmpPtr> pq;

	/* 拿到指针列表，扔进优先队列 */
	va_list ap; va_start(ap, sz);
	int i;
	for (i = 0; i < sz; i++)
	{
		z = va_arg(ap, ListNode*);
		if (z != nullptr) pq.push(z);
	}
	va_end(ap);
	if (pq.empty()) return nullptr;

	/* 拿到第一个（开头） */
	ans = pq.top(); pq.pop();
	if (ans->next != nullptr) pq.push(ans->next);
	z = ans;

	/* 弹出剩余的 */
	while (!pq.empty())
	{
		z->next = pq.top(); pq.pop();
		z = z->next;
		if (z->next != nullptr) pq.push(z->next);
	}

	return ans;
}


int main()
{
	ListNode* x1 = genList(5, 18, 3);
	ListNode* x2 = genList(9, 17, 2);
	ListNode* x3 = genList(1, 13, 4);
	ListNode* x4 = genList(12, 17, 1);
	ListNode* z = mergekSortedList(4, x1, x2, x3, x4);
	delList(z);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}

