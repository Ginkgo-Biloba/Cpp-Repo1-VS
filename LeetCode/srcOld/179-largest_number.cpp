#include "leetcode.hpp"


string largestNumber1(vector<int>& nums)
{
	string ans;
	char buf[16]; bool allzero = true;
	int total = 0; 
	vector<string> strs;
	for (int i : nums)
	{
		allzero = allzero && (i == 0);
		total += sprintf(buf, "%d", i);
		strs.push_back(string(buf));
	}
	if (allzero)
		return string("0");

	std::sort(strs.begin(), strs.end(),
		[](string const& x, string const& y) -> bool
	{
		string xy = x + y;
		string yx = y + x;
		return xy > yx;
	});

	ans.reserve(total + 1);
	for (string const& s : strs)
		ans += s;
	return ans;
}


string largestNumber(vector<int>& nums)
{
	string ans;
	char buf[16]; bool allzero = true;
	int total = 0;
	vector<string> strs;
	for (int i : nums)
	{
		allzero = allzero && (i == 0);
		total += sprintf(buf, "%d", i);
		strs.push_back(string(buf));
	}
	if (allzero)
		return string("0");

	std::sort(strs.begin(), strs.end(),
		[](string const& x, string const& y) -> bool
	{
		// printf("x = %s; y = %s\n", x.c_str(), y.c_str());

		size_t const xlen = x.length(), ylen = y.length();
		size_t maxlen = std::max(xlen, ylen);
		size_t minlen = std::min(xlen, ylen);
		maxlen = ((maxlen + minlen - 1) / minlen) * minlen;
		for (size_t i = 0; i < maxlen; ++i)
		{
			int ix = x[i % xlen], iy = y[i % ylen];
			if (ix > iy)
				return true;
			if (ix < iy)
				return false;
		}
		return (xlen < ylen);
	});

	ans.reserve(total + 1);
	for (string const& s : strs)
		ans += s;
	return ans;
}


int main()
{
	vector<int> nums = { 9051, 5526, 2264, 5041, 1630, 5906, 6787, 8382, 4662, 4532, 6804, 4710, 4542, 2116, 7219, 8701, 8308, 957, 8775, 4822, 396, 8995, 8597, 2304, 8902, 830, 8591, 5828, 9642, 7100, 3976, 5565, 5490, 1613, 5731, 8052, 8985, 2623, 6325, 3723, 5224, 8274, 4787, 6310, 3393, 78, 3288, 7584, 7440, 5752, 351, 4555, 7265, 9959, 3866, 9854, 2709, 5817, 7272, 43, 1014, 7527, 3946, 4289, 1272, 5213, 710, 1603, 2436, 8823, 5228, 2581, 771, 3700, 2109, 5638, 3402, 3910, 871, 5441, 6861, 9556, 1089, 4088, 2788, 9632, 6822, 6145, 5137, 236, 683, 2869, 9525, 8161, 8374, 2439, 6028, 7813, 6406, 7519 };
	string ans = largestNumber(nums);
	printf("%1s = %s\n", "largestNumber", ans.c_str());
}
