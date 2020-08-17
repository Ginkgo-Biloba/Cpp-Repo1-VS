#include "leetcode.hpp"

/* 1530. 好叶子节点对的数量

给你二叉树的根节点 root 和一个整数 distance。

如果二叉树中两个 叶 节点之间的 最短路径长度 小于或者等于 distance ，那它们就可以构成一组 好叶子节点对 。

返回树中 好叶子节点对的数量。

示例 1：
https://assets.leetcode.com/uploads/2020/07/09/e1.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/07/26/e1.jpg
输入：root = [1,2,3,null,4], distance = 3
输出：1
解释：树的叶节点是 3 和 4 ，它们之间的最短路径的长度是 3 。这是唯一的好叶子节点对。

示例 2：
https://assets.leetcode.com/uploads/2020/07/09/e2.jpg
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/07/26/e2.jpg
输入：root = [1,2,3,4,5,6,7], distance = 3
输出：2
解释：好叶子节点对为 [4,5] 和 [6,7] ，最短路径长度都是 2 。但是叶子节点对 [4,6] 不满足要求，因为它们之间的最短路径长度为 4 。

示例 3：
输入：
root = [7,1,4,6,null,5,3,null,null,null,null,null,2],
distance = 3
输出：1
解释：唯一的好叶子节点对是 [2,5] 。

示例 4：
输入：root = [100], distance = 1
输出：0

示例 5：
输入：root = [1,1,1], distance = 2
输出：1

提示：
	tree 的节点数在 [1, 2^10] 范围内。
	每个节点的值都在 [1, 100] 之间。
	1 <= distance <= 10
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
	// A[n][i], num of leaves with distance `i' to node `n'
	vector<array<int, 12>> A;
	int idx, ans, dis;

	int* dfs(TreeNode* node)
	{
		int* ptr = A[idx++].data();
		int *L = ptr, *R = ptr;
		if (node->left)
			L = dfs(node->left);
		if (node->right)
			R = dfs(node->right);
		// leaf
		if (L == ptr && R == ptr)
		{
			ptr[0] = 1;
			return ptr;
		}
		for (int i = 10; i > 0; --i)
			ptr[i] = L[i - 1] + R[i - 1];
		// has two children
		if (L != ptr && R != ptr)
		{
			for (int i = 1; i < 10; ++i)
				R[i] += R[i - 1];
			for (int i = 1; i < dis; ++i)
				ans += L[i - 1] * R[dis - 1 - i];
		}
		return ptr;
	}

public:
	int countPairs(TreeNode* root, int distance)
	{
		A.resize(1024);
		memset(A.data(), 0, A.size() * sizeof(A[0]));
		idx = ans = 0;
		dis = distance;
		dfs(root);
		return ans;
	}
};


int main()
{}
