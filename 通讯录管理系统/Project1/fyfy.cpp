#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
# define Max 100
using namespace std;
class Person
{
    //��⹹�캯��
private:
    string name;
    string phone;
    string address;
    int age;
    int sex;
public:
    void set_infor();
    void get_infor();
    void revise();
    string get_name();
};//ð��
class Person_book
{
public:
    vector<Person> address_book;
    void add_person();
    void delete_person();
    void clear();
    void find_person();
    void look_address_book();
    void revise_person();
};
void show_maneu();
int main()
{
    Person_book book;
    int sec;
    while (true)
    {
        show_maneu();
        if (!(cin >> sec)) {
            cin.clear();  // �������״̬
            // ���Ի�������ʣ����ַ�
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�����������������(0-6)" << endl;
            continue;
        }
        switch (sec)
        {
        case 1:
        {
            book.add_person();break;
        }
        case 2:
        {
            book.delete_person();break;
        }
        case 3:
        {
            book.find_person();break;
        }
        case 4:
        {
            book.look_address_book();break;
        }
        case 5:
        {
            book.revise_person();break;
        }
        case 6:
        {
            book.clear();break;
        }
        case 0:
        {
            cout << "��ӭ�´�ʹ��" << endl;
            system("pause");
            return 0;
        }
        default:
        {
            break;
        }
        }
    }

}
//���ⶨ�庯���ĸ�ʽ
void Person::set_infor()
{
    cout << "����������" << endl;
    cin >> name;
    cout << "�����Ա�" << endl;
    int a;
    while (true)
    {
        cin >> a;
        if (a == 0 || a == 1)
        {
            sex = a;
            break;
        }
        cout << "����������������" << endl;
    }
    cout << "��������:" << endl;
    cin >> age;
    cout << "�����ַ��" << endl;
    cin >> address;
    cout << "����绰��" << endl;
    cin >> phone;
}
void Person::get_infor()
{
    if (sex == 1)
    {
        cout << name << " " << "��" << " " << age << " " << phone << " " << address << endl;
    }
    else
    {
        cout << name << " " << "Ů" << " " << age << " " << phone << " " << address << endl;
    }
}
void Person::revise()
{
    cout << "������������" << endl;
    cin >> name;
    cout << "�������Ա�" << endl;
    int a;
    while (true)
    {
        cin >> a;
        if (a == 0 || a == 1)
        {
            sex = a;
            break;
        }
        cout << "����������������" << endl;
    }
    cout << "����������:" << endl;
    cin >> age;
    cout << "�����µ�ַ:" << endl;
    cin >> address;
    cout << "�����µ绰:" << endl;
    cin >> phone;
}
string Person::get_name()
{
    return name;
}
void Person_book::add_person()
{
    Person temp;
    if (address_book.size() == Max)
    {
        cout << "ͨѶ¼����" << endl;
        return;
    }
    temp.set_infor();
    address_book.push_back(temp);
    cout << "��ӳɹ�" << endl;
    system("pause");
    system("cls");
}
void Person_book::delete_person()
{
    if (address_book.size() == 0)
    {
        cout << "ͨѶ¼Ϊ���޷�ɾ��" << endl;
        return;
    }
    string target;
    cout << "����Ŀ����ϵ��:" << endl;
    cin >> target;
    auto it = find_if(address_book.begin(), address_book.end(), [&target](Person& p) {
        return p.get_name() == target;
        });
    if (it == address_book.end())
    {
        cout << "û���ҵ���ϵ��" << endl;
        return;
    }
    address_book.erase(it);
    cout << "ɾ���ɹ�" << endl;
    system("pause");
    system("cls");
}
void Person_book::find_person()
{
    string target;
    if (address_book.size() == 0)
    {
        cout << "ͨѶ¼Ϊ���޷�����" << endl;
        return;
    }
    cout << "����Ŀ����ϵ��:" << endl;
    cin >> target;
    auto it = find_if(address_book.begin(), address_book.end(), [&target](Person& p) {
        return p.get_name() == target;
        });
    if (it == address_book.end())
    {
        cout << "û���ҵ���ϵ��" << endl;
        return;
    }
    (*it).get_infor();
    system("pause");
    system("cls");
}
void Person_book::clear()
{
    address_book.clear();
    cout << "ɾ���ɹ�" << endl;
    system("pause");
    system("cls");
}
void Person_book::look_address_book()
{
    for (auto i : address_book)
    {
        i.get_infor();
    }
    system("pause");
    system("cls");
}
void Person_book::revise_person()
{
    string target;
    if (address_book.size() == 0)
    {
        cout << "ͨѶ¼Ϊ��,�޷��޸�" << endl;
        return;
    }
    cout << "����Ŀ����ϵ�ˣ�" << endl;
    cin >> target;
    auto it = find_if(address_book.begin(), address_book.end(), [&target](Person& p) {
        return p.get_name() == target;
        });
    (*it).revise();
    cout << "�޸ĳɹ�" << endl;
    system("pause");
    system("cls");
}
void show_maneu()
{
    cout << "1.�����ϵ��" << endl;
    cout << "2.ɾ����ϵ��" << endl;
    cout << "3.������ϵ��" << endl;
    cout << "4.�鿴ȫ����ϵ��" << endl;
    cout << "5.�޸���ϵ��" << endl;
    cout << "6.�����ϵ��" << endl;
    cout << "0.�˳�ͨѶ��" << endl;
}