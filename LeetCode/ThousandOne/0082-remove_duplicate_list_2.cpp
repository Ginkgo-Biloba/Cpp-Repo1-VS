#include "leetcode.hpp"

/* 82. 删除排序链表中的重复元素 II

给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。

示例 1:
输入: 1->2->3->3->4->4->5
输出: 1->2->5

示例 2:
输入: 1->1->1->2->3
输出: 2->3
*/


// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode* next;
	ListNode()
		: val(0)
		, next(nullptr)
	{}
	ListNode(int x)
		: val(x)
		, next(nullptr)
	{}
	ListNode(int x, ListNode* next)
		: val(x)
		, next(next)
	{}
};

ListNode* deleteDuplicates(ListNode* head)
{
	if (!head || !(head->next))
		return head;
	ListNode root(-1, head);
	ListNode *p = &root, *q = head, *r;
	int n = 0;
	for (; q; q = r)
	{
		n = 1;
		r = q->next;
		for (; r; r = r->next)
		{
			if (q->val != r->val)
				break;
			++n;
		}
		if (n == 1)
		{
			p->next->val = q->val;
			p = p->next;
		}
	}
	p->next = nullptr;
	return root.next;
}


int main()
{}
