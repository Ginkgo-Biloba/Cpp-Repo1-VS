#include "leetcode.hpp"

/* 109. 有序链表转换二叉搜索树

给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。

本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:

给定的有序链表： [-10, -3, 0, 5, 9],

一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：

>      0
>     / \
>   -3   9
>   /   /
> -10  5
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

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x)
		: val(x)
		, left(NULL)
		, right(NULL)
	{}
};

// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/discuss/35483/My-Accepted-C%2B%2B-solution
// 抄的
class Solution
{
	TreeNode* helper(ListNode* head, ListNode* tail)
	{
		if (head == tail)
			return NULL;
		if (head->next == tail)
		{
			TreeNode* root = new TreeNode(head->val);
			return root;
		}
		ListNode *mid = head, *tmp = head;
		while (tmp != tail && tmp->next != tail)
		{
			mid = mid->next;
			tmp = tmp->next->next;
		}
		TreeNode* root = new TreeNode(mid->val);
		root->left = helper(head, mid);
		root->right = helper(mid->next, tail);
		return root;
	}

public:
	TreeNode* sortedListToBST(ListNode* head)
	{
		return helper(head, NULL);
	}
};


int main()
{}
