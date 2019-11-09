#include "RPN.h"

int main()
{
	string a = "(1+2)*(3-4/5)";
	cout << RPN().stringToRPN(a) << endl;
	cout << RPN().calculateDirect(a) << endl;
	system("pause");
	return 0;
}
