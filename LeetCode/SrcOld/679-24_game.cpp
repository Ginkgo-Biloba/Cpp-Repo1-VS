#include "leetcode.hpp"

/* 679. 24 点游戏

你有 4 张写有 1 到 9 数字的牌。
你需要判断是否能通过 *，/，+，-，(，) 的运算得到 24。

示例 1:
输入: [4, 1, 8, 7]
输出: True
解释: (8-4) * (7-1) = 24

示例 2:
输入: [1, 2, 1, 2]
输出: False

注意:
	除法运算符 / 表示实数除法，而不是整数除法。例如 4 / (1 - 2/3) = 12 。
	每个运算符对两个数进行运算。特别是我们不能用 - 作为一元运算符。例如，[1, 1, 1, 1] 作为输入时，表达式 -1 - 1 - 1 - 1 是不允许的。
	你不能将数字连接在一起。例如，输入为 [1, 2, 1, 2] 时，不能写成 12 + 12 。
*/

// https://leetcode.com/problems/24-game/discuss/107678/C%2B%2B-Concise-code
// 抄的
using std::abs;

class Solution
{
	bool valid(double a, double b)
	{
		double const eps = 0.0001;
		return false
			|| abs(a + b - 24.0) < eps
			|| abs(a - b - 24.0) < eps
			|| abs(a * b - 24.0) < eps
			|| (b && abs(a / b - 24.0) < eps);
	}

	bool valid(double a, double b, double c)
	{
		return false
			|| valid(a + b, c)
			|| valid(a - b, c)
			|| valid(a * b, c)
			|| (b && valid(a / b, c))
			|| valid(a, b + c)
			|| valid(a, b - c)
			|| valid(a, b * c)
			|| (c && valid(a, b / c));
	}

	bool valid(double a, double b, double c, double d)
	{
		return false
			|| valid(a + b, c, d)
			|| valid(a - b, c, d)
			|| valid(a * b, c, d)
			|| valid(a / b, c, d)
			|| valid(a, b + c, d)
			|| valid(a, b - c, d)
			|| valid(a, b * c, d)
			|| valid(a, b / c, d)
			|| valid(a, b, c + d)
			|| valid(a, b, c - d)
			|| valid(a, b, c * d)
			|| valid(a, b, c / d);
	}


public:
	bool judgePoint24(vector<int> nums)
	{
		sort(nums.begin(), nums.end());
		do
		{
			if (valid(nums[0], nums[1], nums[2], nums[3]))
				return true;
		} while (std::next_permutation(nums.begin(), nums.end()));
		return false;
	}
};


// https://leetcode.com/problems/24-game/discuss/107670/ub5a2ube3buac01uac4eub0c7uac05uac38uae9aubd5fuc223uc684ubd74ubd5eub93cuac08uac0cub914ub58cuc60auba54ub284uc22duceb8uae36uae9buc616uac0dub1d0uca62uacf4ub4c7uac6fuad84uc615uc679ub21euc1b4uac43ub057uae2cub549uadbfuac00uc300ub090uac44uc224ubeb4ub298uac58uaf78uc222uac42uac0buac03ucad0uaf14uc1beuca61uc1d4uc1bfub05bub91cuac04ube3auca6cuc6e8ub534uc620ub91buac02ubd6aub360ub1a4ube50uc60buadd2ub282uac30uac16ub1a5uadbeuac06uc60cubf18ubb30uac70uac0euae37ub0a4uacbc/109855
static std::set<int> const NOT_24 = {
	1111, 1112, 1113, 1114, 1115, 1116, 1117, 1119, 1122, 1123, 1124, 1125, 1133,
	1159, 1167, 1177, 1178, 1179, 1189, 1199, 1222, 1223, 1299, 1355, 1499, 1557,
	1558, 1577, 1667, 1677, 1678, 1777, 1778, 1899, 1999, 2222, 2226, 2279, 2299,
	2334, 2555, 2556, 2599, 2677, 2777, 2779, 2799, 2999, 3358, 3467, 3488, 3555,
	3577, 4459, 4466, 4467, 4499, 4779, 4999, 5557, 5558, 5569, 5579, 5777, 5778,
	5799, 5899, 5999, 6667, 6677, 6678, 6699, 6777, 6778, 6779, 6788, 6999, 7777,
	7778, 7779, 7788, 7789, 7799, 7888, 7899, 7999, 8888, 8889, 8899, 8999, 9999
};
bool judgePoint24(vector<int>& nums)
{
	sort(nums.begin(), nums.end());
	int key = nums[0] * 1000 + nums[1] * 100 + nums[2] * 10 + nums[3];
	return NOT_24.find(key) == NOT_24.end();
}

int main()
{
	Solution s;
	OutExpr(boolstr[s.judgePoint24({ 1, 2, 3, 4 })], "%s");
}
