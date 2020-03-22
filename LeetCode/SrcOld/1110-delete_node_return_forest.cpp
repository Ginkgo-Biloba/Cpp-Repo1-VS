#include "leetcode.hpp"

/* 1110. 删点成林

给出二叉树的根节点 root，树上每个节点都有一个不同的值。

如果节点值在 to_delete 中出现，我们就把该节点从树上删去，最后得到一个森林（一些不相交的树构成的集合）。

返回森林中的每棵树。你可以按任意顺序组织答案。


示例：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/07/05/screen-shot-2019-07-01-at-53836-pm.png
输入：root = [1,2,3,4,5,6,7], to_delete = [3,5]
输出：[[1,2,null,4],[6],[7]]

提示：
	树中的节点数最大为 1000。
	每个节点都有一个介于 1 到 1000 之间的值，且各不相同。
	to_delete.length <= 1000
	to_delete 包含一些从 1 到 1000、各不相同的值。
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

// https://leetcode.com/problems/delete-nodes-and-return-forest/discuss/328853/JavaC%2B%2BPython-Recursion-Solution
// 抄的
class Solution
{
	vector<TreeNode*> ans;
	unordered_set<int> todel;

	TreeNode* bfs(TreeNode* node, bool isroot)
	{
		if (!node)
			return NULL;
		bool del = todel.find(node->val) != todel.end();
		if (isroot && !del)
			ans.push_back(node);
		node->left = bfs(node->left, del);
		node->right = bfs(node->right, del);
		return del ? NULL : node;
	}

public:
	vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete)
	{
		ans.clear();
		todel.clear();
		for (int d : to_delete)
			todel.insert(d);
		bfs(root, true);
		return ans;
	}
};


int main()
{}
