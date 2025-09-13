#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
//为不同字符定义比较级
int get_priority(char c)
{
	switch (c)
	{
	case '(':
	case ')':
	{
		return 0;
	}
	case '+':
	case '-':
	{
		return 1;
	}
	case '*':
	case '/':
	{
		return 2;
	}
	default:
	{
		return -1;
	}
	}
	return -1;
}
class Infix_Node
{
public:
	char val;
	Infix_Node* next;
	Infix_Node(char temp) :val(temp),next(nullptr){}
	Infix_Node():val(0),next(nullptr){}
};
class Switch_Infix
{
public:
	Infix_Node* top;
	int length;
	//构造函数
	Switch_Infix():top(nullptr),length(0){}
	//向栈内添加元素
	void insert_stack(char data);
	//删除栈顶元素
	char delete_stack();
	//将中缀表达式转换为后缀表达式
	string switch_infix(const string temp);
	//得到栈顶元素
	char get_top();
    //判断空栈
    bool is_empty();
	//将后缀表达式输出结果
};
bool Switch_Infix::is_empty()
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
void Switch_Infix::insert_stack(char data)
{
	Infix_Node* temp = new Infix_Node(data);
	temp->next = top;
	top = temp;
	this->length++;
}
char Switch_Infix::delete_stack()
{
    if (this->is_empty())
    {
        return '\0';
    }
	char data;
	Infix_Node* temp = this->top;
	data= temp->val;
	top = top->next;
	delete temp;
	this->length--;
	return data;
}
char Switch_Infix::get_top()
{
    if (this->is_empty())
    {
        return '\0';
    }
	return this->top->val;
}
string Switch_Infix::switch_infix(const string temp)
{
	int n = temp.size();
	int i = 0;
	string result;
	for (i = 0;i < n;i++)
	{
        //处理空格
        if (temp[i] == ' ')
        {
            continue;
        }
        //处理数字，使其能够用与多位数的运算，而不是只能单个数字，也就是个位数的运算
        //后续区分不同的操作，和是不是多位数依靠的空格，简称分隔符
		if (isdigit(temp[i]))
		{
            while (i < n && isdigit(temp[i]))
            {
                //将连续的数字放进后缀表达式内，不添加分隔符，表示后续还有数字的话，他们是一个数字
                result.push_back(temp[i]);
                i++;
            }
            //读到分隔符或者是字符停止，在后缀表达式加入分隔符，表示一个数字读取完成
            result.push_back(' ');
            //因为此时的temp[i]表示的是字符，而后续有i++会跳过这个字符，所以先回退一个，后续i++就有返回了
            i--;
		}
		//处理字符
		else
		{
			if (this->length == 0 || temp[i] == '(')
			{
				this->insert_stack(temp[i]);
			}
			else
			{
				char c;
				if (temp[i] == ')')
				{
					while (this->top->val != '(')
					{
						c = this->delete_stack();
						result.push_back(c);
                        //在后缀表达式放入一个运算符后，紧跟着就放入一个分隔符，用来区分不同的运算符号
                        result.push_back(' ');
					}
					//删除残余的（
					this->delete_stack();
				}
				//处理运算符
				else
				{
					while (this->top != nullptr)
					{
						if (get_priority(temp[i]) <= get_priority(this->get_top()))
						{
							c = this->delete_stack();
							result.push_back(c);
                            //同样加入分隔符
                            result.push_back(' ');
						}
						else
						{
							break;
						}
					}
					this->insert_stack(temp[i]);
				}
			}
		}
	}
	while (top != nullptr)
	{
		char a;
		a = this->delete_stack();
		result.push_back(a);
        result.push_back(' ');
	}
	//删除最后多余的一个空格
	if (!result.empty())
	{
		result.pop_back();
	}
	return result;
}