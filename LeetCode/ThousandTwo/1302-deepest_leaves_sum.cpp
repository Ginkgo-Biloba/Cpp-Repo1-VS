#include "leetcode.hpp"

/* 1302. 层数最深叶子节点的和

给你一棵二叉树，请你返回层数最深的叶子节点的和。

示例：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/12/28/1483_ex1.png
输入：root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
输出：15

提示：
	树中节点数目在 1 到 10^4 之间。
	每个节点的值在 1 到 100 之间。
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
	int sum, depth;

	void dfs(TreeNode* node, int d)
	{
		if (d == depth)
			sum += node->val;
		else if (d > depth)
		{
			depth = d;
			sum = node->val;
		}
		if (node->left)
			dfs(node->left, d + 1);
		if (node->right)
			dfs(node->right, d + 1);
	}

public:
	int deepestLeavesSum(TreeNode* root)
	{
		sum = depth = 0;
		dfs(root, 0);
		return sum;
	}
};

int main()
{}
