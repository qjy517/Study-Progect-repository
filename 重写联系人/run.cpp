#include <iostream>
#include <string>
#include "system.h"
#include "person.h"
using namespace std;
int main()
{
    System book;
    int select;
    while (true)
    {
        book.show_meanu();
        cin >> select;
        switch (select)
        {
        case 1://添加联系人
        {
            book.add_person();
            break;
        }
        case 2://删除联系人
        {
            book.delete_person();
            break;
        }
        case 3://显示联系人
        {
            book.look_person();
            break;
        }
        case 4://查找联系人
        {
            book.find_person();
            break;
        }
        case 5://修改联系人
        {
            book.reverse_person();
            break;
        }
        case 6://清空联系人
        {
            break;
        }
        case 0://退出系统
        {
            cout << "欢迎下次使用" << endl;
            system("pause");
            exit(0);
        }
        default:
        {
            cout << "输入正确的指令" << endl;
            system("pause");
            break;
        }
        }
    }
    return 0;
}