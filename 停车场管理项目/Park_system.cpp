#include <iostream>
#include "park.h"
#define Rate 2
using namespace std;
int main()
{
	Park park_system;
	int select;
	while (true)
	{
		system("cls");
		cout << "\t\t\t\t��ǰ����Ϊ" << Rate << "\t\t\t\t" << endl;
		cout << "\t\t\t\t��ӭ����ͣ��������ϵͳ\t\t\t\t" << endl;
		cout << "\t\t\t\t0.�˳�ϵͳ\t\t\t\t" << endl;
		cout << "\t\t\t\t1.����ʻ��\t\t\t\t" << endl;
		cout << "\t\t\t\t2.����ʻ��\t\t\t\t" << endl;
		cout << "\t\t\t\t3.�鿴ͣ����������Ϣ\t\t\t\t" << endl;
		cin >> select;
		switch (select)
		{
		case 0:
		{
			cout << "��ӭ�´�ʹ��!!!!" << endl;
			exit(0);
			break;
		}
		case 1:
		{
			Car e_car;
			cout << "����ʻ�복���ĳ��ƺ��Լ�ʻ��ʱ�䣺";
			cin >> e_car;
			park_system.enter(e_car);
			system("pause");
			break;
		}
		case 2:
		{
			Car q_car;
			string str;
			double q_time;
			cout << "����ʻ��ĳ��ƺ��Լ�ʻ��ʱ��:";
			cin >> str >> q_time;
			q_car.tag = str;
			if (park_system.quick(q_car))
			{
				cout << "ʻ������Ϊ��" << endl;
				cout << q_car.tag << "    " << "ʻ��ʱ��:" << q_car.e_time << "     " << "ʻ��ʱ��:" << q_time << endl;
				cout << "Ӧ�����:" << (q_time - q_car.e_time) * Rate << endl;
			}
			system("pause");
			break;
		}
		case 3:
		{
			park_system.show();
			system("pause");
			break;
		}
		}

	}
}