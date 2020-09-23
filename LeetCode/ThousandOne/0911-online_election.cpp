#include "leetcode.hpp"

/* 911. 在线选举

在选举中，第 i 张票是在时间为 times[i] 时投给 persons[i] 的。

现在，我们想要实现下面的查询函数：
	TopVotedCandidate.q(int t) 将返回在 t 时刻主导选举的候选人的编号。

在 t 时刻投出的选票也将被计入我们的查询之中。
在平局的情况下，最近获得投票的候选人将会获胜。

示例：
输入：
["TopVotedCandidate","q","q","q","q","q","q"],
[[[0,1,1,0,0,1,0],[0,5,10,15,20,25,30]],[3],[12],[25],[15],[24],[8]]
输出：[null,0,1,1,0,0,1]
解释：
时间为 3，票数分布情况是 [0]，编号为 0 的候选人领先。
时间为 12，票数分布情况是 [0,1,1]，编号为 1 的候选人领先。
时间为 25，票数分布情况是 [0,1,1,0,0,1]，编号为 1 的候选人领先（因为最近的投票结果是平局）。
在时间 15、24 和 8 处继续执行 3 个查询。

提示：
	1 <= persons.length = times.length <= 5000
	0 <= persons[i] <= persons.length
	times 是严格递增的数组，所有元素都在 [0, 10^9] 范围中。
	每个测试用例最多调用 10000 次 TopVotedCandidate.q。
	TopVotedCandidate.q(int t) 被调用时总是满足 t >= times[0]。
*/

class TopVotedCandidate
{
	unordered_map<int, int> M;
	vector<int> T;

public:
	TopVotedCandidate(vector<int>& persons, vector<int>& times)
	{
		int n = static_cast<int>(persons.size()), lead = 0;
		unordered_map<int, int> count;
		T.swap(times);
		for (int i = 0; i < n; ++i)
		{
			int p = persons[i];
			++(count[p]);
			if (count[p] >= count[lead])
				lead = p;
			M[T[i]] = lead;
		}
	}

	int q(int t)
	{
		auto it = upper_bound(T.begin(), T.end(), t);
		--it;
		return M[*it];
	}
};

int main()
{
	vector<int>
		p0 = { 0, 1, 1, 0, 0, 1, 0 },
		t0 = { 0, 5, 10, 15, 20, 25, 30 };
	TopVotedCandidate v(p0, t0);
	OutExpr(v.q(3), "%d");
	OutExpr(v.q(12), "%d");
	OutExpr(v.q(25), "%d");
	OutExpr(v.q(15), "%d");
	OutExpr(v.q(24), "%d");
	OutExpr(v.q(8), "%d");
}
