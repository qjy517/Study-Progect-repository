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
	//��ջ�����Ԫ��
	void insert_stack(double data);
	//ɾ��ջ��Ԫ��
	double delete_stack();
	//�õ�ջ��Ԫ��
	double get_top();
	//�жϿ�ջ
	bool is_empty();
	//�����׺���ʽ���
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
	string str;//��ʱ������������Ŷ�λ����
	for (char c : temp)
	{
		//��������־ʹ������ʱ������
		if (isdigit(c))
		{
			str += c;
		}
		//c��������,��һ������������ǿո��ȿ���ʱ�����Ƿ�Ϊ�գ�Ϊ���Ȱ���ǰ������ѹ��ջ�У�ע��Ҫת��Ϊdouble
		//ע���ǿո����������ĺ���������ȫ��ͬ��һ���ǽ���λ��ѹ�룬һ���ǽ�ջ����������������
		else
		{
			if (c==' ')
			{
				if (!str.empty())
				{
					//atof:��һ������������Ϊconst char*��Ϊc����ַ������ܹ�����ת��Ϊ��Ӧ��double��
					double num = atof(str.c_str());
					this->insert_stack(num);
					str.clear(); // �����ʱ�ַ�����׼����һ������
				}
			}
			else
			{
				//�������ֺ�����ŵ�������������ǿո�
				if (!str.empty())
				{
					//atof:��һ������������Ϊconst char*��Ϊc����ַ������ܹ�����ת��Ϊ��Ӧ��double��
					double num = atof(str.c_str());
					this->insert_stack(num);
					str.clear(); // �����ʱ�ַ�����׼����һ������
				}
				//����������������Ҫ���ж���û������
				if (this->length < 2)
				{
					cout << "��׺���ʽ����" << endl;
					return 0;
				}
				//ע�ⵯ��˳�򣬺󵯳���Ϊ��һ��������
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
						cout << "������Ϊ0" << endl;
						return 0;
					}
					result = num1 / num2;
					break;
				}
				default:
				{
					cout << "��׺���ʽ�޷�ʶ��������" << endl;
					return 0;
					break;
				}
				}
				this->insert_stack(result);
			}
		}
	}
	//�������һ����©�Ķ�λ������Ϊ���������û�пո�����ǲ��������Ͳ���ѹ��ջ��
	if (!str.empty())
	{
		double num = atof(str.c_str());
		this->insert_stack(num);
	}
	return this->delete_stack();
}