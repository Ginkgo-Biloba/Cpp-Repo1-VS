#include "leetcode.hpp"

/* 1104. 二叉树寻路

在一棵无限的二叉树上，每个节点都有两个子节点，树中的节点 逐行 依次按 “之” 字形进行标记。

如下图所示，在奇数行（即，第一行、第三行、第五行……）中，按从左到右的顺序进行标记；

而偶数行（即，第二行、第四行、第六行……）中，按从右到左的顺序进行标记。

给你树上某一个节点的标号 label，请你返回从根节点到该标号为 label 节点的路径，该路径是由途经的节点标号所组成的。

示例 1：
输入：label = 14
输出：[1,3,4,14]

示例 2：
输入：label = 26
输出：[1,2,6,10,26]

提示：
	1 <= label <= 10^6
*/

// https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/discuss/324011/Python-O(logn)-time-and-space-with-readable-code-and-step-by-step-explanation
// 抄的
vector<int> pathInZigZagTree(int label)
{
	vector<int> path;
	int node = 1, level = 1;
	while (label >= node * 2)
	{
		node *= 2;
		level += 1;
	}
	while (label > 0)
	{
		path.push_back(label);
		int lmax = (1 << level) - 1;
		int lmin = 1 << (level - 1);
		label = (lmax + lmin - label) / 2;
		--level;
	}
	reverse(path.begin(), path.end());
	return path;
}


int main()
{
	output(pathInZigZagTree(14));
	output(pathInZigZagTree(26));
}
