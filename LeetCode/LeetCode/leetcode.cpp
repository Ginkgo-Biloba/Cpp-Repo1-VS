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

unsigned popcnt(unsigned n)
{
#if defined _MSC_VER
	return __popcnt(n);
#elif defined __GNUC__
	return __builtin_popcount(n);
#else
	n = n - ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n + (n >> 4)) & 0x0f0f0f0f;
	n = (n * 0x1010101) >> 24;
	return n;
#endif
}


int main()
{
	for (int i = 0; i < 64; ++i)
	{
		printf("%3d: %d,  ", i, popcnt(i));
		if ((i & 7) == 7)
			printf("\n");
	}
}
