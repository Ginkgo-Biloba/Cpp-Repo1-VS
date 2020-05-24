#include "leetcode.hpp"

/* 114. 二叉树展开为链表

给定一个二叉树，原地将它展开为链表。

例如，给定二叉树

>     1
>    / \
>   2   5
>  / \   \
> 3   4   6

将其展开为：

>  1
>   \
>    2
>     \
>      3
>       \
>        4
>         \
>          5
>           \
>            6
*/

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


// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/discuss/36977/My-short-post-order-traversal-Java-solution-for-share
// 抄的
class Solution
{
	TreeNode* prev;

	void post(TreeNode* node)
	{
		if (!node)
			return;
		post(node->right);
		post(node->left);
		node->right = prev;
		node->left = NULL;
		prev = node;
	}

public:
	void flatten(TreeNode* root)
	{
		if (!root)
			return;
		prev = NULL;
		post(root);
	}
};


int main()
{}
