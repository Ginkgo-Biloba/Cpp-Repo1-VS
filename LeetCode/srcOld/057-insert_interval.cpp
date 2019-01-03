#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using std::ostream;
using std::vector;

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

vector<Interval> insert(vector<Interval>& intervals, Interval newInt)
{
	vector<Interval> out;
	intervals.push_back(newInt);
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
	vector<Interval> vec1 = { { 1, 2 }, { 3, 5 }, { 6, 7 }, { 8, 10 }, {12, 16} };
	Interval int1 = { 4, 8 };
	vector<Interval> vec2 = { { 1, 3 }, { 6, 9 } };
	Interval int2 = { 2, 5 };

	vector<Interval> out1 = insert(vec1, int1);
	vector<Interval> out2 = insert(vec2, int2);

	std::copy(out1.begin(), out1.end(), std::ostream_iterator<Interval>(std::cout, "; "));
	std::cout << "\n";
	std::copy(out2.begin(), out2.end(), std::ostream_iterator<Interval>(std::cout, "; "));
	std::cout << "\n";
}

