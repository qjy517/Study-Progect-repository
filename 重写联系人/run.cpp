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
        case 1://�����ϵ��
        {
            book.add_person();
            break;
        }
        case 2://ɾ����ϵ��
        {
            book.delete_person();
            break;
        }
        case 3://��ʾ��ϵ��
        {
            book.look_person();
            break;
        }
        case 4://������ϵ��
        {
            book.find_person();
            break;
        }
        case 5://�޸���ϵ��
        {
            book.reverse_person();
            break;
        }
        case 6://�����ϵ��
        {
            break;
        }
        case 0://�˳�ϵͳ
        {
            cout << "��ӭ�´�ʹ��" << endl;
            system("pause");
            exit(0);
        }
        default:
        {
            cout << "������ȷ��ָ��" << endl;
            system("pause");
            break;
        }
        }
    }
    return 0;
}