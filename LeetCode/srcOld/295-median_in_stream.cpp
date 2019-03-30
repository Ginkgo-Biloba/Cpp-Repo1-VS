#include "../srcOld/utility.hpp"

// 抄的
class MedianFinder
{
	// 顶部是队列中最大元素，存储的加进来的较小的数据
	std::priority_queue<int> qMax;
	std::priority_queue<int, vector<int>, std::greater<int>> qMin;
public:
	MedianFinder()
	{}

	void addNum(int num)
	{
		if (qMax.empty() || num <= qMax.top())
			qMax.push(num);
		else
			qMin.push(num);

		if (qMin.size() < qMax.size() - 1u)
		{
			qMin.push(qMax.top());
			qMax.pop();
		}
		else if (qMin.size() > qMax.size())
		{
			qMax.push(qMin.top());
			qMin.pop();
		}
	}

	double findMedian()
	{
		double val = qMax.top();
		if (qMax.size() == qMin.size())
			val = 0.5 * (val + qMin.top());
		return val;
	}
};

int main()
{
	vector<int> nums = { 1, 2, 3, 4, 5, 6 };
	MedianFinder med;
	for (int i : nums)
	{
		med.addNum(i);
		printf("%.2f, ", med.findMedian());
	}
	printf("\n");
}
