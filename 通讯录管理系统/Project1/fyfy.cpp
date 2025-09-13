#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
# define Max 100
using namespace std;
class Person
{
    //理解构造函数
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
};//冒号
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
            cin.clear();  // 清除错误状态
            // 忽略缓冲区中剩余的字符
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入错误，请输入数字(0-6)" << endl;
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
            cout << "欢迎下次使用" << endl;
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
//类外定义函数的格式
void Person::set_infor()
{
    cout << "输入姓名：" << endl;
    cin >> name;
    cout << "输入性别" << endl;
    int a;
    while (true)
    {
        cin >> a;
        if (a == 0 || a == 1)
        {
            sex = a;
            break;
        }
        cout << "输入有误，重新输入" << endl;
    }
    cout << "输入年龄:" << endl;
    cin >> age;
    cout << "输入地址：" << endl;
    cin >> address;
    cout << "输入电话：" << endl;
    cin >> phone;
}
void Person::get_infor()
{
    if (sex == 1)
    {
        cout << name << " " << "男" << " " << age << " " << phone << " " << address << endl;
    }
    else
    {
        cout << name << " " << "女" << " " << age << " " << phone << " " << address << endl;
    }
}
void Person::revise()
{
    cout << "输入新姓名：" << endl;
    cin >> name;
    cout << "输入新性别" << endl;
    int a;
    while (true)
    {
        cin >> a;
        if (a == 0 || a == 1)
        {
            sex = a;
            break;
        }
        cout << "输入有误，重新输入" << endl;
    }
    cout << "输入新年龄:" << endl;
    cin >> age;
    cout << "输入新地址:" << endl;
    cin >> address;
    cout << "输入新电话:" << endl;
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
        cout << "通讯录满了" << endl;
        return;
    }
    temp.set_infor();
    address_book.push_back(temp);
    cout << "添加成功" << endl;
    system("pause");
    system("cls");
}
void Person_book::delete_person()
{
    if (address_book.size() == 0)
    {
        cout << "通讯录为空无法删除" << endl;
        return;
    }
    string target;
    cout << "输入目标联系人:" << endl;
    cin >> target;
    auto it = find_if(address_book.begin(), address_book.end(), [&target](Person& p) {
        return p.get_name() == target;
        });
    if (it == address_book.end())
    {
        cout << "没有找到联系人" << endl;
        return;
    }
    address_book.erase(it);
    cout << "删除成功" << endl;
    system("pause");
    system("cls");
}
void Person_book::find_person()
{
    string target;
    if (address_book.size() == 0)
    {
        cout << "通讯录为空无法查找" << endl;
        return;
    }
    cout << "输入目标联系人:" << endl;
    cin >> target;
    auto it = find_if(address_book.begin(), address_book.end(), [&target](Person& p) {
        return p.get_name() == target;
        });
    if (it == address_book.end())
    {
        cout << "没有找到联系人" << endl;
        return;
    }
    (*it).get_infor();
    system("pause");
    system("cls");
}
void Person_book::clear()
{
    address_book.clear();
    cout << "删除成功" << endl;
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
        cout << "通讯录为空,无法修改" << endl;
        return;
    }
    cout << "输入目标联系人：" << endl;
    cin >> target;
    auto it = find_if(address_book.begin(), address_book.end(), [&target](Person& p) {
        return p.get_name() == target;
        });
    (*it).revise();
    cout << "修改成功" << endl;
    system("pause");
    system("cls");
}
void show_maneu()
{
    cout << "1.添加联系人" << endl;
    cout << "2.删除联系人" << endl;
    cout << "3.查找联系人" << endl;
    cout << "4.查看全部联系人" << endl;
    cout << "5.修改联系人" << endl;
    cout << "6.清空联系人" << endl;
    cout << "0.退出通讯簿" << endl;
}