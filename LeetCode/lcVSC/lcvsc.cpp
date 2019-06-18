#include "../srcOld/utility.hpp"


int sum(int a, int b)
{
	while (b != 0)
	{
		int noCarry = a ^ b;
		int carry = (a & b) << 1;
		a = noCarry;
		b = carry;
	}
	return a;
}

int main(int argc, char **argv)
{
	int t = sum(1, -2);
	if (argc >= 3)
		t = sum(atoi(argv[1]), atoi(argv[2]));
	printf("sum = %d\n", t);
}
