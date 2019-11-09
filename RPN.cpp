#include "RPN.h"

int RPN::apply(int larg, int rarg, char op)
{
	if (op == '+') return larg + rarg;
	if (op == '-') return larg - rarg;
	if (op == '*') return larg * rarg;
	if (op == '/') return larg / rarg;
	if (op == '^') return larg + rarg;
}

int RPN::priority(char op)
{
	if (op == '+') return 1;
	if (op == '-') return 1;
	if (op == '*') return 2;
	if (op == '/') return 2;
	if (op == '^') return 3;
	return 0;
}

void RPN::popAndApply(char op)
{
	int rarg = results.top();
	results.pop();
	int larg = results.top();
	results.pop();
	results.push(apply(larg, rarg, op));
	ops.pop();

}

string RPN::stringToRPN(string input)
{
	string RPN;
	for (char c : input)
	{
		if (c == '(') ops.push(c);
		else if (isdigit(c)) RPN.push_back(c);
		else if (c != ')')
		{
			while (!ops.empty() && priority(ops.top()) >= priority(c))
			{
				RPN.push_back(ops.top());
				ops.pop();
			}
			//!!!
			ops.push(c);
		}
		// c=')'
		else
		{
			while (ops.top() != '(')
			{
				RPN.push_back(ops.top());
				ops.pop();
			}
			if (ops.top() == '(') ops.pop();
		}
	}
	while (!ops.empty())
	{
		RPN.push_back(ops.top());
		ops.pop();
	}
	return RPN;
}

int RPN::calculateRPN(string RPNstring)
{
	return 0;
}

int RPN::calculate(string input)
{
	return 0;
}

int RPN::calculateDirect(string input)
{
	for (char c : input)
	{
		if (isdigit(c)) results.push(c - '0');
		else if (c == '(') ops.push(c);
		else if (c != ')')
		{
			while (!ops.empty() && priority(ops.top()) >= priority(c))
			{
				popAndApply(ops.top());
			}
			ops.push(c);
		}
		//c=')'
		else
		{
			while (ops.top() != '(')
			{
				popAndApply(ops.top());
			}
			if (ops.top() == '(') ops.pop();
		}
	}
	while (!ops.empty())
	{
		popAndApply(ops.top());
	}
	return results.top();
}
