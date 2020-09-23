#include "leetcode.hpp"

/* 124. 二叉树中的最大路径和

给定一个非空二叉树，返回其最大路径和。

本题中，路径被定义为一条从树中任意节点出发，达到任意节点的序列。
该路径至少包含一个节点，且不一定经过根节点。

示例 1:
输入: [1,2,3]

>   1
>  / \
> 2   3

输出: 6

示例 2:
输入: [-10,9,20,null,null,15,7]

>   -10
>   / \
>  9  20
>    /  \
>   15   7

输出: 42


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

class Solution
{
	int ans;

	int post(TreeNode* node)
	{
		int x = node->val;
		int a = INT_MIN, b = INT_MIN;
		if (node->left)
			a = post(node->left);
		if (node->right)
			b = post(node->right);
		int c = max(a, b);
		// without this node
		ans = max(ans, c);
		// with this node and at most 2 branches
		ans = max(ans, x + max(a, 0) + max(b, 0));
		// with this node and at most 1 branch
		return x + max(c, 0);
	}

public:
	int maxPathSum(TreeNode* root)
	{
		ans = INT_MIN;
		post(root);
		return ans;
	}
};


int main()
{}
