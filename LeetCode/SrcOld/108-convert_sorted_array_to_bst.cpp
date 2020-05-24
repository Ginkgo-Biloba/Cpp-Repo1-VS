#include "leetcode.hpp"

/* 108. 将有序数组转换为二叉搜索树

将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。

本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:

给定有序数组: [-10,-3,0,5,9],

一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：

>      0
>     / \
>   -3   9
>   /   /
> -10  5
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

// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/discuss/35242/16-ms-C%2B%2B-solution
// 抄的
class Solution
{
	vector<int> A;

	TreeNode* helper(int x, int z)
	{
		if (x >= z)
			return NULL;
		int y = (x + z) / 2;
		TreeNode* t = new TreeNode(A[y]);
		t->left = helper(x, y);
		t->right = helper(y + 1, z);
		return t;
	}

public:
	TreeNode* sortedArrayToBST(vector<int>& nums)
	{
		A.swap(nums);
		return helper(0, static_cast<int>(A.size()));
	}
};


int main()
{}
