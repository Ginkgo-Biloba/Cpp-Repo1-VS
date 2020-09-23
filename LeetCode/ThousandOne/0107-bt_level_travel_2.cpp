#include "leetcode.hpp"

/* 107. 二叉树的层次遍历 II

给定一个二叉树，返回其节点值自底向上的层次遍历。
即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历。

例如：
给定二叉树 [3,9,20,null,null,15,7],
		3
	 / \
	9  20
		/  \
	 15   7

返回其自底向上的层次遍历为：
[
	[15,7],
	[9,20],
	[3]
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

vector<vector<int>> levelOrderBottom(TreeNode* root)
{
	vector<vector<int>> R;
	if (!root)
		return R;
	vector<TreeNode*> A, B;
	A.push_back(root);
	while (!A.empty())
	{
		B.clear();
		vector<int> r;
		r.reserve(A.size());
		for (auto t : A)
		{
			r.push_back(t->val);
			if (t->left)
				B.push_back(t->left);
			if (t->right)
				B.push_back(t->right);
		}
		B.swap(A);
		R.push_back(move(r));
	}
	reverse(R.begin(), R.end());
	return R;
}


int main()
{}
