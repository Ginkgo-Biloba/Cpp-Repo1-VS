#include "../srcOld/utility.hpp"

bool all_less(vector<string>& A, int m, int n)
{
	size_t const len = A.size();
	for (size_t i = 0; i < len; ++i)
	{
		if (A[i][m] > A[i][n])
			return false;
	}
	return true;
}


int minDeletionSize(vector<string>& A)
{
	int const str_len = static_cast<int>(A[0].size());
	vector<int> dp(str_len); dp[0] = 1;
	int max_len = 1;
	if (str_len == 1) return 0;

	for (int right = 1; right < str_len; ++right)
	{
		int cur_len = 1;
		for (int left = 0; left < right; ++left)
		{
			if (all_less(A, left, right))
				cur_len = std::max(cur_len, dp[left] + 1);
		}
		dp[right] = cur_len;
		if (max_len < cur_len) max_len = cur_len;
	}
	return str_len - max_len;
}



int main()
{
	vector<string> strs = { "edcba" };
	int n = minDeletionSize(strs);
	printf("minDeletionSize = %d\n", n);
}
