#include "../srcOld/utility.hpp"


string fractionToDecimal(int iA, int iB)
{
	typedef unsigned long long ullong;
	bool neg = (iA > 0 && iB < 0) || (iA < 0 && iB > 0);
	ullong A = std::abs(static_cast<long long>(iA));
	ullong B = std::abs(static_cast<long long>(iB));
	// 计算 A ÷ B = C...D
	// C++ 商向 0 取整，结果是余数和被除数符号一致
	ullong C = A / B;
	ullong D = A - C * B;

	char buf[16];
	if (neg)
		sprintf(buf, "-%llu", C);
	else
		sprintf(buf, "%llu", C);
	string frac(buf);
	if (D == 0)
		return frac;

	frac.push_back('.');
	map<ullong, int> residual;
	int bitstart, bitcur = 0;
	for (; D != 0; ++bitcur)
	{
		D *= 10;
		ullong q = D / B;
		frac.push_back(static_cast<char>(q + '0'));
		map<ullong, int>::iterator iter = residual.find(D);
		if (iter == residual.end())
			residual.emplace(D, bitcur);
		else
		{
			bitstart = iter->second;
			break;
		}
		D -= q * B;
	}

	if (D != 0) // 循环小数
	{
		// 直接覆盖掉多 push_back 进去那个商
		size_t len = frac.size() - 1u;
		for (int repbit = bitcur - bitstart; repbit--; --len)
			frac[len] = frac[len - 1u];
		frac[len] = '(';
		frac.push_back(')');
	}

	return frac;
}



/* 这句注释只是为了防止纯 ANSCI 字符时 VS 改变文件编码 */
int main()
{
	int A, B;
	printf("input two number, separated with space (such as \"1 7\")\n");
	printf("input non-number to exit (such as \"a b\")\n");
	printf("numbers should be in [%d, %d]\n\n", INT_MIN, INT_MAX);
	while (scanf("%d %d", &A, &B) == 2)
	{
		string ans = fractionToDecimal(A, B);
		printf("%1s: %d / %d = %s\n",
			"fractionToDecimal", A, B, ans.c_str());
	}
}
