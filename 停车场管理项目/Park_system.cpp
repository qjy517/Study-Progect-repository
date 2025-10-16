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
		cout << "\t\t\t\t当前利率为" << Rate << "\t\t\t\t" << endl;
		cout << "\t\t\t\t欢迎来到停车场管理系统\t\t\t\t" << endl;
		cout << "\t\t\t\t0.退出系统\t\t\t\t" << endl;
		cout << "\t\t\t\t1.车辆驶入\t\t\t\t" << endl;
		cout << "\t\t\t\t2.车辆驶出\t\t\t\t" << endl;
		cout << "\t\t\t\t3.查看停车场车辆信息\t\t\t\t" << endl;
		cin >> select;
		switch (select)
		{
		case 0:
		{
			cout << "欢迎下次使用!!!!" << endl;
			exit(0);
			break;
		}
		case 1:
		{
			Car e_car;
			cout << "输入驶入车辆的车牌号以及驶入时间：";
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
			cout << "输入驶离的车牌号以及驶离时间:";
			cin >> str >> q_time;
			q_car.tag = str;
			if (park_system.quick(q_car))
			{
				cout << "驶出车辆为：" << endl;
				cout << q_car.tag << "    " << "驶入时间:" << q_car.e_time << "     " << "驶离时间:" << q_time << endl;
				cout << "应付金额:" << (q_time - q_car.e_time) * Rate << endl;
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