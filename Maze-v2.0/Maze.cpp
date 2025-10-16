#include <iostream>
#include <string>
#include <stack>
#include "Maze.h"
using namespace std;

//���캯�����ֶ�����һ���Թ�,ֵ��ѧϰ��ι���ģ��Լ�ʹ��wall��path�ȱ�Ǳ�������߿�ά�����׶���
Maze::Maze() :wall('1'), path('0'), entranceMarker('m'), exitMarker('e'), visited('.')
{
	Stack<char*> mazeRows;
	char str[80], * s;
	int col, row = 0;
	cout << "Enter a rectangular maze using the following "
		<< "characters:\nm - entrance\ne - exit\n1 - wall\n0 - path"
		<< endl;
	while (cin >> str)
	{
		row++;
		cols = strlen(str);
		s = new char[cols + 3];
		mazeRows.push(s);
		strcpy_s(s + 1, cols + 1, str);
		s[0] = s[cols + 1] = wall;
		s[cols + 2] = '\0';
		if (strchr(s, exitMarker) != nullptr)
		{
			exitBlock.x = row;
			exitBlock.y = strchr(s, exitMarker) - s;
		}
		if (strchr(s, entranceMarker) != nullptr)
		{
			entranceBlock.x = row;
			entranceBlock.y = strchr(s, entranceMarker) - s;
		}
	}
	rows = row + 2;
	map = new char* [rows];
	map[0] = new char[cols + 3];
	for (;!mazeRows.empty();row--)
	{
		map[row] = mazeRows.pop();
	}
	map[rows - 1] = new char[cols + 3];
	map[0][cols + 2] = map[rows - 1][cols + 2] = '\0';
	for (col = 0;col <= cols + 1;col++)
	{
		map[0][col] = wall;
		map[rows - 1][col] = wall;
	}
	cols = cols + 2;
}

Maze::~Maze()
{
	for (int i = 0;i < rows;i++)
	{
		if (map[i] != nullptr)
		{
			delete[]map[i];
			map[i] = nullptr;
		}
	}
	delete[]map;
}


//���ĺ����������߳��Թ������������·��
//ע������ǽ���ǰ�������һ�����߷���ѹ��ջ�У�ǰ���ǵ�ǰ��������ջ�У������Ϊ�ѷ��ʡ�
//��һ��˼·���жϵ�ǰ�����Ƿ��п��ߵ���һ�����飬����У��ǽ���ǰ����ѹ��ջ�У���ǰ����Ϊ�ѷ���
//�����ʵ�Ϊǰ�ߣ���Ϊ��������Ƚ����ѹ��ջ�е�ǰ������������currBlock=��ڣ�Ҫ����һ�����߿���ջ��
// ����ǰ�ߣ�����Ǻ��ߣ��ͻ��ظ��������ջ
void Maze::exitMaze()
{
	int count = 0;
	mazeStack.push(entranceBlock);
	mazeBlock currBlock;
	mazeBlock nextBlock;
	while (!mazeStack.empty())
	{
		currBlock = mazeStack.top();
		if (currBlock == exitBlock)
		{
			count++;
			cout << "��" << count << "��·����" << endl;
			//��ӡ�Թ�
			map[currBlock.x][currBlock.y] = exitMarker;
			cout << *this << endl;
			//����
			mazeStack.pop();
			continue;
		}
		if(findNextBlock(&nextBlock,&currBlock))
		{
			//����Ҫ����ջ�е�dir��currBlockֻ��һ���ֲ��������������ݵ�ʱ��dir�Ų�����������ظ���Χ����ѭ��
			mazeStack.pop();
			mazeStack.push(currBlock);//�����º��currBlick��ջ
			mazeStack.push(nextBlock);
			map[nextBlock.x][nextBlock.y] = visited;
		}
		else
		{
			map[currBlock.x][currBlock.y] = path;
			mazeStack.pop();
		}
	}
	cout << "total:" << count << endl;
}

bool Maze::findNextBlock(mazeBlock* nextBlock, mazeBlock* currBlock)
{
	for (int i = currBlock->dir + 1;i < 4;i++)
	{
		//�ؼ����ǣ�ÿ��ѭ��Ҫ���»ص�ԭ����ֵ��Ҫ��Ȼ�ͻᵼ��x��y����
		int x = currBlock->x;
		int y = currBlock->y;
		switch (i)
		{
		case 0:
		{
			x -= 1;
			break;
		}
		case 1:
		{
			y += 1;
			break;
		}
		case 2:
		{
			x += 1;
			break;
		}
		case 3:
		{
			y -= 1;
			break;
		}
		}
		if (judgeBlock(mazeBlock(x, y)))
		{
			currBlock->dir = i;
			nextBlock->x = x;
			nextBlock->y = y;
			nextBlock->dir = -1;
			return true;
		}
	}
	return false;
}

ostream& Maze::printMaze(ostream& os) const
{
	//��Ҫ���ı�ԭ���ĵ�ͼ����Ҫʹ�ø���������
	Stack<mazeBlock> tempStack = this->mazeStack;
	char** temp = new char* [rows];
	for (int i = 0;i < rows;i++)
	{
		temp[i] = new char[cols];
		for (int j = 0;j < cols;j++)
		{
			temp[i][j] = map[i][j];
		}
	}
	int x, y,d;
	mazeBlock tempBlock;
	while (!tempStack.empty())
	{
		tempBlock = tempStack.pop();
		x = tempBlock.x;
		y = tempBlock.y;
		d = tempBlock.dir;
		switch (d)
		{
		case 0:temp[x][y] = '^';break;
		case 1:temp[x][y] = '>';break;
		case 2:temp[x][y] = 'v';break;
		case 3:temp[x][y] = '<';break;
		}
	}
	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			os << temp[i][j] << " ";
		}
		os << endl;
	}
	for (int i = 0;i < rows;i++)
	{
		if (temp[i] != nullptr)
		{
			delete[]temp[i];
			temp[i] = nullptr;
		}
	}
	delete[]temp;
	return os;
}

bool Maze::judgeBlock(mazeBlock block)
{
	int x = block.x;
	int y = block.y;
	if (map[x][y] == wall || map[x][y] == visited || map[x][y] == entranceMarker)
	{
		return false;
	}
	return true;
}