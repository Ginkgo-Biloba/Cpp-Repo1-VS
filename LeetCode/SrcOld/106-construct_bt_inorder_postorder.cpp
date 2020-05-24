#include "leetcode.hpp"

/* 106. 从中序与后序遍历序列构造二叉树

根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]

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

// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/discuss/34911/My-C%2B%2B-Solution
// 抄的
class Solution
{
	vector<int> in, post;

	TreeNode* helper(int i, int k, int p, int r)
	{
		if (i >= k || p >= r)
			return NULL;

		// 每次取postorder的最后一个值mid，将其作为树的根节点
		// 然后从inroder中找到mid，将其分割成为两部分
		// 左边作为mid的左子树，右边作为mid的右子树
		// tree:     8 4 10 3 6 9 11
		// Inorder   [3 4 6] 8 [9 10 11]
		// postorder [3 6 4]   [9 11 10] 8
		int mid = post[r - 1];
		int ofs = i;
		for (; ofs < k; ++ofs)
		{
			if (in[ofs] == mid)
				break;
		}
		ofs = ofs - i;
		TreeNode* root = new TreeNode(mid);
		root->left = helper(i, i + ofs, p, p + ofs);
		root->right = helper(i + ofs + 1, k, p + ofs, r - 1);
		return root;
	}

public:
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
	{
		in.swap(inorder);
		post.swap(postorder);
		return helper(0, static_cast<int>(in.size()),
			0, static_cast<int>(post.size()));
	}
};


int main()
{}
