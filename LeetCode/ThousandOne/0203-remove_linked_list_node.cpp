#include "leetcode.hpp"

/* 203. 移除链表元素

删除链表中等于给定值 val 的所有节点。

示例:
输入: 1->2->6->3->4->5->6, val = 6
输出: 1->2->3->4->5
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

ListNode* removeElements(ListNode* head, int val)
{
	ListNode root(-1);
	root.next = head;
	ListNode *p = &root, *q = p->next;
	while (q)
	{
		if (q->val == val)
		{
			p->next = q->next;
			// delete q
		}
		else
			p = p->next;
		q = q->next;
	}
	return root.next;
}


int main()
{}
