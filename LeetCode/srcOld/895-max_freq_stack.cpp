#include <functional>
#include <algorithm>
#include <vector>
#include <map>

class FreqStack
{
public:

	FreqStack()
	{
		data.reserve(10000u);
		buffer.reserve(10000u);
	}

	void push(int x)
	{
		data.push_back(x);
		std::map<int, int>::iterator it = freqval.find(x);
		if (it != freqval.end())
			it->second++;
		else
			freqval.emplace(x, 1);
	}

	int pop()
	{
		std::vector<int>::iterator ritB = data.end(), ritE = data.begin();
		std::map<int, int>::iterator it = freqval.begin(), itend = freqval.end();
		int x = it->first, xf = it->second;
		if (xf == 1)
		{
			freqval.erase(it);
			for (; ritB != ritE; --ritB)
			{
				std::vector<int>::iterator fit = std::find(buffer.begin(), buffer.end(), x);
				data.erase(fit);
			}
			return x;
		}

		buffer.clear(); buffer.push_back(x);
		for (++it; it != itend; ++it)
		{
			if (it->second == xf)
				buffer.push_back(it->first);
		}
		while(ritB != ritE)
		{
			x = *(--ritB);
			std::vector<int>::iterator fit = std::find(data.begin(), data.end(), x);
			if (fit != buffer.end())
			{
				data.erase(ritB);
				break;
			}
		}
		return x;
	}

private:
	std::vector<int> data;
	std::map<int, int, std::greater<int>> freqval;
	std::vector<int> buffer;
};

/**
* Your FreqStack object will be instantiated and called as such:
* FreqStack obj = new FreqStack();
* obj.push(x);
* int param_2 = obj.pop();
*/

int main()
{
	FreqStack fs;
	fs.push(5); fs.push(7); fs.push(5); fs.push(7); fs.push(4); fs.push(5);
	int val = fs.pop(); val = fs.pop(); val = fs.pop(); val = fs.pop();
	return 0;
}








