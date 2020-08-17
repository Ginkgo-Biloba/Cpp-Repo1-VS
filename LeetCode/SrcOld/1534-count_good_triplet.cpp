#include "leetcode.hpp"

/*


*/

int countGoodTriplets(vector<int>& A, int a, int b, int c)
{
	int len = static_cast<int>(A.size());
	int ans = 0;
	for (int i = 0; i < len; ++i)
		for (int j = i + 1; j < len; ++j)
			for (int k = j + 1; k < len; ++k)
				if (abs(A[i] - A[j]) <= a
					&& abs(A[j] - A[k]) <= b
					&& abs(A[i] - A[k]) <= c)
					++ans;
	return ans;
}

int main()
{}
