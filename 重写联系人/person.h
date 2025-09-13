#pragma once
#include <iostream>
#include <string>
using namespace std;
class Person
{
public:
    string m_name;
    string m_sex;
    string m_phone;
    string m_adress;
    //构造函数
    Person(const string& name, const string& sex, const string& phone, const string& adress) :m_name(name), m_sex(sex), m_phone(phone), m_adress(adress) {}
    //默认构造函数
    Person() = default;
    //重载=
    Person& operator=(const Person& p)
    {
        this->m_name = p.m_name;
        this->m_sex = p.m_sex;
        this->m_phone = p.m_phone;
        this->m_adress = p.m_adress;
        return *this;
    }
};