#include "leetcode.hpp"

/* 142. 环形链表 II

给定一个链表，返回链表开始入环的第一个节点。
如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
如果 pos 是 -1，则在该链表中没有环。

说明：不允许修改给定的链表。

示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist.png

示例 2：
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test2.png

示例 3：
输入：head = [1], pos = -1
输出：false
解释：链表中没有环。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test3.png

进阶：
你能用 O(1)（即，常量）内存解决此问题吗？
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


ListNode* detectCycle(ListNode* head)
{
	bool cycle = false;
	ListNode *a = head, *b = head;
	while (b && b->next)
	{
		a = a->next;
		b = b->next->next;
		if (a == b)
		{
			cycle = true;
			break;
		}
	}
	if (!cycle)
		return NULL;

	a = head;
	while (a != b)
	{
		a = a->next;
		b = b->next;
	}
	return b;
}


int main()
{}
