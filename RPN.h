#ifndef __RPN_H
#define __RPN_H
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class RPN
{
	stack<char> ops;
	stack<int> results;

	int apply(int larg, int rarg, char op);
	int priority(char op);
	void popAndApply(char op);

public:
	string stringToRPN(string input);
	int calculateRPN(string RPNstring);
	int calculate(string input);
	int calculateDirect(string input);
};
#endif