#pragma once
#include <iostream>
#include <vector>
#include "person.h"
#include <string>
using namespace std;
class System
{
public:
    //����ϵͳ��vector����������Ա
    vector<Person> v;
    //��ʾ�˵�
    void show_meanu();
    //�����Ա
    void add_person();
    //ɾ����Ա
    void delete_person();
    //������Ա
    void find_person();
    //�޸���Ա
    void reverse_person();
    //��ʾ������Ա
    void look_person();
    //�����ϵ��
    void clear_person();
    //����Ҫ���ҵĶ���ĵ�����
    vector<Person>::iterator search_person(const string &name);

};