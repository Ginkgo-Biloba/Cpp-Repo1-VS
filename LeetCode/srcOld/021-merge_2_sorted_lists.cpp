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

ListNode* merge2SortedList(ListNode* x, ListNode* y)
{
	if (x == nullptr) return y;
	if (y == nullptr) return x;
	ListNode* ans, *z;

	/* 抽取第一个 */
	if (x->val <= y->val)
	{ ans = x; x = x->next; }
	else
	{ ans = y; y = y->next; }
	z = ans;

	while (x != nullptr && y != nullptr)
	{
		if (x->val <= y->val)
		{
			z->next = x;
			x = x->next;
		}
		else
		{
			z->next = y;
			y = y->next;
		}
		z = z->next;
	}

	/* 拼接剩余的 */
	if (x != nullptr) z->next = x;
	else z->next = y;

	return ans;
}


int main()
{
	ListNode* x = genList(5, 18, 3);
	ListNode* y = genList(9, 17, 2);
	ListNode* z = merge2SortedList(x, y);
	delList(z);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}

