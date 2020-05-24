#include "leetcode.hpp"

/* 113. 路径总和 II

给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，

>        5
>       / \
>      4   8
>     /   / \
>    11  13  4
>   /  \    / \
>  7    2  5   1

返回:

[
	[5,4,11,2],
	[5,8,4,5]
]
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
	vector<vector<int>> ans;
	vector<int> cur;

	void dfs(TreeNode* node, int64_t val)
	{
		cur.push_back(node->val);
		val -= node->val;
		if (!(node->left || node->right))
		{
			if (val == 0)
				ans.push_back(cur);
		}
		else
		{
			if (node->left)
				dfs(node->left, val);
			if (node->right)
				dfs(node->right, val);
		}
		cur.pop_back();
	}

public:
	vector<vector<int>> pathSum(TreeNode* root, int sum)
	{
		vector<vector<int>> R;
		if (root)
		{
			dfs(root, sum);
			R.swap(ans);
		}
		return R;
	}
};

int main()
{}
