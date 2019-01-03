#include "utility.hpp"


/** ��Ȼ���Ӽ������š����� */
int calculate(string const& expr)
{
	int sign = 1, sum = 0, num = 0;
	vector<int> stack;

	for (char c : expr)
	{
		if (c == ' ')
			continue;
		else if (c == '(')
		{
			stack.push_back(sum);
			stack.push_back(sign);
			sum = 0;
			sign = 1;
		}
		else if (c == ')')
		{
			sum += sign * num;
			int prevSign = stack.back(); stack.pop_back();
			int prevSum = stack.back(); stack.pop_back();
			sum = prevSum + prevSign * sum;
			num = 0;
		}
		else if (c == '+')
		{
			sum += sign * num;
			sign = 1;
			num = 0;
		}
		else if (c == '-')
		{
			sum += sign * num;
			sign = -1;
			num = 0;
		}
		else
			num = num * 10 + c - '0';
	}
	sum += sign * num;
	return sum;
}


/** ��Ȼ���Ӽ��˳����������š����� */
int calculate2(string& expr)
{
	char sign = '+'; // �൱�� expr ǰ�����и� +
	int sum = 0, num = 0;
	vector<int> stack;
	// �����ж��ǲ������һ������Ϊ����ֻ��һ������
	expr.push_back('+');

	for (char c : expr)
	{
		if (std::isspace(c))
			continue;
		if (std::isdigit(c))
			num = num * 10 + c - '0';
		else
		{
			if (sign == '+')
				stack.push_back(num);
			else if (sign == '-')
				stack.push_back(-num);
			else if (sign == '*')
				stack.back() *= num;
			else
				stack.back() /= num;

			sign = c;
			num = 0;
		}
	}

	while (!stack.empty())
	{
		sum += stack.back();
		stack.pop_back();
	}
	return sum;
}



int main()
{
	string expr = "(1+(4+5+2)-3)+(6+8)";
	int ans = calculate(expr);
	printf("%1s: %s = %d\n",
		"Basic Calculator 1", expr.c_str(), ans);

	string expr2 = "3+5/2";
	int ans2 = calculate2(expr2);
	printf("%1s: %s = %d\n",
		"Basic Calculator 2", expr2.c_str(), ans2);
}
