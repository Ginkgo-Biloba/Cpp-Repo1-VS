#include "leetcode.hpp"

/* 145. 二叉树的后序遍历

给定一个二叉树，返回它的 后序 遍历。

示例:

输入: [1,null,2,3]
>   1
>    \
>     2
>    /
>   3

输出: [3,2,1]
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

vector<int> postorderTraversal_Org(TreeNode* node)
{
	vector<int> r;
	vector<pair<TreeNode*, int>> s;
	if (node)
		s.emplace_back(node, 0);
	while (!s.empty())
	{
		node = s.back().first;
		if (s.back().second)
		{
			r.push_back(node->val);
			s.pop_back();
		}
		else
		{
			s.back().second = 1;
			if (node->right)
				s.emplace_back(node->right, 0);
			if (node->left)
				s.emplace_back(node->left, 0);
		}
	}
	return r;
}

// 把先序遍历的子节点顺序换一下，再把结果反转，就是后序遍历……
vector<int> postorderTraversal(TreeNode* node)
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
		if (node->left)
			s.push_back(node->left);
		if (node->right)
			s.push_back(node->right);
	}
	reverse(r.begin(), r.end());
	return r;
}

int main()
{}
