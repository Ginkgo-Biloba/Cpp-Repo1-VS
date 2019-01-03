#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using std::ostream;

struct Interval
{
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

ostream& operator<<(ostream& os, Interval const& a)
{
	os << "[" << a.start << ", " << a.end << "]";
	return os;
}

struct CmpInterval
{
	bool operator()(Interval const& a, Interval const& b)
	{
		return (a.start < b.start) ? true :
			(b.start < a.start) ? false : (a.end < b.end);
	}
};

std::vector<Interval> merge(std::vector<Interval>& intervals)
{
	std::vector<Interval> out;
	if (intervals.empty()) return out;
	std::sort(intervals.begin(), intervals.end(), CmpInterval());
	size_t sz = intervals.size();
	Interval val = intervals[0];
	out.push_back(val);
	for (size_t i = 1; i < sz; i++)
	{
		Interval const cur = intervals[i];
		if (cur.start <= val.end)
			val.end = std::max(val.end, cur.end);
		else
		{
			out.back() = val;
			val = cur;
			out.push_back(val);
		}
	}

	out.back() = val;
	return out;
}

int main()
{
	std::vector<Interval> vec1 = { { 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 } };
	std::vector<Interval> vec2 = { { 1, 4 }, { 4, 5 } };

	std::vector<Interval> out1 = merge(vec1);
	std::vector<Interval> out2 = merge(vec2);

	std::copy(out1.begin(), out1.end(), std::ostream_iterator<Interval>(std::cout, "; "));
	std::cout << "\n";
	std::copy(out2.begin(), out2.end(), std::ostream_iterator<Interval>(std::cout, "; "));
	std::cout << "\n";
}

