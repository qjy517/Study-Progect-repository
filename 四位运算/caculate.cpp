#include <iostream>
#include "infix.h"
#include "postfix.h"
#include <string>
using namespace std;
void test01()
{
	Switch_Infix infix;
	string str;
	cout << "请输入表达式:" << endl;
	getline(cin, str);
	str = infix.switch_infix(str);
	cout <<"转换为后缀表达式为:"<< str << endl;
	Post_stack postfix;
	double result=postfix.get_result(str);
	cout << "运算结果为:"<<result << endl;
}
int main()
{
	test01();
	return 0;
}