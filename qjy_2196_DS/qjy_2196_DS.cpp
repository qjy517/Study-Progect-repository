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

//头结点存储线性表长度
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
    LinkList_node* list;//指向链表头结点
    //构造函数与析构函数
    LinkList() :list(nullptr){}
    ~LinkList()
    {
        this->destroy_list();
    }
    //初始化
    void initial_list();
    //销毁
    void destroy_list();
    //判断是否为空
    bool is_empty();
    //求长度
    int get_length();
    //输出线性表
    void show_list();
    //按逻辑序号得到元素
    int get_elem(const int pos);
    //按照元素查找,返回物理序号
    int search_elem(const int e);
    //插入数据
    void insert_elem(const int pos, const int e);
    //删除数据
    void delete_elem(const int pos);

};
//约瑟夫环问题
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
            cout << "插入位置无效" << endl;
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
        cout << "添加成功" << endl;
        system("pause");
    }
    //删除节点,并获得节点的编号，以及密码
    int delete_j(LinkList_node*p,int &outid)
    {
        if (!p || !p->next)
        {
            outid = -1;
            return -1;
        }
        //只能由父类指针指向子类，而不能子类指向父类，但可以用过向下转来实现
        Joseph_node* dele_node = static_cast<Joseph_node*>(p->next);
        outid = dele_node->number;
        int password = dele_node->data;
        p->next = p->next->next;
        delete dele_node;
        this->list->data--;
        cout << "删除成功" << endl;
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
    cout << "输入人员数量:";
    cin >> n;
    for (i = 0;i < n;i++)
    {
        cout << "输入第" << i + 1 << "个人的编号及密码:";
        cin >> id >> password;
        j.insert_j(i + 1, id, password);
    }
    j.make_circle();
    cout << "输入初始密码:";
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
//三种方式交换两个数
void swap_data1(int& x, int& y)
{
    cout << "使用引用交换" << endl;
    int temp;
    temp = x;
    x = y;
    y = temp;
}
void swap_data2(int* x, int* y)
{
    cout << "使用指针交换" << endl;
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void swap_data3(int x, int y)
{
    cout << "值传递交换" << endl;
    int temp = x;
    x = y;
    y = temp;
}
//冒泡排序
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
//快速排序
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
//展示绪论的菜单及实现
void show_menu1()
{
    int select;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t=================用c++语言实现================" << endl;
        cout << "\t\t\t\t********1.使用引用交换两个数的值**************" << endl;
        cout << "\t\t\t\t********2.使用指针交换两个数的值************" << endl;
        cout << "\t\t\t\t********3.使用值传递交换两个数的值**********" << endl;
        cout << "\t\t\t\t********0.返回上级目录**********" << endl;
        cout << "输入操作序号:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "欢迎下次使用,按任意键返回上一级目录" << endl;
            system("pause");
            return;
            break;
        }
        case 1:
        {
            int x, y;
            cout << "输入x的值:";
            cin >> x;
            cout << "输入y的值:";
            cin >> y;
            swap_data1(x, y);
            cout << "交换后x和y的值:" << endl;
            cout << "x=" << x << " " << "y=" << y << endl;
            system("pause");
            break;
        }
        case 2:
        {
            int x, y;
            cout << "输入x的值:";
            cin >> x;
            cout << "输入y的值:";
            cin >> y;
            swap_data2(&x, &y);
            cout << "交换后x和y的值:" << endl;
            cout << "x=" << x << " " << "y=" << y << endl;
            system("pause");
            break;
        }
        case 3:
        {
            int x, y;
            cout << "输入x的值:";
            cin >> x;
            cout << "输入y的值:";
            cin >> y;
            swap_data3(x, y);
            cout << "交换后x和y的值:" << endl;
            cout << "x=" << x << " " << "y=" << y << endl;
            system("pause");
            break;
        }
        default:
        {
            cout << "输入序号错误,请输入正确的序号:" << endl;
            system("pause");
            break;
        }
        }
    }
}
//展示主菜单
void show_menu()
{
    int select;
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t==========数据结构==========" << endl;
        cout << "\t\t\t\t********1.绪论**************" << endl;
        cout << "\t\t\t\t********2.线性表************" << endl;
        cout << "\t\t\t\t********3.排序算法************" << endl;
        cout << "\t\t\t\t********0.退出程序**********" << endl;
        system("pause");
        cout << "输入操作序号:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "欢迎下次使用" << endl;
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
            cout << "输入错误指令,重新输入" << endl;
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
        cout << "\n\t\t\t\t==========排序算法==========" << endl;
        cout << "\t\t\t\t********1.冒泡排序**************" << endl;
        cout << "\t\t\t\t********2.插入排序************" << endl;
        cout << "\t\t\t\t********3.快速排序************" << endl;
        cout << "\t\t\t\t********0.退出程序**********" << endl;
        cout << "输入操作序号:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "欢迎下次使用,按任意键返回上一级目录" << endl;
            system("pause");
            return;
            break;
        }
        case 1:
        {
            int n;
            cout << "输入你要排序的元素数量:";
            cin >> n;
            int* data = new int[n];
            cout << "输入要排序的" << n << "个元素" << endl;
            for (int i = 0;i < n;i++)
            {
                cin >> data[i];
            }
            bubble_sort(data, n);
            cout << "排序后的元素:" << endl;
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
            cout << "输入你要排序的元素数量:";
            cin >> n;
            int* data = new int[n];
            cout << "输入要排序的" << n << "个元素" << endl;
            for (int i = 0;i < n;i++)
            {
                cin >> data[i];
            }
            insert_sort(data, n);
            cout << "排序后的元素:" << endl;
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
            cout << "输入你要排序的元素数量:";
            cin >> n;
            int* data = new int[n];
            cout << "输入要排序的" << n << "个元素" << endl;
            for (int i = 0;i < n;i++)
            {
                cin >> data[i];
            }
            quick_sort(data, 0, n - 1);
            cout << "排序后的元素:" << endl;
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
            cout << "输入序号错误,请输入正确的序号:" << endl;
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
        cout << "\n\t\t\t\t==========线性表==========" << endl;
        cout << "\t\t\t\t********1.顺序表**************" << endl;
        cout << "\t\t\t\t********2.单链表************" << endl;
        cout << "\t\t\t\t********3.约瑟夫环问题************" << endl;
        cout << "\t\t\t\t********0.退出程序**********" << endl;
        cout << "输入操作序号:" << endl;
        cin >> select;
        switch(select)
        {
        case 0:
        {
            cout << "欢迎下次使用,按任意键返回上一级目录" << endl;
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
            cout << "输入序号错误,请输入正确的序号:" << endl;
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
        cout << "\n\t\t\t\t==========顺序表==========" << endl;
        cout << "\t\t\t\t********0.退出程序**************" << endl;
        cout << "\t\t\t\t********1.initial**************" << endl;
        cout << "\t\t\t\t********2.insert_elem************" << endl;
        cout << "\t\t\t\t********3.delete_elem**********" << endl;
        cout << "\t\t\t\t********4.get_length**********" << endl;
        cout << "\t\t\t\t********5.search_elem*********" << endl;
        cout << "\t\t\t\t********6.show_seqlist**********" << endl;
        cout << "\t\t\t\t********7.get_elem**********" << endl;
        cout << "\t\t\t\t********8.destroy_seqlist**********" << endl;
        cout << "输入操作序号:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "欢迎下次使用,按任意键返回上一级目录" << endl;
            system("pause");
            return;
            break;
        }
        case 1:
        {
            int num;
            cout << "输入线性表元素数量:";
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
            cout << "目前线性表长度为:" << l.get_length() << endl;
            cout << "输入插入元素还有位置:";
            cin >> i >> pos;
            l.insert_elem(pos, i);
            break;
        }
        case 3:
        {
            int pos;
            cout << "输入删除元素的逻辑序号:";
            cin >> pos;
            l.delete_elem(pos);
            break;
        }
        case 4:
        {
            cout << "线性表长度为:" << l.get_length() << endl;
            system("pause");
            break;
        }
        case 5:
        {
            int pos;
            cout << "输入要查找元素的值:";
            cin >> pos;
            cout << "查找元素下标为:" << l.search_elem(pos) << endl;
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
            cout << "输入要查找元素逻辑序号:";
            cin >> pos;
            cout << "第" << pos << "个元素为" << l.get_elem(pos) << endl;
            system("pause");
            break;
        }
        case 8:
        {
            l.destroy_seqlist();
            cout << "销毁成功" << endl;
            system("pause");
            break;
        }
        default:
        {
            cout << "输入序号错误,请输入正确的序号:" << endl;
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
        cout << "\n\t\t\t\t==========单链表==========" << endl;
        cout << "\t\t\t\t********0.退出程序**************" << endl;
        cout << "\t\t\t\t********1.initial**************" << endl;
        cout << "\t\t\t\t********2.insert_elem************" << endl;
        cout << "\t\t\t\t********3.delete_elem**********" << endl;
        cout << "\t\t\t\t********4.get_length**********" << endl;
        cout << "\t\t\t\t********5.search_elem*********" << endl;
        cout << "\t\t\t\t********6.show_seqlist**********" << endl;
        cout << "\t\t\t\t********7.get_elem**********" << endl;
        cout << "\t\t\t\t********8.destroy_seqlist**********" << endl;
        cout << "输入操作序号:" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
        {
            cout << "欢迎下次使用,按任意键返回上一级目录" << endl;
            system("pause");
            return;
            break;
        }
        case 1:
        {
            l.initial_list();
            cout << "初始化完成" << endl;
            system("pause");
            break;
        }
        case 2:
        {
            cout << "目前链表元素为:" << endl;
            l.show_list();
            int pos, e;
            cout << "输入插入位置及元素的值(逻辑序号):";
            cin >> pos >> e;
            l.insert_elem(pos, e);
            break;
        }
        case 3:
        {
            cout << "目前链表元素为:" << endl;
            l.show_list();
            int pos;
            cout << "输入删除元素的位置(逻辑序号):";
            cin >> pos;
            l.delete_elem(pos);
            break;
        }
        case 4:
        {
            cout << "线性表长度为:" << l.get_length() << endl;
            system("pause");
            break;
        }
        case 5:
        {
            int e;
            cout << "输入查找元素的值:";
            cin >> e;
            int pos = l.search_elem(e);
            if (pos== -1)
            {
                cout << "未找到元素" << endl;
                system("pause");
                break;
            }
            else
            {
                cout << e << "是第" << pos + 1 << "个元素" << endl;
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
            cout << "输入查找元素的逻辑序号:";
            cin >> pos;
            cout << "第" << pos << "个元素是" << l.get_elem(pos) << endl;
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
//pos是逻辑序号
void SeqList::insert_elem(const int& pos, const int& e)
{
    if (this->data == nullptr)
    {
        cout << "未初始化,请先进行初始化" << endl;
        system("pause");
        return;
    }
    if (pos <= 0 || pos > this->length + 1)
    {
        cout << "插入位置输入错误" << endl;
        system("pause");
        return;
    }
    if (this->length == this->capacity)
    {
        cout << "线性表已经满了,无法插入" << endl;
        system("pause");
    }
    int i;
    for (i = this->length-1;i >= pos - 1;i--)
    {
        this->data[i+1] = data[i];
    }
    this->data[i + 1] = e;
    this->length++;
    cout << "插入成功" << endl;
    system("pause");
}
void SeqList::delete_elem(const int& pos)
{
    if (this->data == nullptr)
    {
        cout << "未初始化,请先进行初始化" << endl;
        system("pause");
        return;
    }
    if (pos <= 0 || pos > this->length)
    {
        cout << "删除位置输入错误" << endl;
        system("pause");
        return;
    }
    int i;
    for (i = pos;i < this->length;i++)
    {
        this->data[i - 1] = this->data[i];
    }
    this->length--;
    cout << "删除成功" << endl;
    system("pause");
}
int SeqList::get_length()
{
    if (this->data == nullptr)
    {
        cout << "未初始化,请先进行初始化" << endl;
        system("pause");
        return-1;
    }
    return this->length;
}
int SeqList::search_elem(const int& e)
{
    if (this->data == nullptr)
    {
        cout << "未初始化,请先进行初始化" << endl;
        system("pause");
        return-1;
    }
    int i = 0;
    while (i < this->length)
    {
        if (this->data[i] == e)
        {
            cout << e << "是线性表中第" << i + 1 << "个元素" << endl;
            system("pause");
            return i;
        }
    }
    cout << "没有找到对应元素" << endl;
    system("pause");
    return -1;
}
void SeqList::show_seqlist()
{
    if (this->data == nullptr)
    {
        cout << "未初始化,请先进行初始化" << endl;
        system("pause");
        return;
    }
    if (this->is_empty())
    {
        cout << "线性表为空" << endl;
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
        cout << "未初始化,请先进行初始化" << endl;
        system("pause");
        return-1;
    }
    if (pos <= 0 || pos > length)
    {
        cout << "查找序号错误" << endl;
        system("pause");
        return-1;
    }
    return this->data[pos - 1];
}
void SeqList::destroy_seqlist()
{
    this->~SeqList();
}
//链表成员函数
LinkList_node::~LinkList_node()
{
    cout << "[节点析构] 释放数据为 " << this->data << " 的节点" << endl;
}

void LinkList::initial_list()
{
    if (this->list != nullptr)
    {
        cout << "请勿重复初始化" << endl;
        system("pause");
        return;
    }
    this->list = new LinkList_node;
}
bool LinkList::is_empty()
{
    if (this->list == nullptr)
    {
        cout << "请先进行初始化" << endl;
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
        cout << "请先进行初始化" << endl;
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
        cout << "请先进行初始化" << endl;
        system("pause");
        return ;
    }
    if (pos <= 0 || pos > this->list->data + 1)
    {
        cout << "插入位置错误" << endl;
        system("pause");
        return;
    }
    LinkList_node* p = this->list;
    int i = 0;
    //循环到第pos-1个节点
    while (p && i < pos-1)
    {
        p = p->next;
        i++;
    }
    if (!p)
    {
        cout << "插入位置错误" << endl;
        system("pause");
        return;
    }
    LinkList_node* q = new LinkList_node;
    q->next = p->next;
    p->next = q;
    q->data = e;
    this->list->data++;
    cout << "添加成功" << endl;
    system("pause");
}
void LinkList::delete_elem(const int pos)
{
    if (this->list == nullptr)
    {
        cout << "请先进行初始化" << endl;
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
        cout << "删除位置错误" << endl;
        system("pause");
        return;
    }
    LinkList_node* temp = p->next;
    p->next = temp->next;
    delete temp;
    this->list->data--;
    cout << "删除成功" << endl;
    system("pause");
}
void LinkList::show_list()
{
    if (this->list == nullptr)
    {
        cout << "请先进行初始化" << endl;
        system("pause");
        return;
    }
    if (this->is_empty())
    {
        cout << "链表为空" << endl;
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
        cout << "请先进行初始化" << endl;
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
        cout << "请先进行初始化" << endl;
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
        cout << "查询位置错误" << endl;
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
        cout << "请先进行初始化" << endl;
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
    cout << "销毁完成" << endl;
    system("pause");
}
