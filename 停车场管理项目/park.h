#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#define Max_size 2
using namespace std;
class Car
{
public:
	string tag;
	double e_time;
	Car(){}
	Car(string str,double time):tag(str),e_time(time){}
	Car(const Car&temp):tag(temp.tag),e_time(temp.e_time){}
};
class C_stc
{
public:
	Car seat[Max_size];
	int i;
	void push(Car e_car);
	Car pop();
	bool is_full();
	C_stc():i(-1){}
	bool is_empty();
	Car top();
};
class Park
{
public:
	C_stc c_stc;
	queue<Car> c_que;
	bool quick(Car &q_car);
	void enter(Car e_car);
	void show();
};
istream& operator>>(istream& is, Car &c)
{
	is >> c.tag >> c.e_time;
	return is;
}
bool operator==(const Car& c1, const Car& c2)
{
	if (c1.tag == c2.tag)
	{
		return true;
	}
	return false;
}
void Park::enter(Car e_car)
{
	if (!c_stc.is_full())
	{
		cout << "ͣ���ɹ�!!!!" << endl;
		c_stc.push(e_car);
	}
	else
	{
		cout << "ͣ�������ˣ���ʱͣ�ں����ڣ�����" << endl;
		this->c_que.push(e_car);
	}
}
bool Park::quick(Car &q_car)
{
	if (this->c_stc.is_empty())
	{
		cout << "ͣ����û�г������޷�ʻ��ͣ����!!!" << endl;
		return false;
	}
	else
	{
		C_stc temp = this->c_stc;
		while (!(this->c_stc.is_empty()))
		{
			if (this->c_stc.top() == q_car)
			{
				break;
			}
			temp.push(this->c_stc.top());
			c_stc.pop();
		}
		if (c_stc.is_empty())
		{
			cout << "δ�ҵ�Ŀ�공��" << endl;
			return false;
		}
		else
		{
			q_car = c_stc.top();
			while (!temp.is_empty())
			{
				this->c_stc.push(temp.top());
				temp.pop();
			}
			cout << "�ҵ����ƺ�Ϊ" << q_car.tag << "�ĳ�������ʻ��ͣ����" << endl;
			if (!this->c_que.empty() && !this->c_stc.is_full())
			{
				this->c_stc.push(this->c_que.front());
				cout << "λ�ں򳵳��ڵ�" << c_que.front().tag << "ʻ��ͣ����" << endl;
				this->c_que.pop();
			}
		}
	}
	return true;
}
void Park::show()
{
	if (this->c_stc.is_empty())
	{
		cout << "ͣ����Ϊ��" << endl;
	}
	else
	{
		cout << "����" << "         " << "����ʱ��" << endl;
		C_stc temp = this->c_stc;
		while (!temp.is_empty())
		{
			Car c_car = temp.top();
			cout << c_car.tag << "       " << c_car.e_time << endl;
			temp.pop();
		}
	}
}
void C_stc::push(Car e_car)
{
	if (!this->is_full())
	{
		this->i++;
		this->seat[this->i] = e_car;
	}
}
bool C_stc::is_empty()
{
	return (this->i == -1) ? true : false;
}
bool C_stc::is_full()
{
	return (this->i == Max_size - 1) ? true : false;
}
Car C_stc::top()
{
	if (this->is_empty())
	{
		throw std::runtime_error("ͣ����Ϊ��,�޷����top");
	}
	return this->seat[this->i];
}
Car C_stc::pop()
{
	if (this->is_empty())
	{
		throw std::runtime_error("ͣ����Ϊ��,�޷����top");
	}
	Car temp = this->seat[this->i];
	this->i--;
	return temp;
}