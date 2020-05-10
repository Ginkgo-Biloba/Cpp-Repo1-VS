#include "leetcode.hpp"

/* 92. 反转链表 II

反转从位置 m 到 n 的链表。
请使用一趟扫描完成反转。

说明:
1 ≤ m ≤ n ≤ 链表长度。

示例:
输入: 1->2->3->4->5->NULL, m = 2, n = 4
输出: 1->4->3->2->5->NULL
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

// https://leetcode.com/problems/reverse-linked-list-ii/discuss/30666/Simple-Java-solution-with-clear-explanation
// 抄的
ListNode* reverseBetween(ListNode* head, int m, int n)
{
	if (!head || (m == n))
		return head;
	ListNode root(-1);
	root.next = head;
	ListNode *p = &root, *q, *r;
	for (int i = 0; i < m - 1; ++i)
		p = p->next;
	q = p->next; // 反转的开头
	r = q->next; // 反转段后面那个
	for (int i = 0; i < (n - m); ++i)
	{
		// 每次都把 r 插入到 p 和 p->next 之间
		q->next = r->next;
		r->next = p->next;
		p->next = r;
		r = q->next;
	}
	return root.next;
}


int main()
{}
