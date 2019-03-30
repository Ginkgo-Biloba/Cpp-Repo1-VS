#include "../srcOld/utility.hpp"


int64_t getNext(int64_t cur)
{
	int64_t next = 0;
	for (; cur; cur /= 10)
	{
		int64_t b = cur % 10;
		next += b * b;
	}
	return next;
}


bool isHappy(int n)
{
	int64_t num = n;
	unordered_set<int64_t> traval;
	traval.insert(num);

	while (num)
	{
		int64_t next = getNext(num);
		if (next == 1)
			return true;
		unordered_set<int64_t>::iterator it = traval.find(next);
		if (it != traval.end())
			return false;

		traval.insert(next);
		num = next;
	}
	return false; // 只是为了防止警告
}


/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	bool ans = isHappy(19);
	printf("%1s: %s\n",
		"isHappy", ans ? "true" : "false");
}
