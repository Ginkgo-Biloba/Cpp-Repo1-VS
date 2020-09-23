#include "leetcode.hpp"

/* 234. 回文链表

请判断一个链表是否为回文链表。

示例 1:
输入: 1->2
输出: false

示例 2:
输入: 1->2->2->1
输出: true

进阶：
你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？。
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


ListNode* revlist(ListNode* node)
{
	ListNode *pre = NULL, *cur;
	while (node)
	{
		cur = node;
		node = node->next;
		cur->next = pre;
		pre = cur;
	}
	return pre;
}


bool isPalindrome(ListNode* head)
{
	if (!(head && head->next))
		return true;

	ListNode root(1);
	ListNode *p = &root, *q = p;
	root.next = head;
	while (q && q->next)
	{
		p = p->next;
		q = q->next->next;
	}
	ListNode* mid = p;
	root.next = q = revlist(p->next);
	p = head;
	while (q)
	{
		if (p->val != q->val)
		{
			root.val = 0;
			break;
		}
		p = p->next;
		q = q->next;
	}
	mid->next = revlist(root.next);
	return root.val != 0;
}


int main()
{}
