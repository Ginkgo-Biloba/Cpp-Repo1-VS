#include "../srcOld/utility.hpp"

vector<vector<int>> generate(int R)
{
	vector<vector<int>> ans;
	vector<int> prev = { 1 }, cur = { 1, 1 };
	if (R >= 1) ans.push_back(prev);
	if (R >= 2) ans.push_back(cur);

	prev.reserve(R); cur.reserve(R);
	for (int r = 3; r <= R; ++r)
	{
		prev.swap(cur);
		cur.clear();
		cur.push_back(1);
		for (int c = 1; c < r - 1; ++c)
			cur.push_back(prev[c - 1] + prev[c]);
		cur.push_back(1);
		ans.push_back(cur);
	}

	return ans;
}

vector<int> getRow(int R)
{
	vector<int> prev = { 1 }, cur = { 1, 1 };
	if (R == 0) return prev; // 这里 R 从 0 开始
	if (R == 1) return cur;

	prev.reserve(R); cur.reserve(R);
	for (int r = 1; r <= R; ++r)
	{
		prev.swap(cur);
		cur.clear();
		cur.push_back(1);
		for (int c = 1; c < r; ++c)
			cur.push_back(prev[c - 1] + prev[c]);
		cur.push_back(1);
	}

	return cur;
}

int main()
{
	vector<vector<int>> ans = generate(5);
	output(ans, "Pascal's Triangle");
	vector<int> row = getRow(3);
	output(row, "Pascal's Triangle 2");
}
