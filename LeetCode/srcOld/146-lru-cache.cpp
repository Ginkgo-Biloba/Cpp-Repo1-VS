#include <cstdio>
#include <unordered_map>
#include <list>
#include <utility>

class LRUCache
{
public:
	typedef std::pair<int, int> pint;
	typedef std::list<pint>::iterator ListIter;
	typedef std::unordered_map<int, ListIter> MapType;

	LRUCache(int c_)
		: capacity(c_)
	{}

	int get(int key)
	{
		MapType::iterator miter = klMap.find(key);
		if (miter == klMap.end())
			return -1;
		else
		{
			int value = (miter->second)->first;
			values.emplace_front(value, key);
			values.erase(miter->second);
			klMap[key] = values.begin();
			return value;
		}
	}

	void put(int key, int value)
	{
		MapType::iterator miter = klMap.find(key);
		if (miter != klMap.end())
		{
			values.erase(miter->second);
		}
		else if (values.size() == capacity)
		{
			klMap.erase(values.back().second);
			values.pop_back();
		}

		values.emplace_front(value, key);
		klMap[key] = values.begin();
	}

private:
	MapType klMap;
	std::list<pint> values;
	size_t const capacity;
};


int main()
{
	LRUCache cache(2);
	cache.put(2, 1);
	cache.put(1, 1);
	cache.get(2);
	cache.put(4, 1);
	cache.get(1);
	cache.get(2);

	return 0;
}
