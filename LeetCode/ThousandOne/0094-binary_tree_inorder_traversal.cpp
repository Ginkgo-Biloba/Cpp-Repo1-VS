#include "leetcode.hpp"

/* 94. 二叉树的中序遍历

给定一个二叉树，返回它的中序 遍历。

示例:

输入: [1,null,2,3]
>   1
>    \
>     2
>    /
>   3

输出: [1,3,2]

进阶: 递归算法很简单，你可以通过迭代算法完成吗？
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


vector<int> inorderTraversal_Org(TreeNode* root)
{
	vector<pair<int, TreeNode*>> S;
	vector<int> R;
	if (root)
		S.emplace_back(0, root);
	while (S.size())
	{
		auto t = S.back();
		if ((t.first == 0) && (t.second->left))
		{
			S.back().first = 1;
			S.emplace_back(0, t.second->left);
		}
		else
		{
			R.push_back(t.second->val);
			S.pop_back();
			if (t.second->right)
				S.emplace_back(0, t.second->right);
		}
	}
	return R;
}

// https://leetcode.com/problems/binary-tree-inorder-traversal/discuss/31231/C%2B%2B-Iterative-Recursive-and-Morris
// 抄的
vector<int> inorderTraversal(TreeNode* root)
{
	vector<TreeNode*> S;
	vector<int> R;
	while (root || S.size())
	{
		for (; root; root = root->left)
			S.push_back(root);
		root = S.back();
		S.pop_back();
		R.push_back(root->val);
		root = root->right;
	}
	return R;
}

int main()
{}
