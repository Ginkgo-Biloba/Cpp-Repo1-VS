#include "leetcode.hpp"

/* 25. K 个一组翻转链表

给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

示例：
给你这个链表：1->2->3->4->5
当 k = 2 时，应当返回: 2->1->4->3->5
当 k = 3 时，应当返回: 3->2->1->4->5

说明：
	你的算法只能使用常数的额外空间。
	你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x)
		: val(x)
		, next(NULL)
	{}
};

ListNode* reverseKGroup(ListNode* head, int k)
{
	if (k < 2)
		return head;
	ListNode root(-1);
	ListNode* a = &root;
	root.next = head;
	while (a)
	{
		int i = 0;
		ListNode *z = a, *p, *q, *r;
		for (; (i <= k) && z; ++i)
			z = z->next;
		if (i <= k)
			break;
		p = a;
		q = a->next;
		while (q != z)
		{
			r = q->next;
			q->next = p;
			p = q;
			q = r;
		}
		q = a->next;
		q->next = z;
		a->next = p;
		a = q;
	}
	return root.next;
}


int main()
{}
