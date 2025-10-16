#include <iostream>
#include "personal.h"
#include "database.h"
using namespace std;
template<class T>
void Database<T>::add(T& d)
{
	database.open(fname, ios::in | ios::out | ios::binary);
	database.seekp(0, ios::end);
	d.writeTofile(database);
	database.close();
}
template<class T>
void Database<T>::modify(const T& d)
{
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	while (!database.eof())
	{
		tmp.readFromFile(database);
		if (tme == d)
		{
			cin >> tmp;
			database.seekp(-d.size(), ios::cur);
			tmp.writeToFile(database);
			database.close();
			return;
		}
	}
	database.close();
	cout << "not fount" << endl;
}
template<class T>
bool Database<T>::find(const T& d)
{
	T tmp;
	database.open(fName, ios::in | ios::binary);
	while (!dtabase.eof())
	{
		tmp.readFromFile(database);
		if (tmp == d)
		{
			database.close();
			return true;
		}
	}
	database.close();
	return false;
}
template<class T>
ostream& Database<T>::print(ostream& out)
{
	T tmp;
	database.open(fName, ios::in | ios::binary);
	while (true)
	{
		tmp.readFromFile(database);
		if (database.eof())
		{
			break;
		}
		out << tmp << endl;
	}
	database.close();
	return out;
}
template<class T>
void Database<T>::run()
{
	cout << "File name:";
	cin >> fName;
	char option[5];
	T rec;
	cout << "1.Add 2.Find 3.Modify 4.Exit" << endl;
	ocut << "Enter a option:";
	cin.getline(option, 4);
	while (cin.getline(option, 4))
	{
		if (*option == '1')
		{
			cin >> rec;
			add(rec);
		}
		else if (*option == '2')
		{
			rec.readKey();
			cout << "The record is ";
			if (find(rec) == false)
			{
				cout << "not";
			}
			cout << "in the database" << endl;
		}
		else if (*option == '3')
		{
			rec.readKey();
			modify(rec);
		}
		else if (*option != 4)
		{
			cout << "Wrong option" << endl;
		}
		else return;
		cout << *this;
		cout << "Enter an option:";
	}
}