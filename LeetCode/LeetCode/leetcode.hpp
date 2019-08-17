#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using std::pair;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

char const* boolstr[2] = { "false", "true" };

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

void output(vector<string> const& vec,
	char const* delimit = "\n", char const* info = nullptr)
{
	if (info)
		printf("----- %s -----\n", info);
	for (string const& s : vec)
		printf("%s%s", s.c_str(), delimit);
	printf("\n");
}
