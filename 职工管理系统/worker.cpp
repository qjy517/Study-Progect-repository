#include <iostream>
#include "system.h"
#include "base.h"
#include <string>
using namespace std;
int main()
{
	int select;
	System worker;
	while (true)
	{
		worker.show_maneu();
		system("pause");
		cin >> select;
		switch (select)
		{
			case 0:
			{
				//�˳��������
				cout << "��ӭ�´�ʹ��" << endl;
				exit(0);
			}	
			case 1:
			{
				//���ְԱ
				worker.add_worker();
				break;
			}
			case 2:
			{
				//ɾ��ְԱ
				worker.delete_worker();
				break;
			}
			case 3:
			{
				//����ְԱ
				worker.find_worker();
				break;
			}
			case 4:
			{
				//�޸�ְԱ
				worker.reverse_worker();
				break;
			}
			case 5:
			{
				//��ʾְԱ
				worker.show_worker();
				break;
			}
			case 6:
			{
				//���ձ������
				worker.sort_worker();
				break;
			}
			case 7:
			{
				//��������ĵ�
				break;
			}
		}
	}
	return 0;
}