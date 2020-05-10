#include "leetcode.hpp"

/* 95. 不同的二叉搜索树 II

给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

示例:

输入: 3
输出:
[
	[1,null,3,2],
	[3,2,null,1],
	[3,1,null,null,2],
	[2,1,3],
	[1,null,2,null,3]
]
解释:
以上的输出对应以下 5 种不同结构的二叉搜索树：

>   1         3     3      2      1
>    \       /     /      / \      \
>     3     2     1      1   3      2
>    /     /       \                 \
>   2     1         2                 3
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


// https://leetcode.com/problems/unique-binary-search-trees-ii/discuss/31563/My-Accepted-C%2B%2B-solution-(recursive-less-than-30-lines)
// 抄的
class Solution
{
	vector<TreeNode*> gen(int a, int b)
	{
		vector<TreeNode*> ans;
		if (a > b)
			ans.push_back(NULL);
		else if (a == b)
			ans.push_back(new TreeNode(a));
		else
		{
			for (int i = a; i <= b; ++i)
			{
				vector<TreeNode*> L = gen(a, i - 1);
				vector<TreeNode*> R = gen(i + 1, b);
				size_t lenL = L.size();
				size_t lenR = R.size();
				for (size_t p = 0; p < lenL; ++p)
					for (size_t q = 0; q < lenR; ++q)
					{
						TreeNode* root = new TreeNode(i);
						root->left = L[p];
						root->right = R[q];
						ans.push_back(root);
					}
			}
		}
		return ans;
	}

public:
	vector<TreeNode*> generateTrees(int n)
	{
		vector<TreeNode*> ans;
		if (n != 0)
			gen(1, n).swap(ans);
		return ans;
	}
};


int main()
{}
