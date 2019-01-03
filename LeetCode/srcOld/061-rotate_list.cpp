#define _CRT_MAP_ALLOC
#include <cstdio>
#include <stdlib.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

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

ListNode* rotateRight(ListNode* head, int k)
{
	if (!k || !head) return head;

	int len = 0;
	ListNode* ptr = head;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		len++;
	}
	k = len - k % len; // 右移变左移
	if (!k || k == len) return head;

	ptr = head;
	for (int i = 0; i < k - 1; i++)
		ptr = ptr->next;

	ListNode* newHead = ptr->next;
	ptr->next = NULL;
	ptr = newHead;
	while (ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = head;
	return newHead;
}


int main()
{
	ListNode* x = genList(1, 2, 1);
	ListNode* z = rotateRight(x, 1);
	delList(z);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}



