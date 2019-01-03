#pragma warning(disable: 4996)
#include "../src/utility.hpp"

vector<string> restoreIpAddresses(string const& S)
{
	int const len = static_cast<int>(S.length());
	int const iplen = len + 3;
	vector<string> ans;
	char val[4] = { 0, 0, 0, 0 };
	char ip[16];
	if (len < 4) return ans;

	for (int a = 1; a <= 3; ++a)
		for (int b = 1; b <= 3; ++b)
			for (int c = 1; c <= 3; ++c)
			{
				int d = len - a - b - c;
				char const* ptr = S.c_str();
				if ((d <= 0) || (d > 3)) continue;

				memcpy(val, ptr, a); val[a] = 0; int A = atoi(val); if (A > 255) continue; ptr += a;
				memcpy(val, ptr, b); val[b] = 0; int B = atoi(val); if (B > 255) continue; ptr += b;
				memcpy(val, ptr, c); val[c] = 0; int C = atoi(val); if (C > 255) continue; ptr += c;
				int D = atoi(ptr); if (D > 255) continue;

				if (sprintf(ip, "%d.%d.%d.%d", A, B, C, D) == iplen)
					ans.push_back(string(ip));
			}
	return ans;
}

int main()
{
	vector<string> ips = restoreIpAddresses(string("010010"));
	output(ips, "\n", "restoreIpAddresses");
}
