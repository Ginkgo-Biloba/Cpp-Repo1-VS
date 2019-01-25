// 这句注释防止 VS 改变编码
#include "../srcOld/utility.hpp"

int countDigitOne(int n)
{
	int ans = 0;
	while (n)
	{
		ans += 	n / 10 + 1;

	}
	return ans;
}


int main()
{
	int n = 1;
	int ans = countDigitOne(n);
	printf("countDigitOne(%d) = %d\n", n, ans);
}

