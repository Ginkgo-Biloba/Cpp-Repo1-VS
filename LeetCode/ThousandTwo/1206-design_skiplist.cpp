#include "leetcode.hpp"

/* 1206. 设计跳表

不使用任何库函数，设计一个跳表。

跳表是在 O(log(n)) 时间内完成增加、删除、搜索操作的数据结构。跳表相比于树堆与红黑树，其功能与性能相当，并且跳表的代码长度相较下更短，其设计思想与链表相似。

例如，一个跳表包含 [30, 40, 50, 60, 70, 90]，然后增加 80、45 到跳表中，以下图的方式操作：

https://assets.leetcode.com/uploads/2019/09/27/1506_skiplist.gif
Artyom Kalinin [CC BY-SA 3.0], via Wikimedia Commons

跳表中有很多层，每一层是一个短的链表。在第一层的作用下，增加、删除和搜索操作的时间复杂度不超过 O(n)。跳表的每一个操作的平均时间复杂度是 O(log(n))，空间复杂度是 O(n)。

在本题中，你的设计应该要包含这些函数：
	bool search(int target) : 返回target是否存在于跳表中。
	void add(int num): 插入一个元素到跳表。
	bool erase(int num): 在跳表中删除一个值，如果 num 不存在，直接返回false。如果存在多个 num，删除其中任意一个即可。

了解更多 : https://en.wikipedia.org/wiki/Skip_list

注意，跳表中可能存在多个相同的值，你的代码需要处理这种情况。

样例:
Skiplist skiplist = new Skiplist();
skiplist.add(1);
skiplist.add(2);
skiplist.add(3);
skiplist.search(0);   // 返回 false
skiplist.add(4);
skiplist.search(1);   // 返回 true
skiplist.erase(0);    // 返回 false，0 不在跳表中
skiplist.erase(1);    // 返回 true
skiplist.search(1);   // 返回 false，1 已被擦除

约束条件:
	0 <= num, target <= 20000
	最多调用 50000 次 search, add, 以及 erase操作。
*/

struct Node
{
	int val;
	Node *prev, *next, *down;
};

class NodePool
{
	int size, idx;
	vector<Node> buffer;
	vector<Node*> extra;
	Node *data, *dataend;

public:
	NodePool(int s)
		: size(s)
		, idx(0)
	{
		buffer.resize(size);
		data = buffer.data();
		dataend = data + size;
		memset(data, 0, size * sizeof(Node));
	}

	~NodePool()
	{
		for (Node* p : extra)
			free(p);
	}

	Node* get(int val)
	{
		Node* p = nullptr;
		if (idx < size)
		{
			p = data + idx;
			++idx;
		}
		else
		{
			p = static_cast<Node*>(malloc(sizeof(Node)));
			memset(p, 0, sizeof(Node));
			extra.push_back(p);
		}
		p->val = val;
		return p;
	}
};

static NodePool NP(50000);

// https://leetcode.com/problems/design-skiplist/discuss/393686/C%2B%2B-Top-down-searchinserterase-bottom-up-randomly-generate-inner-node
// 抄的
class Skiplist
{
	vector<Node*> path;
	Node* head;
	int layer;

public:
	Skiplist()
		: head(nullptr)
	{
		layer = 0;
		srand(static_cast<unsigned>(time(NULL)));
	}

	bool search(int target)
	{
		if (!head)
			return false;
		Node* p = head;
		while (p)
		{
			while (p->next && p->next->val < target)
				p = p->next;
			if (p->next && p->next->val == target)
				return true;
			p = p->down;
		}
		return false;
	}

	void add(int num)
	{
		Node* p = head;
		int len = layer;
		path.assign(len, nullptr);
		for (int i = layer - 1; i >= 0; --i)
		{
			while (p->next && p->next->val < num)
				p = p->next;
			path[i] = p;
			p = p->down;
		}

		for (int i = 0; i <= len; ++i)
		{
			p = NP.get(num);
			if (i == layer)
			{
				Node* last = head;
				head = NP.get(0);
				head->down = last;
				head->next = p;
				p->prev = head;
				++layer;
			}
			else
			{
				p->next = path[i]->next;
				p->prev = path[i];
				path[i]->next = p;
				if (p->next)
					p->next->prev = p;
			}
			if (i != 0)
				p->down = path[i - 1]->next;
			if (rand() & 1)
				break;
		}
	}

	bool erase(int num)
	{
		Node* p = head;
		for (int i = layer - 1; (i >= 0) && p; --i)
		{
			while (p->next && p->next->val < num)
				p = p->next;
			if (p->next && p->next->val == num)
			{
				p = p->next;
				while (p)
				{
					p->prev->next = p->next;
					if (p->next)
						p->next->prev = p->prev;
					p = p->down;
				}
				while (head && !(head->next))
				{
					head = head->down;
					--layer;
				}
				return true;
			}
			p = p->down;
		}
		return false;
	}
};


int main()
{
	Skiplist s;
	s.add(1);
	s.add(2);
	s.add(3);
	OutBool(s.search(0));
	s.add(4);
	OutBool(s.search(1));
	OutBool(s.erase(0));
	OutBool(s.erase(1));
	OutBool(s.search(1));
}
