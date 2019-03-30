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

/* head 到末尾有没有 k 个元素，tail 指向第 k 个元素，闭区间 */
char hasK(ListNode* head, ListNode*& tail, int k)
{
	int i; /* 闭区间从 1 开始 */
	for (i = 1; i < k && head != nullptr; i++)
		head = head->next;
	if (i < k || head == nullptr)
	{ tail = nullptr; return (char)(0); }
	else
	{ tail = head; return (char)(1); }
}

/* 反转链表区间，闭区间包含 head 和 tail */
void reverse(ListNode* head, ListNode* tail)
{
	if (head == nullptr || tail == nullptr) return;
	ListNode* p, *q, *r, *s;
	p = head; q = head->next; s = tail->next;
	while (q != s)
	{
		r = q->next; /* 保存下一个位置 */
		q->next = p; p = q; /* 交换 */
		q = r; /* 下一个位置 */
	}
	/* tail = head; head = p; */ /* 貌似不需要 */
}

ListNode* revNodesInKGps(ListNode* head, int k)
{
	if (head == nullptr || head->next == nullptr || k < 2)
		return head;
	ListNode *p, *q, *r, *s = nullptr;
	char needRev;

	/* 开头的 */
	q = head;
	needRev = hasK(q, r, k);
	if (needRev)
	{
		s = r->next;
		reverse(q, r);
		q->next = s;
		head = r;
	}
	else
		return head;

	/* 剩下的 */
	while (s != nullptr)
	{
		p = q; q = s; /* 前行一步 */
		needRev = hasK(q, r, k);
		if (needRev)
		{
			s = r->next;
			reverse(q, r);
			p->next = r; q->next = s;
		}
		else break;
	}

	return head;
}


int main()
{
	ListNode* x = genList(1, 6, 1);
	ListNode* z = revNodesInKGps(x, 7);
	delList(z);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}

