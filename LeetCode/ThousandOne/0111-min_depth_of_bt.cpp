#include "leetcode.hpp"

/* 111. 二叉树的最小深度

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明: 叶子节点是指没有子节点的节点。

示例:

给定二叉树 [3,9,20,null,null,15,7],

>    3
>   / \
>  9  20
>    /  \
>   15   7

返回它的最小深度 2.
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
	void dfs(TreeNode* node, int d)
	{
		if (d >= ans)
			return;
		if (!(node->left) && !(node->right))
			ans = min(ans, d);
		else
		{
			if (node->left)
				dfs(node->left, d + 1);
			if (node->right)
				dfs(node->right, d + 1);
		}
	}

public:
	int minDepth(TreeNode* root)
	{
		if (!root)
			return 0;
		ans = INT_MAX;
		dfs(root, 1);
		return ans;
	}
};


int main()
{}
