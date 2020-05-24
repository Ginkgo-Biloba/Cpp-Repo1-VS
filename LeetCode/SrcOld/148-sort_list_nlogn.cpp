#include "leetcode.hpp"

/* 148. 排序链表

在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

示例 1:
输入: 4->2->1->3
输出: 1->2->3->4

示例 2:
输入: -1->5->3->4->0
输出: -1->0->3->4->5
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

ListNode* merge(ListNode* a, ListNode* b)
{
	ListNode dummy(-1);
	ListNode* c = &dummy;
	while (a && b)
	{
		if (a->val < b->val)
		{
			c->next = a;
			a = a->next;
		}
		else
		{
			c->next = b;
			b = b->next;
		}
		c = c->next;
	}
	if (a)
		c->next = a;
	else
		c->next = b;
	return dummy.next;
}

ListNode* sortList(ListNode* head)
{
	// 30 个桶足够了吧，存 2^30 - 1 个数字
	int const bsz = 29;
	pair<ListNode*, int> bucket[bsz + 1];
	ListNode* node;
	while (head)
	{
		node = head;
		head = head->next;
		node->next = NULL;
		bucket[0].first = merge(bucket[0].first, node);
		bucket[0].second += 1;
		for (int d = 0; d < bsz; ++d)
		{
			if (bucket[d].second <= (1 << d))
				break;
			bucket[d + 1].first = merge(
				bucket[d + 1].first, bucket[d].first);
			bucket[d + 1].second += bucket[d].second;
			bucket[d].first = NULL;
			bucket[d].second = 0;
		}
	}
	for (int d = 0; d < bsz; ++d)
	{
		bucket[d + 1].first = merge(
			bucket[d + 1].first, bucket[d].first);
		bucket[d + 1].second += bucket[d].second;
		bucket[d].first = NULL;
		bucket[d].second = 0;
	}
	return bucket[bsz].first;
}


void func(vector<int>& a)
{
	vector<ListNode*> tmp;
	size_t len = a.size();
	ListNode root(-1);
	ListNode* c = &root;
	for (size_t i = 0; i < len; ++i)
	{
		tmp.push_back(new ListNode(a[i]));
		c->next = tmp.back();
		c = c->next;
	}
	c->next = NULL;
	c = sortList(root.next);
	for (size_t i = 0; i < len; ++i)
	{
		a[i] = c->val;
		c = c->next;
	}
	assert(c == NULL);
	for (ListNode* t : tmp)
		delete t;
}

int main()
{
	vector<int>
		a = { 4, 2, 1, 3 },
		b = { -1, 5, 3, 4, 0 };
	func(a);
	func(b);
	output(a, "sort list");
	output(b, "sort list");
}
