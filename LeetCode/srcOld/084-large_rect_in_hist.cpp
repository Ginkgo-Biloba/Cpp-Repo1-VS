#include <vector>
#include <algorithm>
#include <cstdio>
using std::vector;
using std::pair;

int largeRectArea(vector<int> const& hist)
{
	int len = static_cast<int>(hist.size());
	if (len == 0u) return 0;
	if (len == 1u) return hist[0];

	int ans = 0;
	vector<pair<int, int>> vec;
	pair<int, int> validx(hist[0], 0);
	vec.push_back(validx);

	for (int i = 1; i < len; i++)
	{
		int h = hist[i];
		if (h < validx.first)
		{
			int idx;
			while (h < validx.first)
			{
				int cur = (i - validx.second) * validx.first;
				if (ans < cur) ans = cur;
				idx = validx.second;
				vec.pop_back();
				if (vec.empty()) break;
				validx = vec.back();
			}
			validx.first = h; validx.second = idx;
			vec.push_back(validx);
		}
		else if (h > validx.first)
		{
			validx.first = h; validx.second = i;
			vec.push_back(validx);
		}
	}

	while (!vec.empty())
	{
		validx = vec.back();
		int cur = (len - validx.second) * validx.first;
		if (ans < cur) ans = cur;
		vec.pop_back();
	}

	return ans;
}

int lranln(vector<int> const& hist, int left, int right)
{
	if (left >= right) return 0;
	vector<int>::const_iterator it = std::min_element(hist.begin() + left, hist.begin() + right);
	int const mval = (*it) * (right - left);
	int const idxMid = static_cast<int>(it - hist.begin());
	int const lval = lranln(hist, left, idxMid);
	int const rval = lranln(hist, idxMid + 1, right);
	return std::max(mval, std::max(lval, rval));
}

int largeRectAreaNlgN(vector<int> const& hist)
{
	int len = static_cast<int>(hist.size());
	if (!len) return 0;
	return lranln(hist, 0, len);
}


int main()
{
	// vector<int> hist = { 2, 1, 5, 6, 2, 3 };
	vector<int> hist(30000, 1);
	int ans0 = largeRectArea(hist);
	int ans1 = largeRectAreaNlgN(hist);
	printf("ans0 = %d, ans1 = %d\n", ans0, ans1);
}