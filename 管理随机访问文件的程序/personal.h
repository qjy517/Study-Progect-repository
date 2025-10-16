#pragma once
//��Ҫ��ϰ����c���ݣ����Ͷ�����������˼�룬�ļ���
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class Person
{
public:
	//���캯��
	//�����Ա����ᰲȫ���룬���������У�������ݣ�нˮ
	Person();
	Person(char*, char*, char*, int, long);
	//���ļ���,д��Ϣ
	void writeToFile(fstream &) const;//const��ʾ�������ı��Ա����
	void readFromFile(fstream&);
	//��ȡ������
	void readKey();
	//��ȡ�ļ������ǣ����ȷ����һ����¼�ƶ�����һ����¼��ֻ��ȷ��ÿһ����¼�Ĵ�С���ɣ�ͳһ�涨��¼�Ĵ�С
	int size() const
	{
		return 9 + nameLen + cityLen + sizeof(year) + sizeof(salary);
	}
	//��������ʱ�ж��Ƿ���Ŀ����ͬ
	bool operator==(const Person& pr)
	{
		//����cstring����
		return strncmp(pr.SSN, SSN, 9) == 0;
	}
protected:
	//�涨Len����ͳһ��¼�ĳ���
	const int nameLen, cityLen;
	char SSN[10], * name, * city;
	int year;
	long salary;
	//���ն˶�ȡ����,�������������ϵ���˼
	ostream& writeLegibly(ostream&);
	friend ostream& operator<<(ostream& out, Person& pr)
	{
		return pr.writeLegibly(out);
	}
	istream& readFromConsole(istream&);
	friend istream& operator>>(istream& in, Person& pr)
	{
		return pr.readFromConsole(in);
	}
};