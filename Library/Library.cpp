#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class Patron;//提前声明

class Book
{
public:
	Book()
	{
		patron = nullptr;//一开始借书为nullptr
	}
	bool operator==(const Book& book) const
	{
		return strcmp(title, book.title)==0;
	}
private:
	//书名
	char* title;
	//借书的人
	Patron* patron;
	//重载左移运算符，注意只有const对象才能调用const函数
	ostream& printBook(ostream& os) const;
	//如果不声明为友元就会有三个参数，一个this，一个os，一个bk，但是<<只有两个参数
	friend ostream& operator<<(ostream& os, const Book& bk)
	{
		return bk.printBook(os);
	}
	//友元声明与函数位置无关，只是表明这个类所有成员对此函数可见
	friend class CheckOutBook;
	friend class Patron;
	friend void includeBook();
	friend void checkOutBook();
	friend void returnBook();
};
class Author
{
public:
	Author()
	{
		//空
	}
	bool operator==(const Author& ar) const
	{
		return strcmp(this->name, ar.name)==0;
	}
private:
	char* name;
	list<Book> books;
	//重载<<
	ostream& printAuthor(ostream&) const;
	friend ostream& operator<<(ostream& os, const Author& ar)
	{
		return ar.printAuthor(os);
	}
	friend void includeBook();
	friend void returnBook();
	friend void checkOutBook();
	friend class CheckOutBook;//借阅记录实体
	friend class Patron;
	friend class Book;
};
class CheckOutBook
{
public:
	CheckOutBook(list<Author>::iterator ar,list<Book>::iterator bk)
	{
		this->author = ar;
		this->book = bk;
	}
	bool operator==(const CheckOutBook& bk) const
	{
		return (strcmp(this->author->name, bk.author->name) == 0) && (strcmp(this->book->title, bk.book->title) == 0);
	}
private:
	list<Author>::iterator author;
	list<Book>::iterator book;
	friend void checkOutBook();
	friend void returnBook();
	friend class Patron;
};
class Patron
{
public:
	Patron()
	{

	}
	bool operator==(const Patron& po) const 
	{
		return strcmp(this->name, po.name) == 0;
	}
private:
	char* name;
	list<CheckOutBook> books;
	ostream& printPatron(ostream& os) const;
	friend ostream& operator<<(ostream& os, const Patron& pn)
	{
		return pn.printPatron(os);
	}
	friend void checkOutBook();
	friend void returnBook();
	friend class Book;
};
list<Author> catalog['z' + 1];
list<Patron> people['z' + 1];
ostream& Author::printAuthor(ostream& out) const
{
	out << name << endl;
	list<Book>::const_iterator ref = books.begin();
	for (;ref != books.end();ref++)
	{
		out << *ref;//重载函数,book
	}
	return out;
}
ostream& Book::printBook(ostream& os) const
{
	os << "*" << this->title;
	if (this->patron != nullptr)
	{
		os << " - checked out to " << patron->name;
	}
	os << endl;
	return os;
}
ostream& Patron::printPatron(ostream& os) const 
{
	os << this->name;
	if (!this->books.empty())
	{
		os << " has the following books:" << endl;
		list<CheckOutBook>::const_iterator bk = this->books.begin();
		for (;bk != this->books.end();bk++)
		{
			os << " * " << bk->author->name << " , " << bk->book->title << endl;
		}
	}
	else
	{
		os << " has no book" << endl;
	}
	return os;
}
template<class T>
ostream& operator<<(ostream& os, const list<T>& lst)
{
	typename list<T>::const_iterator ref = lst.begin();
	for (;ref != lst.end();ref++)
	{
		os << *ref;
	}
	return os;
}
char* getString(const char* msg)
{
	char s[82], i, * destin;
	cout << msg;
	cin.get(s, 80);
	while (cin.get(s[81]) && s[81] != '\n');
	destin = new char[strlen(s) + 1];
	//将目标设置为大写
	for (i = 0;destin[i] = s[i];i++);
	destin[0] = toupper(s[0]);
	return destin;
}
void status()
{
	register int i;
	cout << " Library has the following boks:\n\n ";
	for (i = 'A';i <= 'Z';i++)
	{
		if (!catalog[i].empty())
		{
			cout << catalog[i];
		}
	}
	cout << "\nThe following prple are using the library:\n\n";
	for (i = 'A';i <= 'Z';i++)
	{
		if (!people[i].empty())
		{
			cout << people[i];
		}
	}

}
void includeBook()
{
	Author newAuthor;
	Book newBook;
	newAuthor.name = getString("Enter author's name: ");
	newBook.title = getString("Enter book's title: ");
	list<Author>::iterator oldAuthor = find(catalog[newAuthor.name[0]].begin(), catalog[newAuthor.name[0]].end(), newAuthor);
	if (oldAuthor != catalog[newAuthor.name[0]].end())
	{
		(*oldAuthor).books.push_front(newBook);
	}
	else
	{
		newAuthor.books.push_front(newBook);
		catalog[newAuthor.name[0]].push_front(newAuthor);
	}
}
void checkOutBook()
{
	Author author;
	Book book;
	Patron patron;
	list<Author>::iterator authorRef;
	list<Book>::iterator bookRef;
	patron.name = getString("Enter the patron's name: ");
	while (true)
	{
		author.name = getString("Enter the author's name: ");
		authorRef = find(catalog[author.name[0]].begin(), catalog[author.name[0]].end(), author);
		if (authorRef == catalog[author.name[0]].end())
		{
			cout << "Misspelled author's name" << endl;
		}
		else
		{
			break;
		}
	}
	while (true)
	{
		book.title = getString("Enter the book's title: ");
		bookRef = find((*authorRef).books.begin(), (*authorRef).books.end(), book);
		if (bookRef == (*authorRef).books.end())
		{
			cout << "Misspelled book's name" << endl;
		}
		else
		{
			break;
		}
	}
	list<Patron>::iterator patronRef;
	CheckOutBook checkBook_infor(authorRef, bookRef);
	patronRef = find(people[patron.name[0]].begin(), people[patron.name[0]].end(), patron);
	if (patronRef == people[patron.name[0]].end())
	{
		patron.books.push_front(checkBook_infor);
		people[patron.name[0]].push_front(patron);
		(*bookRef).patron = &(*people[patron.name[0]].begin());
	}
	else
	{
		(*patronRef).books.push_front(checkBook_infor);
		(*bookRef).patron = &(*patronRef);
	}
}
void returnBook()
{
	Patron patron;
	Book book;
	Author author;
	list<Patron>::iterator patronRef;
	list<Book>::iterator bookRef;
	list<Author>::iterator authorRef;
	while (true)
	{
		patron.name = getString("Enter the patron's name: ");
		patronRef = find(people[patron.name[0]].begin(), people[patron.name[0]].end(), patron);
		if (patronRef == people[patron.name[0]].end())
		{
			cout << "Misspelled patron's name" << endl;
		}
		else
		{
			break;
		}
	}
	while (true)
	{
		author.name = getString("Enter the author's name: ");
		authorRef = find(catalog[author.name[0]].begin(), catalog[author.name[0]].end(), author);
		if (authorRef == catalog[author.name[0]].end())
		{
			cout << "Misspelled author's name" << endl;
		}
		else
		{
			break;
		}
	}
	while (true)
	{
		book.title = getString("Enter the book's name: ");
		bookRef = find((*authorRef).books.begin(), (*authorRef).books.end(), book);
		if (bookRef == (*authorRef).books.end())
		{
			cout << "Misspelled book's name" << endl;
		}
		else
		{
			break;
		}
	}
	CheckOutBook checkBook_infor(authorRef, bookRef);
	(*patronRef).books.remove(checkBook_infor);
	(*bookRef).patron = nullptr;
}
int menu()
{
	int option;
	cout << "\nEnter one of the following options:\n"
		<< "1. Include a book in the catalog\n"
		<< "2. Check out a book\n"
		<< "3. Return a book\n"
		<< "4. Status\n"
		<< "5. Exit\n"
		<< "Your option?";
	cin >> option;
	cin.get();
	return option;
}
int main()
{
	while (true)
	{
		system("cls");
		int option = menu();
		switch (option)
		{
		case 1:includeBook();system("pause");break;
		case 2:checkOutBook();system("pause"); break;
		case 3:returnBook();system("pause"); break;
		case 4:status();system("pause");break;
		case 5:system("pause");exit(0);break;
		}
	}
}
