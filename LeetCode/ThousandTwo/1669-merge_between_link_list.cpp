#include "leetcode.hpp"

/* 1669. 合并两个链表

给你两个链表 list1 和 list2 ，它们包含的元素分别为 n 个和 m 个。

请你将 list1 中第 a 个节点到第 b 个节点删除，并将list2 接在被删除节点的位置。

下图中蓝色边和节点展示了操作后的结果：
https://assets.leetcode.com/uploads/2020/11/05/fig1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/11/28/fig1.png
请你返回结果链表的头指针。

示例 1：
https://assets.leetcode.com/uploads/2020/11/05/merge_linked_list_ex1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/11/28/merge_linked_list_ex1.png
输入：list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
输出：[0,1,2,1000000,1000001,1000002,5]
解释：我们删除 list1 中第三和第四个节点，并将 list2 接在该位置。上图中蓝色的边和节点为答案链表。

示例 2：
https://assets.leetcode.com/uploads/2020/11/05/merge_linked_list_ex2.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/11/28/merge_linked_list_ex2.png
输入：list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
输出：[0,1,1000000,1000001,1000002,1000003,1000004,6]
解释：上图中蓝色的边和节点为答案链表。

提示：
	3 <= list1.length <= 10^4
	1 <= a <= b < list1.length - 1
	1 <= list2.length <= 10^4
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

ListNode* mergeInBetween(
	ListNode* list1, int a, int b, ListNode* list2)
{
	ListNode* A = list1;
	for (int i = 1; i < a; ++i)
		A = A->next;
	ListNode* B = A->next;
	for (int i = a; i < b; ++i)
		B = B->next;
	A->next = list2;
	while (A->next)
		A = A->next;
	A->next = B->next;
	B->next = NULL;
	return list1;
}


int main()
{}
