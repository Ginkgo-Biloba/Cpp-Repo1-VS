#include "leetcode.hpp"

/* 857. 雇佣 K 名工人的最低成本

有 N 名工人。
第 i 名工人的工作质量为 quality[i] ，其最低期望工资为 wage[i] 。

现在我们想雇佣 K 名工人组成一个工资组。
在雇佣 一组 K 名工人时，我们必须按照下述规则向他们支付工资：
	对工资组中的每名工人，应当按其工作质量与同组其他工人的工作质量的比例来支付工资。
	工资组中的每名工人至少应当得到他们的最低期望工资。

返回组成一个满足上述条件的工资组至少需要多少钱。

示例 1：
输入： quality = [10,20,5], wage = [70,50,30], K = 2
输出： 105.00000
解释： 我们向 0 号工人支付 70，向 2 号工人支付 35。

示例 2：
输入： quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
输出： 30.66667
解释： 我们向 0 号工人支付 4，向 2 号和 3 号分别支付 13.33333。

提示：
	1 <= K <= N <= 10000，其中 N = quality.length = wage.length
	1 <= quality[i] <= 10000
	1 <= wage[i] <= 10000
	与正确答案误差在 10^-5 之内的答案将被视为正确的。
*/

// https://leetcode.com/problems/minimum-cost-to-hire-k-workers/discuss/141768/Detailed-explanation-O(NlogN)
// 抄的
double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K)
{
	size_t szK = K;
	double ans = DBL_MAX, qsum = 0;
	int len = static_cast<int>(quality.size());
	vector<pair<double, double>> worker;
	priority_queue<double> pq;
	worker.reserve(len);

	for (int i = 0; i < len; ++i)
		worker.emplace_back(1.0 * wage[i] / quality[i], quality[i]);
	sort(worker.begin(), worker.end());

	for (auto w : worker)
	{
		qsum += w.second;
		pq.push(w.second);
		if (pq.size() > szK)
		{
			qsum -= pq.top();
			pq.pop();
		}
		if (pq.size() == szK)
			ans = std::min(ans, qsum * w.first);
	}

	return ans;
}


int main()
{
	vector<int>
		q0 = { 10, 20, 5 },
		w0 = { 70, 50, 30 },
		q1 = { 3, 1, 10, 10, 1 },
		w1 = { 4, 8, 2, 2, 7 };
	OutExpr(mincostToHireWorkers(q0, w0, 2), "%f");
	OutExpr(mincostToHireWorkers(q1, w1, 3), "%f");
}
