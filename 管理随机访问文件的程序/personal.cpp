#include <iostream>
#include "personal.h"
//初始长度,默认初始化
Person::Person() :nameLen(10), cityLen(10)
{
	this->name = new char[nameLen + 1];
	this->city = new char[cityLen + 1];
}
Person::Person(char* ssn, char* n, char* c, int y, long s):nameLen(10),cityLen(10)
{
	name = new char[nameLen + 1];
	city = new char[cityLen + 1];
	strcpy(SSN, ssn);
	strcpy(name, n);
	strcpy(city, c);
	this->year = y;
	this->salary = s;
}
void Person::writeToFile(fstream& out) const
{
	out.write(SSN, 9);
	out.write(name,nameLen);
	out.write(city, cityLen);
	out.write(reinterpret_cast<const char*>(&year),sizeof(int));
	out.write(reinterpret_cast<const char*>(&salary), sizeof(int));
}
void Person::readFromFile(fstream& in)
{
	in.read(SSN, 9);
	in.read(name, nameLen);
	in.read(city, cityLen);
	in.read(reinterpret_cast<char*>(&year), sizeof(int));
	in.read(reinterpret_cast<char*>(&year), sizeof(int));
}
void Person::readKey()
{
	char ssn[80];
	cout << "Enter SSN";
	cin.getline(ssn, 80);
	strncpy(SSN, ssn, 9);
}
ostream& Person::writeLegibly(ostream& out)
{
	SSN[9] = name[nameLen] = city[cityLen] = '\0';
	cout << "SSN = " << SSN << ", name = " << name << ", city = " << city << ", year = " << year << ", salary = " << salary << endl;
	return out;
}
istream& Person::readFromConsole(istream& is)
{
	SSN[9] = name[nameLen] = city[cityLen] = '\0';
	char s[80];
	cout << "SSN:";
	is.getline(s, 80);
	strncpy(SSN, s, 9);
	cout << "Name:";
	is.getline(s, 80);
	strncpy(name, s, nameLen);
	cout << "City:";
	is.getline(s, 80);
	strncpy(city, s, cityLen);
	cout << "Birthyear:";
	is >> year;
	cout << "Salary:";
	is >> salary;
	is.ignore();
	return is;
}