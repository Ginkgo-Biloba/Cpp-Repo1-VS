#include "leetcode.hpp"

/* 208. 实现 Trie (前缀树)

实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。

示例:

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // 返回 true
trie.search("app");     // 返回 false
trie.startsWith("app"); // 返回 true
trie.insert("app");
trie.search("app");     // 返回 true

说明:
	你可以假设所有的输入都是由小写字母 a-z 构成的。
	保证所有输入均为非空字符串。
*/

class Trie
{
	struct Node
	{
		// val is not used...
		char val, leaf;
		Node* data[26];
	};

	Node head;
	vector<Node*> buffer;

	Node* find(string const& word)
	{
		int len = static_cast<int>(word.length());
		Node* node = &head;
		for (int i = 0; i < len; ++i)
		{
			int c = word[i] - 'a';
			if (!(node->data[c]))
				return nullptr;
			node = node->data[c];
		}
		return node;
	}


public:
	/** Initialize your data structure here. */
	Trie()
	{
		memset(&head, 0, sizeof(head));
	}

	~Trie()
	{
		for (auto node : buffer)
			free(node);
	}

	/** Inserts a word into the trie. */
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

	/** Returns if the word is in the trie. */
	bool search(string word)
	{
		Node* node = find(word);
		return node && (node->leaf);
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix)
	{
		Node* node = find(prefix);
		return node;
	}
};


int main()
{
	Trie t;
	t.insert("apple");
	OutBool(t.search("apple"));
	OutBool(t.search("app"));
	OutBool(t.startsWith("app"));
	t.insert("app");
	OutBool(t.search("app"));
}
