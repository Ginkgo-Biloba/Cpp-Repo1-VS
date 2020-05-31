#include "leetcode.hpp"

/* 257. 二叉树的所有路径

给定一个二叉树，返回所有从根节点到叶子节点的路径。

说明: 叶子节点是指没有子节点的节点。

示例:

输入:

>    1
>  /   \
> 2     3
>  \
>   5

输出: ["1->2->5", "1->3"]
解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3
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
	char buffer[32];
	vector<int> cur;
	vector<string> ans;

	void dfs(TreeNode* node)
	{
		cur.push_back(node->val);
		if (!(node->left || node->right))
		{
			string s;
			for (int a : cur)
			{
				sprintf(buffer, "%d->", a);
				s.append(buffer);
			}
			s.pop_back();
			s.pop_back();
			ans.push_back(move(s));
		}
		else
		{
			if (node->left)
				dfs(node->left);
			if (node->right)
				dfs(node->right);
		}
		cur.pop_back();
	}

public:
	vector<string> binaryTreePaths(TreeNode* root)
	{
		if (root)
			dfs(root);
		return move(ans);
	}
};


int main()
{}
