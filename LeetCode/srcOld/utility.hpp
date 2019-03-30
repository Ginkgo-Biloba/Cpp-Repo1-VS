#ifndef LeetCode_Utility_Hpp
#define LeetCode_Utility_Hpp

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <queue>
using std::vector;
using std::string;
using std::pair;
using std::unordered_set; using std::unordered_map;


static char const* boolstr[2] = { "false", "true" };

#define OutExpr(expr, fmt) \
	printf(#expr " = " fmt "\n", (expr))
	

void output(vector<int> const& vec, char const* info = nullptr)
{
	if (info)
		printf("----- %s -----\n", info);
	for (int i : vec)
		printf("%d, ", i);
	printf("\n");
}

void output(vector<vector<int>> const& mat, char const* info = nullptr)
{
	if (info)
		printf("===== %s =====\n", info);
	for (vector<int> const& v : mat)
		output(v);
}

void output(vector<string> const& vec, \
	char const* delimit = "\n", char const* info = nullptr)
{
	if (info)
		printf("----- %s -----\n", info);
	for (string const& s : vec)
		printf("%s%s", s.c_str(), delimit);
	printf("\n");
}


#endif
