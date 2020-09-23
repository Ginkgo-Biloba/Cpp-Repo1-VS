#include "leetcode.hpp"

/* 212. 单词搜索 II

给定一个二维网格 board 和一个字典中的单词列表 words，找出所有同时在二维网格和字典中出现的单词。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母在一个单词中不允许被重复使用。

示例:
输入:
words = ["oath","pea","eat","rain"] and board =
[
	['o','a','a','n'],
	['e','t','a','e'],
	['i','h','k','r'],
	['i','f','l','v']
]
输出: ["eat","oath"]

说明:
你可以假设所有输入都由小写字母 a-z 组成。

提示:
	你需要优化回溯算法以通过更大数据量的测试。你能否早点停止回溯？
	如果当前单词不存在于所有单词的前缀中，则可以立即停止回溯。什么样的数据结构可以有效地执行这样的操作？散列表是否可行？为什么？ 前缀树如何？如果你想学习如何实现一个基本的前缀树，请先查看这个问题： 实现Trie（前缀树）。
*/

class Trie
{
public:
	struct Node
	{
		// val is not used...
		char val, leaf;
		Node* data[26];
	};

	Node head;
	vector<Node*> buffer;

	Trie()
	{
		memset(&head, 0, sizeof(head));
	}

	~Trie()
	{
		clear();
	}

	void clear()
	{
		for (auto node : buffer)
			free(node);
		buffer.clear();
		memset(&head, 0, sizeof(head));
	}

	Node* insert(string word)
	{
		int len = static_cast<int>(word.length());
		Node* node = &head;
		for (int i = 0; i < len; ++i)
		{
			int c = word[i] - 'a';
			if (!(node->data[c]))
			{
				Node* tmp = static_cast<Node*>(calloc(1, sizeof(Node)));
				tmp->val = word[i];
				node->data[c] = tmp;
				buffer.push_back(tmp);
			}
			node = node->data[c];
		}
		node->leaf = 1;
		return node;
	}
};

static int const dir[] = { -1, 0, 1, 0, -1 };

class Solution
{
	typedef Trie::Node Node;

	vector<vector<char>> grid;
	unsigned rows, cols;
	string cur;
	vector<string> ans;
	Trie trie;

	void dfs(Node* node, unsigned h, unsigned w)
	{
		char backup = grid[h][w];
		if (node->leaf)
		{
			ans.push_back(cur);
			node->leaf = 0;
		}
		grid[h][w] = '#';
		for (int d = 0; d < 4; ++d)
		{
			unsigned y = h + dir[d];
			unsigned x = w + dir[d + 1];
			if ((y >= rows) || (x >= cols))
				continue;
			char c = grid[y][x];
			if (c != '#' && node->data[c - 'a'])
			{
				cur.push_back(c);
				dfs(node->data[c - 'a'], y, x);
				cur.pop_back();
			}
		}
		grid[h][w] = backup;
	}

public:
	vector<string> findWords(
		vector<vector<char>>& board,
		vector<string>& words)
	{
		vector<string> R;
		grid.swap(board);
		rows = static_cast<unsigned>(grid.size());
		if (rows == 0)
			return R;
		cols = static_cast<unsigned>(grid[0].size());

		trie.clear();
		for (string& w : words)
			trie.insert(w);

		Node* node = &(trie.head);
		for (unsigned h = 0; h < rows; ++h)
			for (unsigned w = 0; w < cols; ++w)
			{
				char c = grid[h][w];
				if (node->data[c - 'a'])
				{
					cur.push_back(c);
					dfs(node->data[c - 'a'], h, w);
					cur.pop_back();
				}
			}
		R.swap(ans);
		return R;
	}
};


int main()
{
	vector<string>
		a = { "oath", "pea", "eat", "rain" },
		c = { "ab" };
	vector<vector<char>>
		b = {
			{ 'o', 'a', 'a', 'n' },
			{ 'e', 't', 'a', 'e' },
			{ 'i', 'h', 'k', 'r' },
			{ 'i', 'f', 'l', 'v' },
	},
	d = { { 'a' }, { 'b' } };
	Solution s;
	output(s.findWords(d, c), ", ");
	output(s.findWords(b, a), ", ");
}
