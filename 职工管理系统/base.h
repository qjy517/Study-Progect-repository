#pragma once
#include <iostream>
#include <string>
using namespace std;
class Base
{
public:
	string m_id;
	string m_name;
	string m_apartment;
	virtual string get_duty()
	{
		return "�麯��";
	}
};
class Employ :public Base
{
public:
	virtual string get_duty()
	{
		return "�ҵ�ְ����Ŭ������";
	}
	//���캯��
	Employ(const string& id, const string& name, const string& apartment);
	//�������캯��
	Employ(const Base& temp);
};
class Manager :public Base
{
public:
	virtual string get_duty()
	{
		return "�ҵ�ְ���ǹ����Ա��";
	}
	Manager(const string& id, const string& name, const string& apartment);
	//�������캯��
	Manager(const Base& temp);
};
class Boss :public Base
{
public:
	virtual string get_duty()
	{
		return "�ҵ�ְ���ǹ���ù�˾";
	}
	Boss(const string& id, const string& name, const string& apartment);
	//�������캯��
	Boss(const Base& temp);
};