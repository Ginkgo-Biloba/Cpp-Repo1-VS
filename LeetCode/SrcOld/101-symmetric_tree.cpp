#include "leetcode.hpp"

/* 101. 对称二叉树

给定一个二叉树，检查它是否是镜像对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
>     1
>    / \
>   2   2
>  / \ / \
> 3  4 4  3

但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
>    1
>   / \
>  2   2
>   \   \
>   3    3

进阶：
你可以运用递归和迭代两种方法解决这个问题吗？
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


bool isSymmetric(TreeNode* root)
{
	if (!root)
		return true;
	vector<pair<TreeNode*, TreeNode*>> S;
	S.emplace_back(root->left, root->right);
	while (!S.empty())
	{
		auto p = S.back();
		S.pop_back();
		if (p.first == NULL && p.second == NULL)
			continue;
		if (p.first == NULL || p.second == NULL)
			return false;
		if (p.first->val != p.second->val)
			return false;
		S.emplace_back(p.first->left, p.second->right);
		S.emplace_back(p.first->right, p.second->left);
	}
	return true;
}

int main()
{}
