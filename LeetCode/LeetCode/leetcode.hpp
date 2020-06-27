#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using std::array;
using std::deque;
using std::list;
using std::map;
using std::max;
using std::min;
using std::pair;
using std::priority_queue;
using std::set;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

char const* boolstr[2] = { "false", "true" };

#define OutExpr(expr, fmt) \
	printf(#expr " = " fmt "\n", expr)

#define OutBool(expr) \
	printf(#expr " = %s\n", boolstr[!!(expr)])

#define OutString(expr) \
	printf(#expr " = %s\n", (expr).c_str())

void output(vector<int> const& vec, char const* info = nullptr)
{
	if (info)
		printf("----- %s -----\n", info);
	if (vec.empty())
		puts("<empty>");
	else
	{
		for (int i : vec)
			printf("%d, ", i);
		printf("\n");
	}
	fflush(NULL);
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
	{
		if (s.empty())
			printf("<empty>%s", delimit);
		else
			printf("%s%s", s.c_str(), delimit);
	}
	printf("\n");
	fflush(NULL);
}
