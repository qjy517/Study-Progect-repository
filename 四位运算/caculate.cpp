#include <iostream>
#include "infix.h"
#include "postfix.h"
#include <string>
using namespace std;
void test01()
{
	Switch_Infix infix;
	string str;
	cout << "��������ʽ:" << endl;
	getline(cin, str);
	str = infix.switch_infix(str);
	cout <<"ת��Ϊ��׺���ʽΪ:"<< str << endl;
	Post_stack postfix;
	double result=postfix.get_result(str);
	cout << "������Ϊ:"<<result << endl;
}
int main()
{
	test01();
	return 0;
}