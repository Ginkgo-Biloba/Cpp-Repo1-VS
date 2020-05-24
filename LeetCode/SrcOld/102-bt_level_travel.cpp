#include "leetcode.hpp"

/* 102. 二叉树的层序遍历

给你一个二叉树，请你返回其按 层序遍历 得到的节点值。
即逐层地，从左到右访问所有节点。


示例：
二叉树：[3,9,20,null,null,15,7],
>    3
>   / \
>  9  20
>    /  \
>   15   7

返回其层次遍历结果：
[
	[3],
	[9,20],
	[15,7]
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

vector<vector<int>> levelOrder(TreeNode* root)
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
	return R;
}


int main()
{}
