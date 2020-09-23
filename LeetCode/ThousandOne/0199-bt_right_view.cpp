#include "leetcode.hpp"

/* 199. 二叉树的右视图

给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例:
输入: [1,2,3,null,5,null,4]
输出: [1, 3, 4]
解释:
>    1            <---
>  /   \
> 2     3         <---
>  \     \
>   5     4       <---
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

vector<int> rightSideView(TreeNode* root)
{
	vector<int> R;
	vector<TreeNode*> curr, next;
	if (root)
	{
		curr.push_back(root);
		R.push_back(root->val);
	}
	while (curr.size())
	{
		next.clear();
		for (auto p : curr)
		{
			if (p->left)
				next.push_back(p->left);
			if (p->right)
				next.push_back(p->right);
		}
		if (next.size())
			R.push_back(next.back()->val);
		next.swap(curr);
	}
	return R;
}


int main()
{}
