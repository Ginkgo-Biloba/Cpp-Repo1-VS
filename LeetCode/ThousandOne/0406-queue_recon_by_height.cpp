#include "leetcode.hpp"

/* 406. 根据身高重建队列

假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身高，k是排在这个人前面且身高大于或等于h的人数。 编写一个算法来重建这个队列。

注意：
总人数少于1100人。

示例

输入:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

输出:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
*/

// https://leetcode.com/problems/queue-reconstruction-by-height/discuss/287878/A-simple-C%2B%2B-solution-with-explanation
// 抄的
vector<vector<int>> reconstructQueue(vector<vector<int>>& pp)
{
	int len = static_cast<int>(pp.size());
	std::sort(pp.begin(), pp.end(),
		[](vector<int> const& a, vector<int> const& b)
	{
		return (a[0] > b[0]) || ((a[0] == b[0]) && (a[1] < b[1]));
	});

	for (int i = 0; i < len; ++i)
	{
		// vector 复制太费时间
		int val = pp[i][0];
		int pos = pp[i][1];
		for (int k = i; k > pos; --k)
		{
			pp[k][0] = pp[k - 1][0];
			pp[k][1] = pp[k - 1][1];
		}
		pp[pos][0] = val;
		pp[pos][1] = pos;
	}
	return pp;
}


int main()
{
	vector<vector<int>> pp = { { 7, 0 }, { 4, 4 }, { 7, 1 }, { 5, 0 }, { 6, 1 }, { 5, 2 } };
	reconstructQueue(pp);
	output(pp, "reconstructQueue");
};


