#include "leetcode.hpp"

/* 226. 翻转二叉树

翻转一棵二叉树。

示例：

输入：

>      4
>    /   \
>   2     7
>  / \   / \
> 1   3 6   9

输出：

>      4
>    /   \
>   7     2
>  / \   / \
> 9   6 3   1

备注:
这个问题是受到 Max Howell 的 原问题 启发的 ：
谷歌：我们90％的工程师使用您编写的软件(Homebrew)，但是您却无法在面试时在白板上写出翻转二叉树这道题，这太糟糕了。
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

TreeNode* invertTree(TreeNode* root)
{
	vector<TreeNode*> pre, cur;
	TreeNode *a, *b;
	if (root)
		cur.push_back(root);
	while (!cur.empty())
	{
		pre.swap(cur);
		cur.clear();
		for (TreeNode* p : pre)
		{
			a = p->left;
			b = p->right;
			p->left = b;
			p->right = a;
			if (b)
				cur.push_back(b);
			if (a)
				cur.push_back(a);
		}
	}
	return root;
}


int main()
{}
