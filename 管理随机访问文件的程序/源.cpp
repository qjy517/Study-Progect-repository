#include <iostream>
#include "database.h"
#include "personal.h"
using namespace std;
int main()
{
	Database<Person>().run;
	return 0;
}  