#include "../srcOld/utility.hpp"

vector<int> plusOne(vector<int>& digits)
{
	std::reverse(digits.begin(), digits.end());
	unsigned const len = static_cast<unsigned>(digits.size());
	int sum = 1;

	for (unsigned l = 0u; l < len; ++l)
	{
		sum += digits[l];
		digits[l] = sum % 10;
		sum /= 10;
		if (sum == 0) break;
	}
	if (sum > 0)
		digits.push_back(sum);

	std::reverse(digits.begin(), digits.end());
	return digits;
}

string addBinary(string a, string b)
{
	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());
	size_t const lenA = a.size(), lenB = b.size();
	size_t const len = std::min(lenA, lenB);
	size_t const lenMax = std::max(lenA, lenB);
	if (lenA < lenB) a.resize(lenB);

	int sum = 0;
	for (size_t l = 0u; l < len; ++l)
	{
		sum += (a[l] - '0') + (b[l] - '0');
		a[l] = (sum & 1) + '0';
		sum >>= 1;
	}
	char const* ptr = (lenA < lenB) ? b.data() : a.data();
	for (size_t l = len; l < lenMax; l++)
	{
		sum += ptr[l] - '0';
		a[l] = (sum & 1) + '0';
		sum >>= 1;
	}
	if (sum)
		a.push_back('1');

	std::reverse(a.begin(), a.end());
	return a;
}


int main()
{
	vector<int> digits = { 9, 9 };
	digits = plusOne(digits);
	output(digits, "plusOne");

	string binSum = addBinary(string("1010"), string("1011"));
	printf("%1s = %s\n", "addBinary", binSum.c_str());
}
