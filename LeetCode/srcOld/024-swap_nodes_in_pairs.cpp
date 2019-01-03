#include <cstdio>
#include <cstdlib>
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

ListNode* mergekSortedList(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return head;
	ListNode *p, *q, *r, *s;

	/* 处理开头 */
	q = head; r = q->next; s = r->next;
	r->next = q; q->next = s;
	head = r; p = q;

	/* 剩下的 */
	while (s != nullptr && s->next != nullptr)
	{
		q = s; r = q->next; s = r->next;
		p->next = r; r->next = q; q->next = s;
		p = q;
	}

	return head;
}


int main()
{
	ListNode* x = genList(1, 2, 1);
	ListNode* z = mergekSortedList(x);
	delList(z);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}

