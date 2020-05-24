#include "leetcode.hpp"

/* 144. 二叉树的前序遍历

给定一个二叉树，返回它的 前序 遍历。

示例:
输入: [1,null,2,3]
>   1
>    \
>     2
>    /
>   3

输出: [1,2,3]

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

vector<int> preorderTraversal(TreeNode* node)
{
	vector<int> r;
	vector<TreeNode*> s;
	if (node)
		s.push_back(node);
	while (!s.empty())
	{
		node = s.back();
		s.pop_back();
		r.push_back(node->val);
		if (node->right)
			s.push_back(node->right);
		if (node->left)
			s.push_back(node->left);
	}
	return r;
}


int main()
{}
