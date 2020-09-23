#include "leetcode.hpp"

/* 1032. 字符流

按下述要求实现 StreamChecker 类：

StreamChecker(words)：构造函数，用给定的字词初始化数据结构。
query(letter)：如果存在某些 k >= 1，可以用查询的最后 k个字符（按从旧到新顺序，包括刚刚查询的字母）拼写出给定字词表中的某一字词时，返回 true。否则，返回 false。

示例：

StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // 初始化字典
streamChecker.query('a');          // 返回 false
streamChecker.query('b');          // 返回 false
streamChecker.query('c');          // 返回 false
streamChecker.query('d');          // 返回 true，因为 'cd' 在字词表中
streamChecker.query('e');          // 返回 false
streamChecker.query('f');          // 返回 true，因为 'f' 在字词表中
streamChecker.query('g');          // 返回 false
streamChecker.query('h');          // 返回 false
streamChecker.query('i');          // 返回 false
streamChecker.query('j');          // 返回 false
streamChecker.query('k');          // 返回 false
streamChecker.query('l');          // 返回 true，因为 'kl' 在字词表中。

提示：
	1 <= words.length <= 2000
	1 <= words[i].length <= 2000
	字词只包含小写英文字母。
	待查项只包含小写英文字母。
	待查项最多 40000 个。
*/


class Trie
{
public:
	enum { CharNum = 26 };

	struct Node
	{
		char stop;
		Node* child[CharNum];
	};

private:
	vector<Node*> refptr;
	size_t idxptr;
	Node root;

	Node* make()
	{
		Node* t = nullptr;
		if (idxptr < refptr.size())
			t = refptr[idxptr];
		else
		{
			t = new Node;
			refptr.emplace_back(t);
		}
		++idxptr;
		memset(t, 0, sizeof(*t));
		return t;
	}

public:
	Trie(int len = (1 << 12))
	{
		while (len--)
			refptr.emplace_back(new Node);
		clear();
	}

	~Trie()
	{
		for (Node* t : refptr)
			delete t;
	}

	Node const* getRoot()
	{
		return &root;
	}

	int clear()
	{
		int len = static_cast<int>(idxptr);
		memset(&root, 0, sizeof(root));
		idxptr = 0;
		return static_cast<int>(len);
	}

	bool insert(string const& s)
	{
		bool have = true;
		Node *p = &root, *t = nullptr;
		for (char c : s)
		{
			int i = c - 'a';
			t = p->child[i];
			if (!t)
			{
				have = false;
				t = make();
				p->child[i] = t;
			}
			p = t;
		}
		p->stop = 1;
		return have;
	}

	bool search(string const& s)
	{
		Node *p = &root, *t;
		for (char c : s)
		{
			int i = c - 'a';
			t = p->child[i];
			if (!t)
				return false;
			p = t;
		}
		return p->stop != 0;
	}
};

// 大的缓存
// 如果放在 Solution 里面，每次构造和析构会超时
// 如果放在外面，速度竟然 80%
static Trie trie(1 << 12);

// https://leetcode.com/problems/stream-of-characters/discuss/278769/Java-Trie-Solution
// 抄的
class StreamChecker
{
	string sb;

public:
	StreamChecker(vector<string>& words)
	{
		trie.clear();
		for (string w : words)
		{
			reverse(w.begin(), w.end());
			trie.insert(w);
		}
	}

	bool query(char letter)
	{
		Trie::Node const *p = trie.getRoot(), *t;
		sb.push_back(letter);
		int i = static_cast<int>(sb.size());
		for (--i; i >= 0; --i)
		{
			t = p->child[sb[i] - 'a'];
			if (!t)
				return false;
			if (t->stop)
				return true;
			p = t;
		}
		return false;
	}
};


int main()
{
	vector<string> a = { "cd", "f", "kl" };
	StreamChecker s(a);
	for (char c = 'a'; c <= 'z'; ++c)
		printf("%c = %s\n", c, boolstr[s.query(c)]);
}
