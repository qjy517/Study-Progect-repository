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
		return "虚函数";
	}
};
class Employ :public Base
{
public:
	virtual string get_duty()
	{
		return "我的职责是努力工作";
	}
	//构造函数
	Employ(const string& id, const string& name, const string& apartment);
	//拷贝构造函数
	Employ(const Base& temp);
};
class Manager :public Base
{
public:
	virtual string get_duty()
	{
		return "我的职责是管理好员工";
	}
	Manager(const string& id, const string& name, const string& apartment);
	//拷贝构造函数
	Manager(const Base& temp);
};
class Boss :public Base
{
public:
	virtual string get_duty()
	{
		return "我的职责是管理好公司";
	}
	Boss(const string& id, const string& name, const string& apartment);
	//拷贝构造函数
	Boss(const Base& temp);
};