#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
//Ϊ��ͬ�ַ�����Ƚϼ�
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
	//���캯��
	Switch_Infix():top(nullptr),length(0){}
	//��ջ�����Ԫ��
	void insert_stack(char data);
	//ɾ��ջ��Ԫ��
	char delete_stack();
	//����׺���ʽת��Ϊ��׺���ʽ
	string switch_infix(const string temp);
	//�õ�ջ��Ԫ��
	char get_top();
    //�жϿ�ջ
    bool is_empty();
	//����׺���ʽ������
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
        //����ո�
        if (temp[i] == ' ')
        {
            continue;
        }
        //�������֣�ʹ���ܹ������λ�������㣬������ֻ�ܵ������֣�Ҳ���Ǹ�λ��������
        //�������ֲ�ͬ�Ĳ��������ǲ��Ƕ�λ�������Ŀո񣬼�Ʒָ���
		if (isdigit(temp[i]))
		{
            while (i < n && isdigit(temp[i]))
            {
                //�����������ַŽ���׺���ʽ�ڣ�����ӷָ�������ʾ�����������ֵĻ���������һ������
                result.push_back(temp[i]);
                i++;
            }
            //�����ָ����������ַ�ֹͣ���ں�׺���ʽ����ָ�������ʾһ�����ֶ�ȡ���
            result.push_back(' ');
            //��Ϊ��ʱ��temp[i]��ʾ�����ַ�����������i++����������ַ��������Ȼ���һ��������i++���з�����
            i--;
		}
		//�����ַ�
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
                        //�ں�׺���ʽ����һ��������󣬽����žͷ���һ���ָ������������ֲ�ͬ���������
                        result.push_back(' ');
					}
					//ɾ������ģ�
					this->delete_stack();
				}
				//���������
				else
				{
					while (this->top != nullptr)
					{
						if (get_priority(temp[i]) <= get_priority(this->get_top()))
						{
							c = this->delete_stack();
							result.push_back(c);
                            //ͬ������ָ���
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
	//ɾ���������һ���ո�
	if (!result.empty())
	{
		result.pop_back();
	}
	return result;
}