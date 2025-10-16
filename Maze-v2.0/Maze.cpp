#include <iostream>
#include <string>
#include <stack>
#include "Maze.h"
using namespace std;

//构造函数，手动构造一个迷宫,值得学习如何构造的，以及使用wall，path等标记变量，提高可维护型易读性
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


//核心函数，用来走出迷宫并且输出所有路径
//注意核心是将当前方块的下一个可走方块压入栈中，前提是当前方块已在栈中，并标记为已访问。
//另一种思路是判断当前方块是否有可走的下一个方块，如果有，是将当前方块压入栈中，当前块标记为已访问
//更合适的为前者，因为这更符合先将入口压入栈中的前提条件，这里currBlock=入口，要将下一个可走块入栈，
// 符合前者，如果是后者，就会重复将入口入栈
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
			cout << "第" << count << "条路径：" << endl;
			//打印迷宫
			map[currBlock.x][currBlock.y] = exitMarker;
			cout << *this << endl;
			//回溯
			mazeStack.pop();
			continue;
		}
		if(findNextBlock(&nextBlock,&currBlock))
		{
			//这里要更新栈中的dir，currBlock只是一个局部变量，这样回溯的时候dir才不会出错，导致重复范围，死循环
			mazeStack.pop();
			mazeStack.push(currBlock);//将更新后的currBlick入栈
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
		//关键就是，每次循环要更新回到原来的值，要不然就会导致x，y都变
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
	//想要不改变原来的地图，就要使用副本来操作
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