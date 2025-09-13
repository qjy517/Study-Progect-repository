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
	//���캯��
	System();
	//��������
	~System();
	//��ȡ�ļ���ְԱ����
	int get_num();
	//��ʼ��workerָ��
	void initial();
	//���������ݱ��浽�ļ���
	void save();
	//ȷ��id��һ�޶�
	bool id_unique(string &id);
	//��ʾ�˵�
	void show_maneu();
	//���ְ��
	void add_worker();
	//ɾ��ְ��
	void delete_worker();
	//����Ŀ����������±�
	int search_worker(const string &id);
	//�޸�ְ��
	void reverse_worker();
	//���ձ������
	void sort_worker();
	//����ְ��
	void find_worker();
	//��ʾ����ְ��
	void show_worker();
	//��������ĵ�
	void clear_worker();
};