#include "leetcode.hpp"

/* 100. 相同的树

给定两个二叉树，编写一个函数来检验它们是否相同。

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

示例 1:
输入:
>       1         1
>      / \       / \
>     2   3     2   3
>    [1,2,3],   [1,2,3]
输出: true

示例 2:
输入:
>      1          1
>     /            \
>    2              2
>   [1,2],     [1,null,2]
输出: false

示例 3:
输入:
>       1         1
>      / \       / \
>     2   1     1   2
>    [1,2,1],   [1,1,2]
输出: false
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
public:
	bool isSameTree_Org(TreeNode* p, TreeNode* q)
	{
		if (p == NULL && q == NULL)
			return true;
		if ((!p) != (!q))
			return false;
		if (p->val != q->val)
			return false;
		return isSameTree_Org(p->left, q->left)
			&& isSameTree_Org(p->right, q->right);
	}

	// 先序遍历
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		vector<pair<TreeNode*, TreeNode*>> S;
		S.emplace_back(p, q);
		while (S.size())
		{
			auto t = S.back();
			S.pop_back();
			if (!t.first && !t.second)
				continue;
			if (!t.first != !t.second)
				return false;
			if (t.first->val != t.second->val)
				return false;
			S.emplace_back(t.first->left, t.second->left);
			S.emplace_back(t.first->right, t.second->right);
		}
		return true;
	}
};


int main()
{}
