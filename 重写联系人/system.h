#pragma once
#include <iostream>
#include <vector>
#include "person.h"
#include <string>
using namespace std;
class System
{
public:
    //管理系统用vector容器管理人员
    vector<Person> v;
    //显示菜单
    void show_meanu();
    //添加人员
    void add_person();
    //删除人员
    void delete_person();
    //查找人员
    void find_person();
    //修改人员
    void reverse_person();
    //显示所有人员
    void look_person();
    //清空联系人
    void clear_person();
    //返回要查找的对象的迭代器
    vector<Person>::iterator search_person(const string &name);

};