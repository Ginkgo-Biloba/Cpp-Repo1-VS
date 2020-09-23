#include "leetcode.hpp"

/* 1305. 两棵二叉搜索树中的所有元素

给你 root1 和 root2 这两棵二叉搜索树。

请你返回一个列表，其中包含 两棵树 中的所有整数并按 升序 排序。

示例 1：
输入：root1 = [2,1,4], root2 = [1,0,3]
输出：[0,1,1,2,3,4]

示例 2：
输入：root1 = [0,-10,10], root2 = [5,1,7,0,2]
输出：[-10,0,0,1,2,5,7,10]

示例 3：
输入：root1 = [], root2 = [5,1,7,0,2]
输出：[0,1,2,5,7]

示例 4：
输入：root1 = [0,-10,10], root2 = []
输出：[-10,0,10]

示例 5：
输入：root1 = [1,null,8], root2 = [8,1]
输出：[1,1,8,8]

提示：
	每棵树最多有 5000 个节点。
	每个节点的值在 [-10^5, 10^5] 之间。
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

// https://leetcode.com/problems/all-elements-in-two-binary-search-trees/discuss/464073/C%2B%2B-One-Pass-Traversal
// 抄的
class Solution
{
	void pushLeft(vector<TreeNode*>& S, TreeNode* node)
	{
		while (node)
		{
			S.push_back(node);
			node = node->left;
		}
	}

public:
	vector<int> getAllElements(TreeNode* root1, TreeNode* root2)
	{
		vector<int> V;
		vector<TreeNode*> P, Q;
		pushLeft(P, root1);
		pushLeft(Q, root2);
		while (!P.empty() || !Q.empty())
		{
			if (P.empty()
				|| (!Q.empty() && Q.back()->val < P.back()->val))
			{
				TreeNode* t = Q.back();
				Q.pop_back();
				V.push_back(t->val);
				pushLeft(Q, t->right);
			}
			else
			{
				TreeNode* t = P.back();
				P.pop_back();
				V.push_back(t->val);
				pushLeft(P, t->right);
			}
		}
		return V;
	}
};


int main()
{}
