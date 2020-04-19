#include "leetcode.hpp"

/* 1315. 祖父节点值为偶数的节点和

给你一棵二叉树，请你返回满足以下条件的所有节点的值之和：
	该节点的祖父节点的值为偶数。（一个节点的祖父节点是指该节点的父节点的父节点。）

如果不存在祖父节点值为偶数的节点，那么返回 0 。

示例：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/10/1473_ex1.png
输入：root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
输出：18
解释：图中红色节点的祖父节点的值为偶数，蓝色节点为这些红色节点的祖父节点。

提示：
	树中节点的数目在 1 到 10^4 之间。
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
	int sum;

	void dfs(TreeNode* node, int flag)
	{
		if (flag & 1)
			sum += node->val;
		flag >>= 1;
		if (!(node->val & 1))
			flag |= (1 << 2);
		if (node->left)
			dfs(node->left, flag);
		if (node->right)
			dfs(node->right, flag);
	}

public:
	int sumEvenGrandparent(TreeNode* root)
	{
		sum = 0;
		dfs(root, 0);
		return sum;
	}
};


int main()
{}
