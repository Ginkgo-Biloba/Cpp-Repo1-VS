#include "leetcode.hpp"

/* 429. N叉树的层序遍历
给定一个 N 叉树，返回其节点值的层序遍历。 (即从左到右，逐层遍历)。

例如，给定一个 3叉树 :
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/narytreeexample.png

返回其层序遍历:
[
	[1],
	[3,2,4],
	[5,6]
]

说明:
		树的深度不会超过 1000。
		树的节点总数不会超过 5000。
*/

class Node
{
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children)
	{
		val = _val;
		children = _children;
	}
};

vector<vector<int>> levelOrder(Node* root)
{
	vector<vector<int>> all;
	if (root == nullptr)
		return all;

	std::queue<Node*> p, q;
	p.push(root);

	while (!p.empty())
	{
		p.swap(q);
		vector<int> cur;
		while (!q.empty())
		{
			Node* nd = q.front();
			q.pop();
			cur.push_back(nd->val);
			size_t len = nd->children.size();
			for (size_t i = 0; i < len; ++i)
				p.push(nd->children[i]);
		}
		all.push_back(std::move(cur));
	}
	return all;
}


int main()
{}
