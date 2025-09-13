#include <iostream>
#include "person.h"
#include "system.h"
#include <limits>
#include <string>
#include <vector>
using namespace std;
//重载>>
istream& operator>>(istream& is, Person& p)
{
    cout << "输入姓名:" << endl;
    is >> p.m_name;
    cout << "输入性别:" << endl;
    is >> p.m_sex;
    cout << "输入电话:" << endl;
    is >> p.m_phone;
    cout << "输入家庭地址:" << endl;
    is >> p.m_adress;
    return is;
}
//重载<<
ostream& operator<<(ostream& os, const Person& p)
{
    cout << p.m_name << " " << p.m_sex << " " << p.m_phone << " " << p.m_adress;
    return os;
}
//重载=,只能在类内定义
//菜单显示
void System::show_meanu()
{
    cout << "********************" << endl;
    cout << "***0.退出系统********" << endl;
    cout << "***1.添加联系人******" << endl;
    cout << "***2.删除联系人******" << endl;
    cout << "***3.显示联系人******" << endl;
    cout << "***4.查找联系人******" << endl;
    cout << "***5.修改联系人******" << endl;
    cout << "***6.清空联系人******" << endl;
    cout << "********************" << endl;
    cout << "********************" << endl;
    system("pause");
}
//添加人员
void System::add_person()
{
    int count;
    cout << "输入添加的人数:" << endl;
    cin >> count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除换行符
    Person temp;
    for (int i = 1;i <= count;i++)
    {
        //重载<<和>>运算符
        cin >> temp;
        v.push_back(temp);
        cout << "添加成功" << endl;
    }
    system("pause");
    system("cls");
    
}
//显示所有人员
void System::look_person()
{
    for (auto i : this->v)
    {
        cout << i << endl;
    }
    system("pause");
    system("cls");
}
//返回要找的人的迭代器
vector<Person>::iterator System::search_person(const string &name)
{
    auto i = this->v.begin();
    while (i != this->v.end())
    {
        if ((*i).m_name == name)
        {
            return i;
        }
    }  
    if (i == this->v.end())
    {
        return v.end();
    }
}
//删除联系人
void System::delete_person()
{
    string name;
    cout << "输出删除人员名字:" << endl;
    cin >> name;
    auto i = this->search_person(name);
    i = v.erase(i);
    cout << "删除成功" << endl;
    system("pause");
    system("cls");
}
//查找人员
void System::find_person()
{
    string name;
    cout << "输入查找人员名字:" << endl;
    cin >> name;
    auto i = this->search_person(name);
    if (i == v.end())
    {
        cout << "未找到目标人员" << endl;
    }
    else
    {
        cout << *i << endl;
    }
    system("pause");
    system("cls");
}
//修改人员
void System::reverse_person()
{
    string name;
    cout << "输入修改人员的名字" << endl;
    cin >> name;
    auto i = this->search_person(name);
    if (i == v.end())
    {
        cout << "未找到人员" << endl;
    }
    else
    {
        cout << "输入新的人员信息" << endl;
        Person temp;
        cin >> temp;
        //重载=操作
        *i = temp;
        cout << "修改成功" << endl;
    }
    system("pause");
    system("cls");
}
void System::clear_person()
{
    int select;
    cout << "确认删除:\n1.Yes\n2.No" << endl;
    cin >> select;
    if (select == 1)
    {
        this->v.clear();
    }
    else
    {
        return;
    }
}