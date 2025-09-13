#include <iostream>
#define Maxsize 100
using namespace std;

void swap_data1(int& x, int& y);
void swap_data2(int* x, int* y);
void swap_data3(int x, int y);
void bubble_sort(int* data, const int& n);
void insert_sort(int* data,const int& n);
void quick_sort(int* data, int low, int hight);
void show_menu1();
void show_menu();
void sort_menu();
void seqlist_menu();
void seqlist_menu01();
void seqlist_menu02();

class SeqList
{
public:
    int* data;
    int length;
    int capacity;
    SeqList():data(nullptr),length(0),capacity(Maxsize){}
    SeqList(const int& n);
    ~SeqList();
    void initial_seqlist(const int& n);
    void insert_elem(const int &pos,const int&e);
    void delete_elem(const int &pos);
    int get_length();
    int search_elem(const int& e);
    void show_seqlist();
    int get_elem(const int&pos);
    bool is_empty();
    void destroy_seqlist();
};

//ͷ���洢���Ա���
class LinkList_node
{
public:
    int data;
    LinkList_node* next;
    LinkList_node():data(0),next(nullptr){}
    LinkList_node(int i):data(i),next(nullptr){}
    ~LinkList_node();
};
class LinkList
{
public:
    LinkList_node* list;//ָ������ͷ���
    //���캯������������
    LinkList() :list(nullptr){}
    ~LinkList()
    {
        this->destroy_list();
    }
    //��ʼ��
    void initial_list();
    //����
    void destroy_list();
    //�ж��Ƿ�Ϊ��
    bool is_empty();
    //�󳤶�
    int get_length();
    //������Ա�
    void show_list();
    //���߼���ŵõ�Ԫ��
    int get_elem(const int pos);
    //����Ԫ�ز���,�����������
    int search_elem(const int e);
    //��������
    void insert_elem(const int pos, const int e);
    //ɾ������
    void delete_elem(const int pos);

};
//Լɪ������
class Joseph_node:public LinkList_node
{
public:
    int number;
    Joseph_node(const int number_m,const int data_m):number(number_m),LinkList_node(data_m){}
};
class Joseph:public LinkList
{
public:
    Joseph()
    {
        initial_list();
    }
    void insert_j(const int pos, const int id, const int password)
    {
        if (pos < 1 || pos > get_length() + 1) {
            cout << "����λ����Ч" << endl;
            return;
        }
        Joseph_node* p = new Joseph_node(id, password);
        LinkList_node* q = this->list;
        int i = 0;
        while (q&&i<pos-1)
        {
            q = q->next;
            i++;
        }
        p->next = q->next;
        q->next = p;
        this->list->data++;
        cout << "��ӳɹ�" << endl;
        system("pause");
    }
    //ɾ���ڵ�,����ýڵ�ı�ţ��Լ�����
    int delete_j(LinkList_node*p,int &outid)
    {
        if (!p || !p->next)
        {
            outid = -1;
            return -1;
        }
        //ֻ���ɸ���ָ��ָ�����࣬����������ָ���࣬�������ù�����ת��ʵ��
        Joseph_node* dele_node = static_cast<Joseph_node*>(p->next);
        outid = dele_node->number;
        int password = dele_node->data;
        p->next = p->next->next;
        delete dele_node;
        this->list->data--;
        cout << "ɾ���ɹ�" << endl;
        system("pause");
        return password;
    }
    void make_circle()
    {
        LinkList_node* p = this->list;
        while (p->next)
        {
            p = p->next;
        }
        p->next = this->list->next;
    }
};
void joseph()
{
    Joseph j;
    int i, id, password, n;
    cout << "������Ա����:";
    cin >> n;
    for (i = 0;i < n;i++)
    {
        cout << "�����" << i + 1 << "���˵ı�ż�����:";
        cin >> id >> password;
        j.insert_j(i + 1, id, password);
    }
    j.make_circle();
    cout << "�����ʼ����:";
    cin >> password;
    int outid;
    LinkList_node* p = j.list;
    while (n > 0)
    {
        for (i = 0;i < password-1;i++)
        {
            p = p->next;
        }
        password = j.delete_j(p, outid);
        cout << outid << " " << endl;
        n--;
    }
    system("pause");
}
int main()
{
    show_menu();
    return 0;
}
//���ַ�ʽ����������
void swap_data1(int& x, int& y)
{
    cout << "ʹ�����ý���" << endl;
    int temp;
    temp = x;
    x = y;
    y = temp;
}
void swap_data2(int* x, int* y)
{
    cout << "ʹ��ָ�뽻��" << endl;
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void swap_data3(int x, int y)
{
    cout << "ֵ���ݽ���" << endl;
    int temp = x;
    x = y;
    y = temp;
}
//ð������
void bubble_sort(int* data, const int& n)
{
    int i;
    int j;
    if (data)
        for (i = 0;i < n - 1;i++)
        {
            for (j = 0;j < n - 1 - i;j++)
            {
                if (data[j] >= data[j + 1])
                {
                    int temp;
                    temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
}
//��������
void quick_sort(int* data, int low, int hight)
{
    if (low >= hight)
    {
        return;
    }
    int i = low, j = hight;
    int temp = data[low];
    while (i < j)
    {
        while (data[j] > temp && i < j)
        {
            j--;
        }
        data[i] = data[j];
        while (data[i] <= temp && i < j)
        {
            i++;
        }
        data[j] = data[i];
    }
    data[i] = temp;
    quick_sort(data, low, i - 1);
    quick_sort(data, i + 1, hight);
}
//չʾ���۵Ĳ˵���ʵ��
void show_menu1()
{
    int select;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t=================��c++����ʵ��================" << endl;
        cout << "\t\t\t\t********1.ʹ�����ý�����������ֵ**************" << endl;
        cout << "\t\t\t\t********2.ʹ��ָ�뽻����������ֵ************" << endl;
        cout << "\t\t\t\t********3.ʹ��ֵ���ݽ�����������ֵ**********" << endl;
        cout << "\t\t\t\t********0.�����ϼ�Ŀ¼**********" << endl;
        cout << "����������:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "��ӭ�´�ʹ��,�������������һ��Ŀ¼" << endl;
            system("pause");
            return;
            break;
        }
        case 1:
        {
            int x, y;
            cout << "����x��ֵ:";
            cin >> x;
            cout << "����y��ֵ:";
            cin >> y;
            swap_data1(x, y);
            cout << "������x��y��ֵ:" << endl;
            cout << "x=" << x << " " << "y=" << y << endl;
            system("pause");
            break;
        }
        case 2:
        {
            int x, y;
            cout << "����x��ֵ:";
            cin >> x;
            cout << "����y��ֵ:";
            cin >> y;
            swap_data2(&x, &y);
            cout << "������x��y��ֵ:" << endl;
            cout << "x=" << x << " " << "y=" << y << endl;
            system("pause");
            break;
        }
        case 3:
        {
            int x, y;
            cout << "����x��ֵ:";
            cin >> x;
            cout << "����y��ֵ:";
            cin >> y;
            swap_data3(x, y);
            cout << "������x��y��ֵ:" << endl;
            cout << "x=" << x << " " << "y=" << y << endl;
            system("pause");
            break;
        }
        default:
        {
            cout << "������Ŵ���,��������ȷ�����:" << endl;
            system("pause");
            break;
        }
        }
    }
}
//չʾ���˵�
void show_menu()
{
    int select;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t==========���ݽṹ==========" << endl;
        cout << "\t\t\t\t********1.����**************" << endl;
        cout << "\t\t\t\t********2.���Ա�************" << endl;
        cout << "\t\t\t\t********3.�����㷨************" << endl;
        cout << "\t\t\t\t********0.�˳�����**********" << endl;
        system("pause");
        cout << "����������:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "��ӭ�´�ʹ��" << endl;
            exit(0);
        }
        case 1:
        {
            show_menu1();
            break;
        }
        case 2:
        {
            seqlist_menu();
            break;
        }
        case 3:
        {
            sort_menu();
            break;
        }
        default:
        {
            cout << "�������ָ��,��������" << endl;
            system("pause");
            break;
        }
        }
    }
}
void sort_menu()
{
    int select;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t==========�����㷨==========" << endl;
        cout << "\t\t\t\t********1.ð������**************" << endl;
        cout << "\t\t\t\t********2.��������************" << endl;
        cout << "\t\t\t\t********3.��������************" << endl;
        cout << "\t\t\t\t********0.�˳�����**********" << endl;
        cout << "����������:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "��ӭ�´�ʹ��,�������������һ��Ŀ¼" << endl;
            system("pause");
            return;
            break;
        }
        case 1:
        {
            int n;
            cout << "������Ҫ�����Ԫ������:";
            cin >> n;
            int* data = new int[n];
            cout << "����Ҫ�����" << n << "��Ԫ��" << endl;
            for (int i = 0;i < n;i++)
            {
                cin >> data[i];
            }
            bubble_sort(data, n);
            cout << "������Ԫ��:" << endl;
            for (int i = 0;i < n;i++)
            {
                cout << data[i] << " ";
            }
            cout << endl;
            delete[]data;
            system("pause");
            break;
        }
        case 2:
        {
            int n;
            cout << "������Ҫ�����Ԫ������:";
            cin >> n;
            int* data = new int[n];
            cout << "����Ҫ�����" << n << "��Ԫ��" << endl;
            for (int i = 0;i < n;i++)
            {
                cin >> data[i];
            }
            insert_sort(data, n);
            cout << "������Ԫ��:" << endl;
            for (int i = 0;i < n;i++)
            {
                cout << data[i] << " ";
            }
            cout << endl;
            delete[]data;
            system("pause");
            break;
        }
        case 3:
        {
            int n;
            cout << "������Ҫ�����Ԫ������:";
            cin >> n;
            int* data = new int[n];
            cout << "����Ҫ�����" << n << "��Ԫ��" << endl;
            for (int i = 0;i < n;i++)
            {
                cin >> data[i];
            }
            quick_sort(data, 0, n - 1);
            cout << "������Ԫ��:" << endl;
            for (int i = 0;i < n;i++)
            {
                cout << data[i] << " ";
            }
            cout << endl;
            delete[]data;
            system("pause");
            break;
        }
        default:
        {
            cout << "������Ŵ���,��������ȷ�����:" << endl;
            system("pause");
            break;
        }
        }
    }
}
void insert_sort(int* data, const int& n)
{
    int i, j;
    for (int i = 1;i < n;i++)
    {
        int temp = data[i];
        j = i;
        while (j >= 0)
        {
            if (temp < data[j - 1])
            {
                data[j] = data[j - 1];
                j--;
            }
            else
            {
                break;
            }
        }
        data[j] = temp;
    }
}
void seqlist_menu()
{
    int select;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t==========���Ա�==========" << endl;
        cout << "\t\t\t\t********1.˳���**************" << endl;
        cout << "\t\t\t\t********2.������************" << endl;
        cout << "\t\t\t\t********3.Լɪ������************" << endl;
        cout << "\t\t\t\t********0.�˳�����**********" << endl;
        cout << "����������:" << endl;
        cin >> select;
        switch(select)
        {
        case 0:
        {
            cout << "��ӭ�´�ʹ��,�������������һ��Ŀ¼" << endl;
            system("pause");
            return;
            break;
            break;
        }
        case 1:
        {
            seqlist_menu01();
            break;
        }
        case 2:
        {
            seqlist_menu02();
            break;
        }
        case 3:
        {
            joseph();
            break;
        }
        default:
        {
            cout << "������Ŵ���,��������ȷ�����:" << endl;
            system("pause");
            break;
        }
        }
    }
}
void seqlist_menu01()
{
    int select;
    SeqList l;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t==========˳���==========" << endl;
        cout << "\t\t\t\t********0.�˳�����**************" << endl;
        cout << "\t\t\t\t********1.initial**************" << endl;
        cout << "\t\t\t\t********2.insert_elem************" << endl;
        cout << "\t\t\t\t********3.delete_elem**********" << endl;
        cout << "\t\t\t\t********4.get_length**********" << endl;
        cout << "\t\t\t\t********5.search_elem*********" << endl;
        cout << "\t\t\t\t********6.show_seqlist**********" << endl;
        cout << "\t\t\t\t********7.get_elem**********" << endl;
        cout << "\t\t\t\t********8.destroy_seqlist**********" << endl;
        cout << "����������:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "��ӭ�´�ʹ��,�������������һ��Ŀ¼" << endl;
            system("pause");
            return;
            break;
        }
        case 1:
        {
            int num;
            cout << "�������Ա�Ԫ������:";
            cin >> num;
            l.initial_seqlist(num);
            break;
        }
        case 2:
        {
            int i, pos;
            if (l.get_length() == -1)
            {
                break;
            }
            cout << "Ŀǰ���Ա���Ϊ:" << l.get_length() << endl;
            cout << "�������Ԫ�ػ���λ��:";
            cin >> i >> pos;
            l.insert_elem(pos, i);
            break;
        }
        case 3:
        {
            int pos;
            cout << "����ɾ��Ԫ�ص��߼����:";
            cin >> pos;
            l.delete_elem(pos);
            break;
        }
        case 4:
        {
            cout << "���Ա���Ϊ:" << l.get_length() << endl;
            system("pause");
            break;
        }
        case 5:
        {
            int pos;
            cout << "����Ҫ����Ԫ�ص�ֵ:";
            cin >> pos;
            cout << "����Ԫ���±�Ϊ:" << l.search_elem(pos) << endl;
            system("pause");
            break;
        }
        case 6:
        {
            l.show_seqlist();
            break;
        }
        case 7:
        {
            int pos;
            cout << "����Ҫ����Ԫ���߼����:";
            cin >> pos;
            cout << "��" << pos << "��Ԫ��Ϊ" << l.get_elem(pos) << endl;
            system("pause");
            break;
        }
        case 8:
        {
            l.destroy_seqlist();
            cout << "���ٳɹ�" << endl;
            system("pause");
            break;
        }
        default:
        {
            cout << "������Ŵ���,��������ȷ�����:" << endl;
            system("pause");
            break;
        }
        }
    }
}
void seqlist_menu02()
{
    int select;
    LinkList l;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t==========������==========" << endl;
        cout << "\t\t\t\t********0.�˳�����**************" << endl;
        cout << "\t\t\t\t********1.initial**************" << endl;
        cout << "\t\t\t\t********2.insert_elem************" << endl;
        cout << "\t\t\t\t********3.delete_elem**********" << endl;
        cout << "\t\t\t\t********4.get_length**********" << endl;
        cout << "\t\t\t\t********5.search_elem*********" << endl;
        cout << "\t\t\t\t********6.show_seqlist**********" << endl;
        cout << "\t\t\t\t********7.get_elem**********" << endl;
        cout << "\t\t\t\t********8.destroy_seqlist**********" << endl;
        cout << "����������:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "��ӭ�´�ʹ��,�������������һ��Ŀ¼" << endl;
            system("pause");
            return;
            break;
        }
        case 1:
        {
            l.initial_list();
            cout << "��ʼ�����" << endl;
            system("pause");
            break;
        }
        case 2:
        {
            cout << "Ŀǰ����Ԫ��Ϊ:" << endl;
            l.show_list();
            int pos, e;
            cout << "�������λ�ü�Ԫ�ص�ֵ(�߼����):";
            cin >> pos >> e;
            l.insert_elem(pos, e);
            break;
        }
        case 3:
        {
            cout << "Ŀǰ����Ԫ��Ϊ:" << endl;
            l.show_list();
            int pos;
            cout << "����ɾ��Ԫ�ص�λ��(�߼����):";
            cin >> pos;
            l.delete_elem(pos);
            break;
        }
        case 4:
        {
            cout << "���Ա���Ϊ:" << l.get_length() << endl;
            system("pause");
            break;
        }
        case 5:
        {
            int e;
            cout << "�������Ԫ�ص�ֵ:";
            cin >> e;
            int pos = l.search_elem(e);
            if (pos== -1)
            {
                cout << "δ�ҵ�Ԫ��" << endl;
                system("pause");
                break;
            }
            else
            {
                cout << e << "�ǵ�" << pos + 1 << "��Ԫ��" << endl;
                system("pause");
                break;
            }
        }
        case 6:
        {
            l.show_list();
            system("pause");
            break;
        }
        case 7:
        {
            int pos;
            cout << "�������Ԫ�ص��߼����:";
            cin >> pos;
            cout << "��" << pos << "��Ԫ����" << l.get_elem(pos) << endl;
            system("pause");
            break;
        }
        case 8:
        {
            l.destroy_list();
        }
        }
    }
}
SeqList::SeqList(const int& n)
{
    this->data = new int[n];
    this->length = 0;
    this->capacity = n;
}
SeqList::~SeqList()
{
    if (this->data)
    {
        delete[]data;
        this->data = nullptr;
        this->length = 0;
        this->capacity = 0;
    }
}
void SeqList::initial_seqlist(const int& n)
{
    this->data = new int[n];
    this->length = 0;
    this->capacity = n;
}
bool SeqList::is_empty()
{
    return (this->length == 0) ? true : false;
}
//pos���߼����
void SeqList::insert_elem(const int& pos, const int& e)
{
    if (this->data == nullptr)
    {
        cout << "δ��ʼ��,���Ƚ��г�ʼ��" << endl;
        system("pause");
        return;
    }
    if (pos <= 0 || pos > this->length + 1)
    {
        cout << "����λ���������" << endl;
        system("pause");
        return;
    }
    if (this->length == this->capacity)
    {
        cout << "���Ա��Ѿ�����,�޷�����" << endl;
        system("pause");
    }
    int i;
    for (i = this->length-1;i >= pos - 1;i--)
    {
        this->data[i+1] = data[i];
    }
    this->data[i + 1] = e;
    this->length++;
    cout << "����ɹ�" << endl;
    system("pause");
}
void SeqList::delete_elem(const int& pos)
{
    if (this->data == nullptr)
    {
        cout << "δ��ʼ��,���Ƚ��г�ʼ��" << endl;
        system("pause");
        return;
    }
    if (pos <= 0 || pos > this->length)
    {
        cout << "ɾ��λ���������" << endl;
        system("pause");
        return;
    }
    int i;
    for (i = pos;i < this->length;i++)
    {
        this->data[i - 1] = this->data[i];
    }
    this->length--;
    cout << "ɾ���ɹ�" << endl;
    system("pause");
}
int SeqList::get_length()
{
    if (this->data == nullptr)
    {
        cout << "δ��ʼ��,���Ƚ��г�ʼ��" << endl;
        system("pause");
        return-1;
    }
    return this->length;
}
int SeqList::search_elem(const int& e)
{
    if (this->data == nullptr)
    {
        cout << "δ��ʼ��,���Ƚ��г�ʼ��" << endl;
        system("pause");
        return-1;
    }
    int i = 0;
    while (i < this->length)
    {
        if (this->data[i] == e)
        {
            cout << e << "�����Ա��е�" << i + 1 << "��Ԫ��" << endl;
            system("pause");
            return i;
        }
    }
    cout << "û���ҵ���ӦԪ��" << endl;
    system("pause");
    return -1;
}
void SeqList::show_seqlist()
{
    if (this->data == nullptr)
    {
        cout << "δ��ʼ��,���Ƚ��г�ʼ��" << endl;
        system("pause");
        return;
    }
    if (this->is_empty())
    {
        cout << "���Ա�Ϊ��" << endl;
        system("pause");
        return;
    }
    for (int i = 0;i < this->length;i++)
    {
        cout << this->data[i] << " ";
    }
    system("pause");
    cout << endl;
}
int SeqList::get_elem(const int& pos)
{
    if (this->data == nullptr)
    {
        cout << "δ��ʼ��,���Ƚ��г�ʼ��" << endl;
        system("pause");
        return-1;
    }
    if (pos <= 0 || pos > length)
    {
        cout << "������Ŵ���" << endl;
        system("pause");
        return-1;
    }
    return this->data[pos - 1];
}
void SeqList::destroy_seqlist()
{
    this->~SeqList();
}
//�����Ա����
LinkList_node::~LinkList_node()
{
    cout << "[�ڵ�����] �ͷ�����Ϊ " << this->data << " �Ľڵ�" << endl;
}

void LinkList::initial_list()
{
    if (this->list != nullptr)
    {
        cout << "�����ظ���ʼ��" << endl;
        system("pause");
        return;
    }
    this->list = new LinkList_node;
}
bool LinkList::is_empty()
{
    if (this->list == nullptr)
    {
        cout << "���Ƚ��г�ʼ��" << endl;
        system("pause");
        return true;
    }
    else
    {
        return (this->list->data == 0) ? true : false;
    }
}
int LinkList::get_length()
{
    if (this->list == nullptr)
    {
        cout << "���Ƚ��г�ʼ��" << endl;
        system("pause");
        return -1;
    }
    else
    {
        return this->list->data;
    }
}
void LinkList::insert_elem(const int pos, const int e)
{
    if (this->list == nullptr)
    {
        cout << "���Ƚ��г�ʼ��" << endl;
        system("pause");
        return ;
    }
    if (pos <= 0 || pos > this->list->data + 1)
    {
        cout << "����λ�ô���" << endl;
        system("pause");
        return;
    }
    LinkList_node* p = this->list;
    int i = 0;
    //ѭ������pos-1���ڵ�
    while (p && i < pos-1)
    {
        p = p->next;
        i++;
    }
    if (!p)
    {
        cout << "����λ�ô���" << endl;
        system("pause");
        return;
    }
    LinkList_node* q = new LinkList_node;
    q->next = p->next;
    p->next = q;
    q->data = e;
    this->list->data++;
    cout << "��ӳɹ�" << endl;
    system("pause");
}
void LinkList::delete_elem(const int pos)
{
    if (this->list == nullptr)
    {
        cout << "���Ƚ��г�ʼ��" << endl;
        system("pause");
        return;
    }
    int i = 0;
    LinkList_node* p = this->list;
    while (p && i < pos - 1)
    {
        p = p->next;
        i++;
    }
    if (!p)
    {
        cout << "ɾ��λ�ô���" << endl;
        system("pause");
        return;
    }
    LinkList_node* temp = p->next;
    p->next = temp->next;
    delete temp;
    this->list->data--;
    cout << "ɾ���ɹ�" << endl;
    system("pause");
}
void LinkList::show_list()
{
    if (this->list == nullptr)
    {
        cout << "���Ƚ��г�ʼ��" << endl;
        system("pause");
        return;
    }
    if (this->is_empty())
    {
        cout << "����Ϊ��" << endl;
        system("pause");
        return;
    }
    LinkList_node* p = this->list;
    for (int i = 0;i < this->list->data;i++)
    {
        p = p->next;
        cout << p->data << " ";
    }
    cout << endl;
}
int LinkList::search_elem(const int e)
{
    if (this->list == nullptr)
    {
        cout << "���Ƚ��г�ʼ��" << endl;
        system("pause");
        return-1;
    }
    int pos=-1;
    LinkList_node* p = this->list;
    while (p)
    {
        p = p->next;
        pos++;
        if (p->data == e)
        {
            return pos;
        }
    }
    return -1;
}
int LinkList::get_elem(const int pos)
{
    if (this->list == nullptr)
    {
        cout << "���Ƚ��г�ʼ��" << endl;
        system("pause");
        return-1;
    }
    LinkList_node* p = this->list;
    int i = 0;
    while (p && i < pos)
    {
        p = p->next;
    }
    if (!p)
    {
        cout << "��ѯλ�ô���" << endl;
        system("pause");
        return -1;
    }
    else
    {
        return p->data;
    }
}
void LinkList::destroy_list()
{
    if (this->list == nullptr)
    {
        cout << "���Ƚ��г�ʼ��" << endl;
        system("pause");
        return;
    }
    LinkList_node* current = this->list;
    LinkList_node* last = nullptr;
    while (current)
    {
        last= current;
        current = current->next;
        delete last;
    }
    cout << "�������" << endl;
    system("pause");
}
