#include "leetcode.hpp"

/* 912. 排序数组

给定一个整数数组 nums，将该数组升序排列。
*/


void adjust(vector<int>& A, int par, int len)
{
	int chd = par * 2 + 1;
	int val = A[par];
	while (chd < len)
	{
		if ((chd + 1 < len) && (A[chd] < A[chd + 1]))
			++chd;
		if (val < A[chd])
		{
			A[par] = A[chd];
			par = chd;
			chd = par * 2 + 1;
		}
		else
			break;
	}
	A[par] = val;
}


vector<int> sortArray(vector<int>& A)
{
	int len = static_cast<int>(A.size());

	for (int k = len / 2 - 1; k >= 0; --k)
		adjust(A, k, len);

	for (int k = len - 1; k >= 0; --k)
	{
		std::swap(A[0], A[k]);
		adjust(A, 0, k);
	}

	return A;
}


int main()
{
	vector<int>
		a = { 5, 2, 3, 1 },
		b = { 5, 1, 1, 2, 0, 0 },
		c = { -4, 0, 7, 4, 9, -5, -1, 0, -7, -1 };
	output(sortArray(a), "Sort an Array");
	output(sortArray(b), "Sort an Array");
	output(sortArray(c), "Sort an Array");
}
