#include "leetcode.hpp"

/* 211. 添加与搜索单词 - 数据结构设计

设计一个支持以下两种操作的数据结构：

void addWord(word)
bool search(word)

search(word) 可以搜索文字或正则表达式字符串，字符串只包含字母 . 或 a-z 。
. 可以表示任何一个字母。

示例:
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true

说明:
你可以假设所有单词都是由小写字母 a-z 组成的。
*/

class WordDictionary
{
	struct Node
	{
		char leaf;
		Node* data[26];
	};

	Node head;
	vector<Node*> buffer;

public:
	/** Initialize your data structure here. */
	WordDictionary()
	{
		memset(&head, 0, sizeof(Node));
	}

	~WordDictionary()
	{
		for (Node* node : buffer)
			free(node);
	}

	/** Adds a word into the data structure. */
	void addWord(string word)
	{
		Node* node = &head;
		for (char w : word)
		{
			int c = w - 'a';
			if (!(node->data[c]))
			{
				Node* tmp = static_cast<Node*>(calloc(1, sizeof(Node)));
				buffer.push_back(tmp);
				node->data[c] = tmp;
			}
			node = node->data[c];
		}
		node->leaf = 1;
	}

	/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
	bool search(string word)
	{
		vector<Node*> curr, next;
		curr.push_back(&head);
		for (char w : word)
		{
			int c = w - 'a';
			if (curr.empty())
				return false;
			next.clear();
			for (Node* node : curr)
			{
				if (w == '.')
					for (int i = 0; i < 26; ++i)
					{
						if (node->data[i])
							next.push_back(node->data[i]);
					}
				else
				{
					if (node->data[c])
						next.push_back(node->data[c]);
				}
			}
			next.swap(curr);
		}
		for (Node* node : curr)
		{
			if (node->leaf)
				return true;
		}
		return false;
	}
};


int main()
{
	WordDictionary d;
	d.addWord("bad");
	d.addWord("dad");
	d.addWord("mad");
	OutBool(d.search("pad"));
	OutBool(d.search("bad"));
	OutBool(d.search(".ad"));
	OutBool(d.search("b.."));
}
