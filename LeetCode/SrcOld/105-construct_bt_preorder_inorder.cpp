#include "leetcode.hpp"

/* 105. 从前序与中序遍历序列构造二叉树

根据一棵树的前序遍历与中序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]

返回如下的二叉树：

>    3
>   / \
>  9  20
>    /  \
>   15   7
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

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/discuss/34557/My-neat-C%2B%2B-solution
// 抄的
class Solution
{
	vector<int> pre, in;

	TreeNode* helper(int i, int k, int p, int r)
	{
		if (i >= k || p >= r)
			return NULL;

		// 每次从 preorder 头部取一个值 mid，作为树的根节点
		// 检查 mid 在 inorder 中 的位置
		// 则 mid 前面部分将作为 树的左子树，右部分作为树的右子树
		// tree        8 4 5 3 7 3
		// preorder    8 [4 3 3 7] [5]
		// inorder     [3 3 4 7] 8 [5]
		int mid = pre[i];
		int ofs = 0;
		for (ofs = p; ofs < r; ++ofs)
		{
			if (in[ofs] == mid)
				break;
		}
		ofs = ofs - p;
		TreeNode* root = new TreeNode(mid);
		root->left = helper(i + 1, i + 1 + ofs, p, p + ofs);
		root->right = helper(i + 1 + ofs, k, p + 1 + ofs, r);
		return root;
	}

public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		pre.swap(preorder);
		in.swap(inorder);
		return helper(0, static_cast<int>(pre.size()),
			0, static_cast<int>(in.size()));
	}
};


int main()
{}
