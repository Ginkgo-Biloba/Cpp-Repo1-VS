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
		: val(x)
		, left(NULL)
		, right(NULL)
	{}
};

// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x)
		: val(x)
		, next(NULL)
	{}
};


int main()
{}
