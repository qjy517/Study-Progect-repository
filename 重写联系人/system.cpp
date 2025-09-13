#include <iostream>
#include "person.h"
#include "system.h"
#include <limits>
#include <string>
#include <vector>
using namespace std;
//����>>
istream& operator>>(istream& is, Person& p)
{
    cout << "��������:" << endl;
    is >> p.m_name;
    cout << "�����Ա�:" << endl;
    is >> p.m_sex;
    cout << "����绰:" << endl;
    is >> p.m_phone;
    cout << "�����ͥ��ַ:" << endl;
    is >> p.m_adress;
    return is;
}
//����<<
ostream& operator<<(ostream& os, const Person& p)
{
    cout << p.m_name << " " << p.m_sex << " " << p.m_phone << " " << p.m_adress;
    return os;
}
//����=,ֻ�������ڶ���
//�˵���ʾ
void System::show_meanu()
{
    cout << "********************" << endl;
    cout << "***0.�˳�ϵͳ********" << endl;
    cout << "***1.�����ϵ��******" << endl;
    cout << "***2.ɾ����ϵ��******" << endl;
    cout << "***3.��ʾ��ϵ��******" << endl;
    cout << "***4.������ϵ��******" << endl;
    cout << "***5.�޸���ϵ��******" << endl;
    cout << "***6.�����ϵ��******" << endl;
    cout << "********************" << endl;
    cout << "********************" << endl;
    system("pause");
}
//�����Ա
void System::add_person()
{
    int count;
    cout << "������ӵ�����:" << endl;
    cin >> count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������з�
    Person temp;
    for (int i = 1;i <= count;i++)
    {
        //����<<��>>�����
        cin >> temp;
        v.push_back(temp);
        cout << "��ӳɹ�" << endl;
    }
    system("pause");
    system("cls");
    
}
//��ʾ������Ա
void System::look_person()
{
    for (auto i : this->v)
    {
        cout << i << endl;
    }
    system("pause");
    system("cls");
}
//����Ҫ�ҵ��˵ĵ�����
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
//ɾ����ϵ��
void System::delete_person()
{
    string name;
    cout << "���ɾ����Ա����:" << endl;
    cin >> name;
    auto i = this->search_person(name);
    i = v.erase(i);
    cout << "ɾ���ɹ�" << endl;
    system("pause");
    system("cls");
}
//������Ա
void System::find_person()
{
    string name;
    cout << "���������Ա����:" << endl;
    cin >> name;
    auto i = this->search_person(name);
    if (i == v.end())
    {
        cout << "δ�ҵ�Ŀ����Ա" << endl;
    }
    else
    {
        cout << *i << endl;
    }
    system("pause");
    system("cls");
}
//�޸���Ա
void System::reverse_person()
{
    string name;
    cout << "�����޸���Ա������" << endl;
    cin >> name;
    auto i = this->search_person(name);
    if (i == v.end())
    {
        cout << "δ�ҵ���Ա" << endl;
    }
    else
    {
        cout << "�����µ���Ա��Ϣ" << endl;
        Person temp;
        cin >> temp;
        //����=����
        *i = temp;
        cout << "�޸ĳɹ�" << endl;
    }
    system("pause");
    system("cls");
}
void System::clear_person()
{
    int select;
    cout << "ȷ��ɾ��:\n1.Yes\n2.No" << endl;
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