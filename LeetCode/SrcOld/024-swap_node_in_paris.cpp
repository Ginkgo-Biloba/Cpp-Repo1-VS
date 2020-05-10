#include "leetcode.hpp"

/* 24. 两两交换链表中的节点

给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
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


ListNode* swapPairs(ListNode* head)
{
	if (!head || !(head->next))
		return head;
	ListNode root(-1);
	ListNode* h = &root;
	h->next = head;
	while (h->next && h->next->next)
	{
		ListNode
			*p = h->next,
			*q = p->next,
			*r = q->next;
		h->next = q;
		q->next = p;
		p->next = r;
		h = p;
	}
	return root.next;
}


int main()
{}
