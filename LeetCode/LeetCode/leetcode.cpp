#include "leetcode.hpp"

/*


*/

int adds(int a, int b)
{
	if (a > 0)
	{
		if (b > INT_MAX - a)
			return INT_MAX;
	}
	else if (b < INT_MIN - a)
		return INT_MIN;
	return a + b;
}

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x)
		: val(x), left(NULL), right(NULL)
	{}
};

// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x)
		: val(x), next(NULL)
	{}
};


class SegTree
{
	vector<int> sum;
	int len;

	int lowbit(int i)
	{
		return i & (-i);
	}

public:
	SegTree(int size)
	{
		len = size + 1;
		sum.resize(len);
	}

	void update(int i, int x)
	{
		++i;
		assert(i < len);
		for (; i < len; i += lowbit(i))
			sum[i] += x;
	}

	int get(int i)
	{
		// 需要 +1 要不 0 那里退不出去循环
		++i;
		assert(i < len);
		int r = 0;
		for (; i > 0; i -= lowbit(i))
			r += sum[i];
		return r;
	}
};



int main()
{
}

