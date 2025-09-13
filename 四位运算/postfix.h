#pragma once
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
class Post_node
{
public:
	double val;
	Post_node* next;
	Post_node():val(0),next(nullptr){}
	Post_node(const int temp):val(temp),next(nullptr){}
};
class Post_stack
{
public:
	Post_node* top;
	int length;
	Post_stack():top(nullptr),length(0){}
	//向栈内添加元素
	void insert_stack(double data);
	//删除栈顶元素
	double delete_stack();
	//得到栈顶元素
	double get_top();
	//判断空栈
	bool is_empty();
	//输出后缀表达式结果
	double get_result(const string& temp);
};
void Post_stack::insert_stack(double data)
{
	Post_node* temp = new Post_node(data);
	temp->next = top;
	top = temp;
	this->length++;
}
bool Post_stack::is_empty()
{
	if (this->length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
double Post_stack::delete_stack()
{
	if (this->is_empty())
	{
		return '\0';
	}
	char data;
	Post_node* temp = this->top;
	data = temp->val;
	top = top->next;
	delete temp;
	this->length--;
	return data;
}
double Post_stack::get_top()
{
	if (this->is_empty())
	{
		return '\0';
	}
	return this->top->val;
}
double Post_stack::get_result(const string& temp)
{
	string str;//临时变量，用来存放多位数字
	for (char c : temp)
	{
		//如果是数字就存放在临时变量里
		if (isdigit(c))
		{
			str += c;
		}
		//c不是数字,是一个运算符或者是空格，先看临时变量是否为空，为空先把先前的数字压入栈中，注意要转换为double
		//注意是空格和是运算符的后续操作完全不同，一个是将多位数压入，一个是将栈中两个操作数弹出
		else
		{
			if (c==' ')
			{
				if (!str.empty())
				{
					//atof:是一个函数，参数为const char*，为c风格字符串，能够将其转换为对应的double型
					double num = atof(str.c_str());
					this->insert_stack(num);
					str.clear(); // 清空临时字符串，准备下一个数字
				}
			}
			else
			{
				//避免数字后紧跟着的是运算符而不是空格
				if (!str.empty())
				{
					//atof:是一个函数，参数为const char*，为c风格字符串，能够将其转换为对应的double型
					double num = atof(str.c_str());
					this->insert_stack(num);
					str.clear(); // 清空临时字符串，准备下一个数字
				}
				//弹出两个操作数，要先判断有没有两个
				if (this->length < 2)
				{
					cout << "后缀表达式错误" << endl;
					return 0;
				}
				//注意弹出顺序，后弹出的为第一个操作数
				double num1, num2;
				num2 = this->delete_stack();
				num1 = this->delete_stack();
				double result;
				switch (c)
				{
				case '+':
				{
					result = num1 + num2;
					break;
				}
				case '-':
				{
					result = num1 - num2;
					break;
				}
				case '*':
				{
					result = num1 * num2;
					break;
				}
				case '/':
				{
					if (num2 == 0)
					{
						cout << "除数不为0" << endl;
						return 0;
					}
					result = num1 / num2;
					break;
				}
				default:
				{
					cout << "后缀表达式无法识别的运算符" << endl;
					return 0;
					break;
				}
				}
				this->insert_stack(result);
			}
		}
	}
	//处理最后一个遗漏的多位数，因为如果他后面没有空格或者是操作数，就不会压入栈中
	if (!str.empty())
	{
		double num = atof(str.c_str());
		this->insert_stack(num);
	}
	return this->delete_stack();
}