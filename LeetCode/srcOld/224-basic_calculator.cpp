#include "../srcOld/utility.hpp"

class Solution 
{
public:
  /** 自然数加减和括号，抄的 */
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
};