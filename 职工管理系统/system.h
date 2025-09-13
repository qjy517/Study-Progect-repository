#pragma once
#include <iostream>
#include <string>
#include "base.h"
using namespace std;
class System
{
public:
	bool is_empty = true;
	int worker_number;
	Base** worker;
	//构造函数
	System();
	//析构函数
	~System();
	//获取文件中职员数量
	int get_num();
	//初始化worker指针
	void initial();
	//将堆区数据保存到文件中
	void save();
	//确定id独一无二
	bool id_unique(string &id);
	//显示菜单
	void show_maneu();
	//添加职工
	void add_worker();
	//删除职工
	void delete_worker();
	//查找目标人物，返回下标
	int search_worker(const string &id);
	//修改职工
	void reverse_worker();
	//按照编号排序
	void sort_worker();
	//查找职工
	void find_worker();
	//显示所有职工
	void show_worker();
	//清空所有文档
	void clear_worker();
};