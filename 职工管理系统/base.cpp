#include "base.h"
#include <iostream>
#include <string>
using namespace std;
Employ::Employ(const string& id, const string& name,const string &apartment)
{
	this->m_id = id;
	this->m_name = name;
	this-> m_apartment = apartment;
}
Manager::Manager(const string& id, const string& name, const string& apartment)
{
	this->m_id = id;
	this->m_name = name;
	this->m_apartment =apartment;
}
Boss::Boss(const string& id, const string& name, const string& apartment)
{
	this->m_id = id;
	this->m_name = name;
	this->m_apartment = apartment;
}
Employ::Employ(const Base& temp)
{
	this->m_id = temp.m_id;
	this->m_name = temp.m_name;
	this->m_apartment = temp.m_apartment;
}
Manager::Manager(const Base& temp)
{
	this->m_id = temp.m_id;
	this->m_name = temp.m_name;
	this->m_apartment = temp.m_apartment;
}
Boss::Boss(const Base& temp)
{
	this->m_id = temp.m_id;
	this->m_name = temp.m_name;
	this->m_apartment = temp.m_apartment;
}