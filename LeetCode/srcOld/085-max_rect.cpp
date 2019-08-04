#include "leetcode.hpp"


int largestRectangleArea(vector<int>& height)
{
	int ret = 0;
	height.push_back(-1);
	int const len = static_cast<int>(height.size());
	vector<int> index; index.reserve(len);

	for (int i = 0; i < len; ++i)
	{
		while (!index.empty() && (height[index.back()] >= height[i]))
		{
			int h = height[index.back()];
			index.pop_back();
			int const sidx = index.empty() ? -1 : index.back();
			h *= (i - sidx - 1);
			if (ret < h) ret = h;
		}
		index.push_back(i);
	}

	height.pop_back();
	return ret;
}

int maximalRectangle(vector<vector<char>> const& matrix)
{
	if (matrix.empty()) return 0;
	int ans = 0;
	int const rows = static_cast<int>(matrix.size());
	int const cols = static_cast<int>(matrix[0].size());
	vector<int> height(cols, 0);

	for (int r = 0; r < rows; ++r)
	{
		char const* ptr = matrix[r].data();
		for (int c = 0; c < cols; ++c)
		{
			if (ptr[c] == '0') height[c] = 0;
			else ++(height[c]);
		}
		int const cur = largestRectangleArea(height);
		if (ans < cur) ans = cur;
	}

	return ans;
}

int main()
{
	vector<vector<char>> matrix = \
	{ 
		{'1', '0', '1', '0', '0'},
		{'1', '0', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '0', '0', '1', '0'} 
	};
	int ans = maximalRectangle(matrix);
	printf("%1s = %d\n", "maximalRectangle", ans);
}
