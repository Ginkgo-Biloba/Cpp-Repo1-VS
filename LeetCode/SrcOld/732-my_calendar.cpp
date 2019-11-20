#include "leetcode.hpp"

/* 729. 我的日程安排表 I

实现一个 MyCalendar 类来存放你的日程安排。
如果要添加的时间内没有其他安排，则可以存储这个新的日程安排。

MyCalendar 有一个 book(int start, int end)方法，它意味着在 start 到 end 时间内增加一个日程安排。
注意，这里的时间是半开区间，即 [start, end), 实数 x 的范围为，start <= x < end。

当两个日程安排有一些时间上的交叉时（例如两个日程安排都在同一时间内），就会产生重复预订。

每次调用 MyCalendar.book方法时，如果可以将日程安排成功添加到日历中而不会导致重复预订，返回 true。
否则，返回 false 并且不要将该日程安排添加到日历中。

请按照以下步骤调用 MyCalendar 类:
	MyCalendar cal = new MyCalendar();
	MyCalendar.book(start, end)

示例 1:
MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(15, 25); // returns false
MyCalendar.book(20, 30); // returns true
解释:
第一个日程安排可以添加到日历中.  第二个日程安排不能添加到日历中，因为时间 15 已经被第一个日程安排预定了。
第三个日程安排可以添加到日历中，因为第一个日程安排并不包含时间 20 。

说明:
	每个测试用例，调用 MyCalendar.book 函数最多不超过 100 次。
	调用函数 MyCalendar.book(start, end)时， start 和 end 的取值范围为 [0, 10^9]。
*/

class MyCalendar
{
	std::vector<pair<int, int>> vp;

public:
	MyCalendar()
	{
		vp.reserve(100);
	}

	bool book(int start, int end)
	{
		for (auto p : vp)
		{
			if (std::max(p.first, start) < std::min(p.second, end))
				return false;
		}
		vp.emplace_back(start, end);
		return true;
	}
};


/* 731. 我的日程安排表 II

实现一个 MyCalendar 类来存放你的日程安排。
如果要添加的时间内不会导致三重预订时，则可以存储这个新的日程安排。

MyCalendar 有一个 book(int start, int end)方法，它意味着在 start 到 end 时间内增加一个日程安排。
注意，这里的时间是半开区间，即 [start, end), 实数 x 的范围为，start <= x < end。

当三个日程安排有一些时间上的交叉时（例如三个日程安排都在同一时间内），就会产生三重预订。

每次调用 MyCalendar.book方法时，如果可以将日程安排成功添加到日历中而不会导致三重预订，返回 true。
否则，返回 false 并且不要将该日程安排添加到日历中。

请按照以下步骤调用MyCalendar 类: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)

示例：
MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(50, 60); // returns true
MyCalendar.book(10, 40); // returns true
MyCalendar.book(5, 15); // returns false
MyCalendar.book(5, 10); // returns true
MyCalendar.book(25, 55); // returns true
解释：
前两个日程安排可以添加至日历中。 第三个日程安排会导致双重预订，但可以添加至日历中。
第四个日程安排活动（5,15）不能添加至日历中，因为它会导致三重预订。
第五个日程安排（5,10）可以添加至日历中，因为它未使用已经双重预订的时间10。
第六个日程安排（25,55）可以添加至日历中，因为时间 [25,40] 将和第三个日程安排双重预订；
时间 [40,50] 将单独预订，时间 [50,55）将和第二个日程安排双重预订。

提示：
	每个测试用例，调用 MyCalendar.book 函数最多不超过 1000 次。
	调用函数 MyCalendar.book(start, end)时， start 和 end 的取值范围为 [0, 10^9]。
*/

// https://leetcode.com/problems/my-calendar-ii/discuss/109522/Simplified-winner's-solution
// 抄的
class MyCalendarTwo
{
	std::map<int, int> m;

public:
	MyCalendarTwo() {}

	bool book(int start, int end)
	{
		int b = 0;
		m[start] += 1;
		m[end] -= 1;
		for (auto const& p : m)
		{
			b += p.second;
			// 看 start 前面的起点是不是比终点多了 3
			if (b == 3)
			{
				m[start] -= 1;
				m[end] += 1;
				return false;
			}
		}
		return true;
	}
};


/* 732. 我的日程安排表 III

实现一个 MyCalendar 类来存放你的日程安排，你可以一直添加新的日程安排。

MyCalendar 有一个 book(int start, int end)方法，它意味着在start到end时间内增加一个日程安排。
注意，这里的时间是半开区间，即 [start, end), 实数 x 的范围为，start <= x < end。

当 K 个日程安排有一些时间上的交叉时（例如K个日程安排都在同一时间内），就会产生 K 次预订。

每次调用 MyCalendar.book方法时，返回一个整数 K，表示最大的 K 次预订。

请按照以下步骤调用MyCalendar 类:
	MyCalendar cal = new MyCalendar();
	MyCalendar.book(start, end);

示例 1:
MyCalendarThree();
MyCalendarThree.book(10, 20); // returns 1
MyCalendarThree.book(50, 60); // returns 1
MyCalendarThree.book(10, 40); // returns 2
MyCalendarThree.book(5, 15); // returns 3
MyCalendarThree.book(5, 10); // returns 3
MyCalendarThree.book(25, 55); // returns 3
解释:
前两个日程安排可以预订并且不相交，所以最大的K次预订是1。
第三个日程安排[10,40]与第一个日程安排相交，最高的K次预订为2。
其余的日程安排的最高K次预订仅为3。
请注意，最后一次日程安排可能会导致局部最高K次预订为2，但答案仍然是3，原因是从开始到最后，时间[10,20]，[10,40]和[5,15]仍然会导致3次预订。

说明:
	每个测试用例，调用 MyCalendar.book 函数最多不超过 400 次。
	调用函数 MyCalendar.book(start, end)时， start 和 end 的取值范围为 [0, 10^9]。
*/

// 同 MyCalendarTwo
class MyCalendarThree
{
	std::map<int, int> m;

public:
	MyCalendarThree() {}

	int book(int start, int end)
	{
		int a = 0, b = 0;
		m[start] += 1;
		m[end] -= 1;
		for (auto const& p : m)
		{
			b += p.second;
			a = std::max(a, b);
		}
		return a;
	}
};


int main()
{
	char const* delim = "====================";
	MyCalendar m1;
	OutBool(m1.book(10, 20));
	OutBool(m1.book(15, 25));
	OutBool(m1.book(20, 30));
	puts(delim);
	MyCalendarTwo m2;
	OutBool(m2.book(10, 20));
	OutBool(m2.book(50, 60));
	OutBool(m2.book(10, 40));
	OutBool(m2.book(5, 15));
	OutBool(m2.book(5, 10));
	OutBool(m2.book(25, 55));
	puts(delim);
	MyCalendarThree m3;
	OutExpr(m3.book(10, 20), "%d");
	OutExpr(m3.book(50, 60), "%d");
	OutExpr(m3.book(10, 40), "%d");
	OutExpr(m3.book(5, 15), "%d");
	OutExpr(m3.book(5, 10), "%d");
	OutExpr(m3.book(25, 55), "%d");
}
