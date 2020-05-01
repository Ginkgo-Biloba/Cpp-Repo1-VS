#include "leetcode.hpp"

/* 1361. 验证二叉树

二叉树上有 n 个节点，按从 0 到 n - 1 编号，其中节点 i 的两个子节点分别是 leftChild[i] 和 rightChild[i]。

只有 所有 节点能够形成且 只 形成 一颗 有效的二叉树时，返回 true；否则返回 false。

如果节点 i 没有左子节点，那么 leftChild[i] 就等于 -1。
右子节点也符合该规则。

注意：节点没有值，本问题中仅仅使用节点编号。

示例 1：
输入：n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
输出：true

示例 2：
输入：n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
输出：false

示例 3：
输入：n = 2, leftChild = [1,0], rightChild = [-1,-1]
输出：false

示例 4：
输入：n = 6, leftChild = [1,-1,-1,4,-1,-1], rightChild = [2,-1,-1,5,-1,-1]
输出：false

提示：
	1 <= n <= 10^4
	leftChild.length == rightChild.length == n
	-1 <= leftChild[i], rightChild[i] <= n - 1
*/

bool validateBinaryTreeNodes(int n,
	vector<int>& leftChild, vector<int>& rightChild)
{
	vector<int> par(n);
	for (int i = 0; i < n; ++i)
	{
		int a = leftChild[i];
		int b = rightChild[i];
		if (a != -1)
			par[a] += 1;
		if (b != -1)
			par[b] += 1;
	}

	int root = -1;
	for (int i = 0; i < n; ++i)
	{
		// 超过两个父节点
		if (par[i] > 2)
			return false;
		if (par[i] == 0)
		{
			// 有多于一个没有父亲的节点
			if (root == -1)
				root = i;
			else
				return false;
		}
	}
	// 都有父节点，没有根
	if (root == -1)
		return false;

	vector<char> visit(n);
	vector<int> current, nextloop;
	current.push_back(root);
	visit[root] = 1;
	while (!current.empty())
	{
		nextloop.clear();
		for (int i : current)
		{
			int a = leftChild[i];
			int b = rightChild[i];
			if (a != -1)
			{
				// 有环
				if (visit[a])
					return false;
				visit[a] = 1;
				nextloop.push_back(a);
			}
			if (b != -1)
			{
				if (visit[b])
					return false;
				visit[b] = 1;
				nextloop.push_back(b);
			}
		}
		nextloop.swap(current);
	}

	for (int i = 0; i < n; ++i)
	{
		// 有孤立的点
		if (!visit[i])
			return false;
	}
	return true;
}


int main()
{}
