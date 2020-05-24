#include "leetcode.hpp"

/* 143. 重排链表

给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例 1:
给定链表 1->2->3->4, 重新排列为 1->4->2->3.

示例 2:
给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
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

void reorderList(ListNode* head)
{
	ListNode dummy(0);
	ListNode *slow = head, *fast = head;

	// len <= 2 不操作
	if (!(head && head->next && head->next->next))
		return;

	// 找到中点
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	// 断开
	fast = slow->next;
	slow->next = nullptr;

	// 翻转后半部分
	ListNode* prev = nullptr;
	if (fast && fast->next)
	{
		while (fast)
		{
			ListNode* next = fast->next;
			fast->next = prev;
			prev = fast;
			fast = next;
		}
		fast = prev;
	}

	// 合并
	slow = head;
	prev = &dummy;
	while (slow && fast)
	{
		ListNode *s = slow->next;
		prev->next = slow;
		slow->next = fast;
		prev = fast;
		slow = s;
		fast = fast->next;
	}
	// 奇数情况
	if (slow)
		prev->next = slow;

	head = dummy.next;
}


int main()
{}
