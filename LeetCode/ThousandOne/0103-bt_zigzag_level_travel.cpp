#include "leetcode.hpp"

/* 103. 二叉树的锯齿形层次遍历

给定一个二叉树，返回其节点值的锯齿形层次遍历。
即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行。

例如：
给定二叉树 [3,9,20,null,null,15,7],
>    3
>   / \
>  9  20
>    /  \
>   15   7

返回锯齿形层次遍历如下：
[
	[3],
	[20,9],
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

vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
	vector<vector<int>> R;
	if (!root)
		return R;
	vector<TreeNode*> A, B;
	A.push_back(root);
	for (int level = 0; !A.empty(); ++level)
	{
		B.clear();
		vector<int> r;
		int len = static_cast<int>(A.size());
		r.reserve(len);
		for (auto t : A)
		{
			r.push_back(t->val);
			if (t->left)
				B.push_back(t->left);
			if (t->right)
				B.push_back(t->right);
		}
		B.swap(A);
		if (level & 1)
			reverse(r.begin(), r.end());
		R.push_back(move(r));
	}
	return R;
}


int main()
{}
