#pragma once
//主要练习，与c兼容，面型对象的三大程序思想，文件流
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class Person
{
public:
	//构造函数
	//五个成员：社会安全号码，姓名，城市，出生年份，薪水
	Person();
	Person(char*, char*, char*, int, long);
	//向文件读,写信息
	void writeToFile(fstream &) const;//const表示函数不改变成员变量
	void readFromFile(fstream&);
	//读取社会号码
	void readKey();
	//读取文件数据是，如何确定从一条记录移动到下一条记录，只需确定每一条记录的大小即可，统一规定记录的大小
	int size() const
	{
		return 9 + nameLen + cityLen + sizeof(year) + sizeof(salary);
	}
	//用来查找时判断是否与目标相同
	bool operator==(const Person& pr)
	{
		//利用cstring函数
		return strncmp(pr.SSN, SSN, 9) == 0;
	}
protected:
	//规定Len就是统一记录的长度
	const int nameLen, cityLen;
	char SSN[10], * name, * city;
	int year;
	long salary;
	//从终端读取数据,理解两两函数组合的意思
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