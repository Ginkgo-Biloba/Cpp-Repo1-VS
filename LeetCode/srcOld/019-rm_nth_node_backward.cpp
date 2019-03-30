#include <cstdio>
#include <cstdlib>

/* 单向链表 */
struct ListNode
{
	int val;
	ListNode* next;

	ListNode(int x) : val(x), next(nullptr) {};
};

ListNode* genList(int x)
{
	if (x < 1) return nullptr;
	ListNode* head = new ListNode(x);
	fprintf(stdout, "%2d  ", head->val);
	ListNode* p = head, *q;
	for (x--; x > 0; x--)
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

/* q 先往前走 n + 1 步，然后当 q 到末尾时，p 正好到倒数第 n + 1 个节点*/
ListNode* rmNthFromEnd(ListNode* head, int n)
{
	if (n <= 0) return head;
	ListNode* p = head, *q = head;
	for (; n >= 0 && q != nullptr; n--)
		q = q->next;

	/* n 太大 */
	if (n >= 0)
	{
		p = head->next;
		delete head;
		head = p;
	}
	else
	{
		while (q != nullptr)
		{
			p = p->next;
			q = q->next;
		}
		q = p->next;
		p->next = q->next;
		delete q;
	}
	return head;
}

int main()
{
	int const x = 10;
	ListNode* head = genList(x);
	head = rmNthFromEnd(head, 3);
	delList(head);
	return 0;
}