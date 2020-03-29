#include "leetcode.hpp"

/* 1157. 子数组中占绝大多数的元素

实现一个 MajorityChecker 的类，它应该具有下述几个 API：
	MajorityChecker(int[] arr) 会用给定的数组 arr 来构造一个 MajorityChecker 的实例。
	int query(int left, int right, int threshold) 有这么几个参数：
			0 <= left <= right < arr.length 表示数组 arr 的子数组的长度。
			2 * threshold > right - left + 1，也就是说阈值 threshold 始终比子序列长度的一半还要大。

每次查询 query(...) 会返回在 arr[left], arr[left+1], ..., arr[right] 中至少出现阈值次数 threshold 的元素，如果不存在这样的元素，就返回 -1。

示例：
MajorityChecker majorityChecker = new MajorityChecker([1,1,2,2,1,1]);
majorityChecker.query(0,5,4); // 返回 1
majorityChecker.query(0,3,3); // 返回 -1
majorityChecker.query(2,3,2); // 返回 2

提示：
	1 <= arr.length <= 20000
	1 <= arr[i] <= 20000
	对于每次查询，0 <= left <= right < len(arr)
	对于每次查询，2 * threshold > right - left + 1
	查询次数最多为 10000
*/

// https://leetcode.com/problems/online-majority-element-in-subarray/discuss/356227/C%2B%2B-Codes-of-different-approaches-(Random-Pick-Trade-off-Segment-Tree-Bucket)
// 抄的
class MajorityChecker
{
	int len;
	vector<int> A;
	unordered_map<int, vector<int>> idx;
	vector<int> popular;
	int lookup;

	int vote(int L, int R)
	{
		int val = A[L], cnt = 1;
		for (int i = L + 1; i <= R; ++i)
		{
			if (A[i] == val)
				++cnt;
			else
			{
				--cnt;
				if (cnt < 0)
				{
					val = A[i];
					cnt = 1;
				}
			}
		}
		cnt = 0;
		for (int i = L; i <= R; ++i)
		{
			if (A[i] == val)
				++cnt;
		}
		return (cnt * 2 > R - L + 1) ? val : -1;
	}

	int occurrence(int val, int L, int R)
	{
		auto itval = idx.find(val);
		if (itval == idx.end())
			return 0;
		vector<int> const& p = itval->second;
		auto it0 = lower_bound(p.begin(), p.end(), L);
		if (it0 == p.end())
			return 0;
		auto it1 = upper_bound(p.begin(), p.end(), R);
		return static_cast<int>(it1 - it0);
	}

public:
	MajorityChecker(vector<int>& arr)
	{
		A.swap(arr);
		len = static_cast<int>(A.size());
		for (int i = 0; i < len; ++i)
			idx[A[i]].push_back(i);
		lookup = static_cast<int>(::sqrt(len) + 0.5);
		for (auto const& kv : idx)
		{
			if (kv.second.size() >= static_cast<size_t>(lookup))
				popular.push_back(kv.first);
		}
	}

	int query(int left, int right, int threshold)
	{
		if (threshold <= lookup)
		{
			int cand = vote(left, right);
			if (cand != -1 && occurrence(cand, left, right) >= threshold)
				return cand;
		}
		else
			for (int cand : popular)
			{
				if (occurrence(cand, left, right) >= threshold)
					return cand;
			}
		return -1;
	}
};


int main()
{
	vector<int> a = { 1, 1, 2, 2, 1, 1 };
	MajorityChecker m(a);
	OutExpr(m.query(0, 5, 4), "%d");
	OutExpr(m.query(0, 3, 3), "%d");
	OutExpr(m.query(2, 3, 2), "%d");
}
