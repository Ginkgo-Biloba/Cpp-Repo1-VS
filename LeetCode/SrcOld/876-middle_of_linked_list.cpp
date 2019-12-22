#include "leetcode.hpp"

/* 876. 链表的中间结点

给定一个带有头结点 head 的非空单链表，返回链表的中间结点。
如果有两个中间结点，则返回第二个中间结点。
*/

// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x)
		: val(x), next(NULL)
	{}
};

class Solution
{
public:
	ListNode* middleNode(ListNode* head)
	{
		ListNode *s = head, *f = head;
		while (f && f->next)
		{
			s = s->next;
			f = f->next->next;
		}
		return s;
	}
};

int main()
{}
