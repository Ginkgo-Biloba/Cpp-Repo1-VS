#include "leetcode.hpp"

/* 21. 合并两个有序链表

将两个升序链表合并为一个新的升序链表并返回。
新链表是通过拼接给定的两个链表的所有节点组成的。

示例：
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
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

ListNode* mergeTwoLists(ListNode* A, ListNode* B)
{
	ListNode root(-1);
	ListNode* C = &root;
	while (A && B)
	{
		if (A->val < B->val)
		{
			C->next = A;
			A = A->next;
		}
		else
		{
			C->next = B;
			B = B->next;
		}
		C = C->next;
	}
	if (B)
		A = B;
	C->next = A;
	return root.next;
}

int main()
{}
