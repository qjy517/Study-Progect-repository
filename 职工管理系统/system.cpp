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
    cout << "**                    ��ӭʹ��ְ������ϵͳ��                **" << endl;
    cout << "********************************************************" << endl;
    cout << "**        0. �˳��������                                 **" << endl;
    cout << "**        1. ����ְ����Ϣ                                 **" << endl;
    cout << "**        2. ɾ��ְ����Ϣ                                 **" << endl;
    cout << "**        3. ������ְְ��                                 **" << endl;
    cout << "**        4. �޸�ְ����Ϣ                                 **" << endl;
    cout << "**        5. ��ʾְ����Ϣ                                 **" << endl;
    cout << "**        6. ���ձ������                                 **" << endl;
    cout << "**        7. ��������ĵ�                                 **" << endl;
    cout << "********************************************************" << endl;
    cout << "�������ѡ��" << endl;
    cout << endl;
}
//�����ļ�>>
ifstream& operator>>(ifstream& is, Base& worker)
{
    is >> worker.m_id >> worker.m_name >> worker.m_apartment;
    return is;
}
//�����ļ�<<
ofstream& operator<<(ofstream& os, Base& worker)
{
    os << worker.m_id << " " << worker.m_name << " " << worker.m_apartment;
    return os;
}
//���ر�׼>>
istream& operator>>(istream& is, Base& worker)
{
    is >> worker.m_id >> worker.m_name >> worker.m_apartment;
    return is;
}
//���ر�׼<<
ostream& operator<<(ostream& os, Base& worker)
{
    os << worker.m_id << " " << worker.m_name << " " << worker.m_apartment;
    return os;
}
//�Ժ����ֱ��д��׼��<<,>>���أ���Ϊ�ļ�<<,>>�Ǽ̳��Ա�׼��
//��ȡ�ļ���ԭ��ְԱ����
int System::get_num()
{
    string id;
    string name;
    string apartment;
    ifstream file;//>>���ز�����if�����Բ���ʹ��f
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
//��ʼ��workerָ��
void System::initial()
{
    ifstream file;
    file.open(FILENAME, ios::in);
    int size = this->get_num();
    Base temp;
    for (int i = 0;i < size;i++)
    {
        //�����Ǵ�ģ���Ϊÿ��Ԫ�ض���base�ģ�����������ְԱ���Ǿ���
        //file >> temp;
        //this->worker[i] = new Base(temp);
        file >> temp;
        if (temp.m_apartment == "ְԱ")
        {
            //���ٵ������ǿ�������
            this->worker[i] = new Employ(temp);//����һ���������캯�����������������캯�����Ǹ�
        }
        if (temp.m_apartment == "����")
        {
            this->worker[i] = new Manager(temp);
        }
        if (temp.m_apartment == "�ϰ�")
        {
            this->worker[i] = new Boss(temp);
        }
    }
    file.close();
}
System::System()
{
    //����������ļ������ڣ��ļ����ڵ�Ϊ�գ��ļ����ڲ�Ϊ��
    fstream file;
    file.open(FILENAME, ios::in);
    //��һ��
    if (!file.is_open())
    {
        cout << "�ļ�������" << endl;
        this->is_empty = true;
        this->worker_number = 0;
        this->worker = nullptr;
        file.close();//��Ҫ����close
    }
    //�ڶ���
    else
    {
        file.seekg(0, ios::end);
        int size = file.tellg();
        if (size == 0)
        {
            cout << "�ļ�Ϊ��" << endl;
            this->is_empty = true;
            this->worker_number = 0;
            this->worker = nullptr;
            file.close();
        }
        else
        {
            cout << "�ļ������Ҳ�Ϊ��" << endl;
            this->is_empty = false;
            //Ҫ��һ���������õ��ļ����ж���ְԱ
            this->worker_number = this->get_num();
            //��һ����������ʼ��worker
            this->worker = new Base * [this->worker_number];
            this->initial();
            file.close();
            for (int i = 0; i < this->worker_number; i++)
            {
                //<<���������
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
        //�����ļ�<<
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
    cout << "�������ְԱ������:" << endl;
    cin >> size;
    int new_size = size + this->get_num();
    Base** new_space = new Base * [new_size];
    Base temp;
    for (int i = 0;i < this->get_num();i++)
    {
        new_space[i] = this->worker[i]; //ǳ�����������ͷ�ͷָ�룬����Ҫ�ͷų�Աָ��
    }
    for (int i = 0;i < size;i++)
    {
        cout << "������Ա��:" << endl;
        cin >> temp;
        while (true)
        {
            if (!this->id_unique(temp.m_id))
            {
                cout << "����ظ�,��������" << endl;
                cin >> temp;
            }
            else
            {
                break;
            }
        }

        if (temp.m_apartment == "ְԱ")
        {
            //���ٵ������ǿ����������
            new_space[this->get_num() + i] = new Employ(temp);//����һ���������캯�����������������캯�����Ǹ�
        }
        if (temp.m_apartment == "����")
        {
            new_space[this->get_num() + i] = new Manager(temp);
        }
        if (temp.m_apartment == "�ϰ�")
        {
            new_space[this->get_num() + i] = new Boss(temp);
        }
    }
    delete[] worker;
    this->worker = new_space;
    this->is_empty = false;
    this -> worker_number = new_size;
    //��������������ݷŵ��ļ��У���save����
    this->save();
    cout << "����ɹ�" << endl;
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
    //�ȶ���һ������Ŀ������ĺ���
    string id;
    cout << "����ɾ����Ա��id:" << endl;
    cin >> id;
    int index = this->search_worker(id);
    if (this->worker_number == 0)
    {
        cout << "�ļ�Ϊ�գ��޷�ɾ��" << endl;
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
        //����ѭ�������һ��Ԫ�غ͵����ڶ���Ԫ�ص�ָ������ͬ�ģ��������һ��ָ����Ч������Ҫdelete����Ϊǳ�����ᵼ��
        //����ָ�붼ʧЧ��ֻ�����ó�nullptr����
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
        cout << "ɾ���ɹ�" << endl;
    }
    else
    {
        cout << "���޴���" << endl;
    }
    system("pause");
    system("cls");
}
void System::reverse_worker()
{
    if (this->is_empty)
    {
        cout << "�ļ�Ϊ��,�޷��޸�" << endl;
    }
    else
    {
        cout << "�����޸���Ա��id:" << endl;
        string id;
        cin >> id;
        int index = this->search_worker(id);
        if (index == -1)
        {
            cout << "���޴���" << endl;
        }
        else
        {
            cout << "��������Ա����Ϣ:" << endl;
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
                    cout << "id�ظ�,��������:" << endl;
                }
            }
            delete worker[index];
            worker[index] = nullptr;
            worker[index] = new Base(temp);
            this->save();
            cout << "�޸ĳɹ�" << endl;
            system("pause");
            system("cls");
        }
    }
}
void System::find_worker()
{
    if (this->is_empty)
    {
        cout << "�ļ�Ϊ��" << endl;
    }
    else
    {
        string id;
        cout << "���������Ա��id:" << endl;
        cin >> id;
        int index = this->search_worker(id);
        if (index != -1)
        {
            cout << *(this->worker[index]) << endl;
        }
        else
        {
            cout << "���޴���" << endl;
        }
    }
    system("pause");
    system("cls");
}
void System::show_worker()
{
    if (this->is_empty)
    {
        cout << "û��ְԱ" << endl;
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
    //ʹ�ò�������
    if (this->is_empty)
    {
        cout << "�ļ�Ϊ��,�޷�����" << endl;
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
        cout << "����ɹ�" << endl;
    }
    system("pause");
    system("cls");
}
void System::clear_worker()
{
    cout << "ȷ�����:\n1.Yes\n2.No" << endl;
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
