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
				//退出管理程序
				cout << "欢迎下次使用" << endl;
				exit(0);
			}	
			case 1:
			{
				//添加职员
				worker.add_worker();
				break;
			}
			case 2:
			{
				//删除职员
				worker.delete_worker();
				break;
			}
			case 3:
			{
				//查找职员
				worker.find_worker();
				break;
			}
			case 4:
			{
				//修改职员
				worker.reverse_worker();
				break;
			}
			case 5:
			{
				//显示职员
				worker.show_worker();
				break;
			}
			case 6:
			{
				//按照编号排序
				worker.sort_worker();
				break;
			}
			case 7:
			{
				//清空所有文档
				break;
			}
		}
	}
	return 0;
}