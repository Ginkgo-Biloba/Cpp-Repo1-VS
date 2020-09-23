#include "leetcode.hpp"

/* 23. 合并K个排序链表

合并 k 个排序链表，返回合并后的排序链表。
请分析和描述算法的复杂度。

示例:
输入:
[
	1->4->5,
	1->3->4,
	2->6
]
输出: 1->1->2->3->4->4->5->6
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


class Solution
{
	struct Comp
	{
		bool operator()(ListNode* a, ListNode* b) const
		{
			return a->val > b->val;
		}
	};

public:
	ListNode* mergeKLists(vector<ListNode*>& A)
	{
		ListNode root(-1);
		ListNode* C = &root;
		priority_queue<ListNode*, vector<ListNode*>, Comp> Q;
		for (ListNode* node : A)
		{
			if (node)
				Q.push(node);
		}
		while (!Q.empty())
		{
			ListNode* q = Q.top();
			Q.pop();
			C->next = q;
			C = q;
			q = q->next;
			if (q)
				Q.push(q);
		}
		return root.next;
	}
};


int main()
{}
