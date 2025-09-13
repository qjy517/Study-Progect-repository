#include <iostream>
#include <string>
#include "system.h"
#include "base.h"
#include <fstream>
# define FILENAME "test.txt"
using namespace std;
void System::show_maneu()
{
    cout << "********************************************************" << endl;
    cout << "**                    欢迎使用职工管理系统！                **" << endl;
    cout << "********************************************************" << endl;
    cout << "**        0. 退出管理程序                                 **" << endl;
    cout << "**        1. 增加职工信息                                 **" << endl;
    cout << "**        2. 删除职工信息                                 **" << endl;
    cout << "**        3. 查找离职职工                                 **" << endl;
    cout << "**        4. 修改职工信息                                 **" << endl;
    cout << "**        5. 显示职工信息                                 **" << endl;
    cout << "**        6. 按照编号排序                                 **" << endl;
    cout << "**        7. 清空所有文档                                 **" << endl;
    cout << "********************************************************" << endl;
    cout << "输入你的选择" << endl;
    cout << endl;
}
//重载文件>>
ifstream& operator>>(ifstream& is, Base& worker)
{
    is >> worker.m_id >> worker.m_name >> worker.m_apartment;
    return is;
}
//重载文件<<
ofstream& operator<<(ofstream& os, Base& worker)
{
    os << worker.m_id << " " << worker.m_name << " " << worker.m_apartment;
    return os;
}
//重载标准>>
istream& operator>>(istream& is, Base& worker)
{
    is >> worker.m_id >> worker.m_name >> worker.m_apartment;
    return is;
}
//重载标准<<
ostream& operator<<(ostream& os, Base& worker)
{
    os << worker.m_id << " " << worker.m_name << " " << worker.m_apartment;
    return os;
}
//以后可以直接写标准的<<,>>重载，因为文件<<,>>是继承自标准的
//获取文件中原有职员数量
int System::get_num()
{
    string id;
    string name;
    string apartment;
    ifstream file;//>>重载参数是if，所以不能使用f
    file.open(FILENAME, ios::in);
    int count = 0;
    Base temp;
    while (file>>temp)
    {
        count++;
    }
    file.close();
    return count;
}
//初始化worker指针
void System::initial()
{
    ifstream file;
    file.open(FILENAME, ios::in);
    int size = this->get_num();
    Base temp;
    for (int i = 0;i < size;i++)
    {
        //这样是错的，因为每个元素都是base的，不能区分是职员还是经理
        //file >> temp;
        //this->worker[i] = new Base(temp);
        file >> temp;
        if (temp.m_apartment == "职员")
        {
            //开辟到堆区是拷贝构造
            this->worker[i] = new Employ(temp);//这是一个拷贝构造函数，不是有三个构造函数的那个
        }
        if (temp.m_apartment == "经理")
        {
            this->worker[i] = new Manager(temp);
        }
        if (temp.m_apartment == "老板")
        {
            this->worker[i] = new Boss(temp);
        }
    }
    file.close();
}
System::System()
{
    //三种情况，文件不存在，文件存在但为空，文件存在不为空
    fstream file;
    file.open(FILENAME, ios::in);
    //第一种
    if (!file.is_open())
    {
        cout << "文件不存在" << endl;
        this->is_empty = true;
        this->worker_number = 0;
        this->worker = nullptr;
        file.close();//不要忘记close
    }
    //第二种
    else
    {
        file.seekg(0, ios::end);
        int size = file.tellg();
        if (size == 0)
        {
            cout << "文件为空" << endl;
            this->is_empty = true;
            this->worker_number = 0;
            this->worker = nullptr;
            file.close();
        }
        else
        {
            cout << "文件存在且不为空" << endl;
            this->is_empty = false;
            //要有一个函数来得到文件中有多少职员
            this->worker_number = this->get_num();
            //有一个函数来初始化worker
            this->worker = new Base * [this->worker_number];
            this->initial();
            file.close();
            for (int i = 0; i < this->worker_number; i++)
            {
                //<<运算符重载
                cout << *(this->worker[i]) << endl;
            }
        }
    }
}
System::~System()
{
    if (this->worker != nullptr)
    {
        delete[]worker;
        worker = nullptr;
    }
}
void System::save()
{
    fstream file;
    file.open(FILENAME, ios::out);
    for (int i = 0;i < this->worker_number;i++)
    {
        //重载文件<<
        file << *(worker[i]) << endl;
    }
}
bool System::id_unique(string &id)
{
    for (int i = 0;i < this->worker_number;i++)
    {
        if (worker[i]->m_id == id)
        {
            return false;
        }
    }
    return true;
}
void System::add_worker()
{
    int size;
    cout << "输入添加职员的人数:" << endl;
    cin >> size;
    int new_size = size + this->get_num();
    Base** new_space = new Base * [new_size];
    Base temp;
    for (int i = 0;i < this->get_num();i++)
    {
        new_space[i] = this->worker[i]; //浅拷贝，秩序释放头指针，不需要释放成员指针
    }
    for (int i = 0;i < size;i++)
    {
        cout << "输入新员工:" << endl;
        cin >> temp;
        while (true)
        {
            if (!this->id_unique(temp.m_id))
            {
                cout << "编号重复,重新输入" << endl;
                cin >> temp;
            }
            else
            {
                break;
            }
        }

        if (temp.m_apartment == "职员")
        {
            //开辟到堆区是拷贝构造过程
            new_space[this->get_num() + i] = new Employ(temp);//这是一个拷贝构造函数，不是有三个构造函数的那个
        }
        if (temp.m_apartment == "经理")
        {
            new_space[this->get_num() + i] = new Manager(temp);
        }
        if (temp.m_apartment == "老板")
        {
            new_space[this->get_num() + i] = new Boss(temp);
        }
    }
    delete[] worker;
    this->worker = new_space;
    this->is_empty = false;
    this -> worker_number = new_size;
    //将保存堆区的数据放到文件中，用save函数
    this->save();
    cout << "保存成功" << endl;
    system("pause");
    system("cls");
}
int System::search_worker(const string &id)
{
    for (int i = 0;i < this->worker_number;i++)
    {
        if ((this->worker[i])->m_id == id)
        {
            return i;
        }
    }
    return -1;
}
void System::delete_worker()
{
    //先定义一个查找目标人物的函数
    string id;
    cout << "输入删除人员的id:" << endl;
    cin >> id;
    int index = this->search_worker(id);
    if (this->worker_number == 0)
    {
        cout << "文件为空，无法删除" << endl;
    }
    if (index!=-1)
    {
        int i;
        delete worker[index];
        worker[index] = nullptr;
        for (i=index;i < this->worker_number-1;i++)
        {
            worker[i] = worker[i + 1];
        }
        //经历循环后，最后一个元素和倒数第二个元素的指向都是相同的，向让最后一个指针无效，不需要delete，因为浅拷贝会导致
        //两个指针都失效，只需设置成nullptr即可
        //delete worker[i + 1];//
        worker[i + 1] = nullptr;
        this->worker_number--;
        if (worker_number == 0)
        {
            this->is_empty = false;
        }
        else
        {
            this->is_empty = true;
        }
        this->save();
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}
void System::reverse_worker()
{
    if (this->is_empty)
    {
        cout << "文件为空,无法修改" << endl;
    }
    else
    {
        cout << "输入修改人员的id:" << endl;
        string id;
        cin >> id;
        int index = this->search_worker(id);
        if (index == -1)
        {
            cout << "查无此人" << endl;
        }
        else
        {
            cout << "输入新人员的信息:" << endl;
            Base temp;
            while (true)
            {
                cin >> temp;
                if (this->id_unique(temp.m_id))
                {
                    break;
                }
                else
                {
                    cout << "id重复,重新输入:" << endl;
                }
            }
            delete worker[index];
            worker[index] = nullptr;
            worker[index] = new Base(temp);
            this->save();
            cout << "修改成功" << endl;
            system("pause");
            system("cls");
        }
    }
}
void System::find_worker()
{
    if (this->is_empty)
    {
        cout << "文件为空" << endl;
    }
    else
    {
        string id;
        cout << "输入查找人员的id:" << endl;
        cin >> id;
        int index = this->search_worker(id);
        if (index != -1)
        {
            cout << *(this->worker[index]) << endl;
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    system("pause");
    system("cls");
}
void System::show_worker()
{
    if (this->is_empty)
    {
        cout << "没有职员" << endl;
    }
    else
    {
        for (int i = 0;i < this->worker_number;i++)
        {
            cout << *(this->worker[i]) << endl;
        }
    }
    system("pause");
    system("cls");
}
void System::sort_worker()
{
    //使用插入排序
    if (this->is_empty)
    {
        cout << "文件为空,无法排序" << endl;
    }
    else
    {
        for (int i = 1;i < this->worker_number;i++)
        {
            int j = i-1;
            Base* temp=this->worker[i];
            while (j >= 0)
            {
                if (this->worker[j]->m_id > temp->m_id)
                {
                    worker[j + 1] = worker[j];
                    j--;
                }
                else
                {
                    break;
                }
            }
            worker[j+1] = temp;
        }
        this->save();
        cout << "排序成功" << endl;
    }
    system("pause");
    system("cls");
}
void System::clear_worker()
{
    cout << "确定清空:\n1.Yes\n2.No" << endl;
    int select;
    cin >> select;
    if (select == 1)
    {
        fstream file;
        file.open(FILENAME, ios::trunc);
        if (this->worker != nullptr)
        {
            for (int i = 0;i < this->worker_number;i++)
            {
                if (this->worker[i] != nullptr)
                {
                    delete this->worker[i];
                    worker[i] = nullptr;
                }
            }
        }
        delete[]worker;
        this->worker = nullptr;
    }
    system("pause");
    system("cls");
}
