#include <cstdio>
#include <vector>
#include <map>

struct Point
{
	int x, y;
	Point(int x_ = 0, int y_ = 0)
		: x(x_), y(y_) {}
};

struct lessSlope
{
	bool operator()(Point const& a, Point const& b)
	{
		int64_t diff = (int64_t)(a.x) * b.y - (int64_t)(a.y) * b.x;
		return ((int64_t)(a.y) * b.y > 0) ? (diff > 0) : (diff < 0);
	}
};
// 你好
int maxPoints(std::vector<Point>& points)
{
	int ans = 0;
	for (Point const& ref : points)
	{
		std::map<Point, int, lessSlope> count;
		int dup = 0;
		for (Point const& cur : points)
		{
			int curMax = 0;
			if ((ref.x == cur.x) && (ref.y == cur.y))
				++dup;
			else
				curMax = (++count[Point(ref.x - cur.x, ref.y - cur.y)]);
			curMax += dup;
			if (ans < curMax) ans = curMax;
		}
	}
	return ans;
}

int main()
{
	std::vector<Point> points = { { 1, 1 }, { 3, 2 }, { 5, 3 }, { 4, 1 }, { 2, 3 }, { 1, 4 } };
	int ans = maxPoints(points);
	printf("ans = %d\n", ans);
	return 0;
}

