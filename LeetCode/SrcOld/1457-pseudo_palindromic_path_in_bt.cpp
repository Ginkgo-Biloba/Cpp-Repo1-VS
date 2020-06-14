#include "leetcode.hpp"

/* 1457. 二叉树中的伪回文路径

给你一棵二叉树，每个节点的值为 1 到 9 。
我们称二叉树中的一条路径是 「伪回文」的，当它满足：路径经过的所有节点值的排列中，存在一个回文序列。

请你返回从根到叶子节点的所有路径中 伪回文 路径的数目。

示例 1：
https://assets.leetcode.com/uploads/2020/05/06/palindromic_paths_1.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/23/palindromic_paths_1.png
输入：root = [2,3,1,3,1,null,1]
输出：2
解释：
上图为给定的二叉树。总共有 3 条从根到叶子的路径：红色路径 [2,3,3] ，绿色路径 [2,1,1] 和路径 [2,3,1] 。
在这些路径中，只有红色和绿色的路径是伪回文路径，因为红色路径 [2,3,3] 存在回文排列 [3,2,3] ，绿色路径 [2,1,1] 存在回文排列 [1,2,1] 。

示例 2：
https://assets.leetcode.com/uploads/2020/05/07/palindromic_paths_2.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/23/palindromic_paths_2.png
输入：root = [2,1,1,1,3,null,null,null,null,null,1]
输出：1
解释：
上图为给定二叉树。
总共有 3 条从根到叶子的路径：绿色路径 [2,1,1] ，路径 [2,1,3,1] 和路径 [2,1] 。
这些路径中只有绿色路径是伪回文路径，因为 [2,1,1] 存在回文排列 [1,2,1] 。

示例 3：
输入：root = [9]
输出：1

提示：
	给定二叉树的节点数目在 1 到 10^5 之间。
	节点值在 1 到 9 之间。
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

class Solution1
{
	int freq[11]; // freq[10] -> ans

	void dfs(TreeNode* node, int odd, int even)
	{
		int key = node->val;
		freq[key] += 1;
		int val = freq[key];
		if (val & 1)
		{
			odd += 1;
			if (val != 1)
				even -= 1;
		}
		else
		{
			odd -= 1;
			even += 1;
		}
		if (!(node->left || node->right) && (odd <= 1))
			++(freq[10]);
		else
		{
			if (node->left)
				dfs(node->left, odd, even);
			if (node->right)
				dfs(node->right, odd, even);
		}
		freq[key] -= 1;
	}

public:
	int pseudoPalindromicPaths(TreeNode* root)
	{
		memset(freq, 0, sizeof(freq));
		if (root)
			dfs(root, 0, 0);
		return freq[10];
	}
};


// https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/discuss/648534/JavaC%2B%2BPython-At-most-one-odd-occurrence
// 抄的，位运算大法好
class Solution
{
public:
	int pseudoPalindromicPaths(TreeNode* root)
	{
		vector<TreeNode*> cur, tmp;
		int sum = 0;
		if (root)
		{
			root->val = (1 << root->val);
			cur.push_back(root);
		}
		while (!cur.empty())
		{
			tmp.clear();
			for (TreeNode* node : cur)
			{
				TreeNode* a = node->left;
				TreeNode* b = node->right;
				if (!(a || b))
				{
					int v = node->val;
					// sum += _popcnt32(v) <= 1;
					sum += ((v & (v - 1)) == 0);
					continue;
				}
				if (a)
				{
					a->val = (1 << a->val) ^ node->val;
					tmp.push_back(a);
				}
				if (b)
				{
					b->val = (1 << b->val) ^ node->val;
					tmp.push_back(b);
				}
			}
			tmp.swap(cur);
		}
		return sum;
	}
};


int main()
{}
