#pragma once
#include <iostream>
#include <stack>
using namespace std;

//重载标准库的pop使其返回值，注意书写格式
template<class T>
class Stack :public stack<T>
{
public:
	T pop()
	{
		T temp = stack<T>::top();
		stack<T>::pop();
		return temp;
	}
};

//路线的基本元素，如果要输出全部的路线，那就要记录每个元素的探索方向，避免重复探索
//单个路线可以忽略，或者使用递归
class mazeBlock
{
public:
	mazeBlock() :dir(-1){}
	mazeBlock(int m_x, int m_y):x(m_x),y(m_y),dir(-1){}
private:
	int x;
	int y;
	int dir;
	friend class Maze;
	bool operator==(const mazeBlock& block)
	{
		return (x == block.x) && (y == block.y);
	}
	mazeBlock& operator=(const mazeBlock& block)
	{
		x = block.x;
		y = block.y;
		dir = block.dir;
		return *this;
	}
};

//迷宫类，核心功能：手动构造迷宫，输出全部路径
class Maze
{
public:
	//手动输入迷宫,构造函数
	Maze();
	~Maze();
	//核心函数用来走出迷宫,并维护多条路径
	void exitMaze();
	//封装，利用<<来输出迷宫图像
	friend ostream& operator<<(ostream& os, const Maze& maze)
	{
		return maze.printMaze(os);
	}
private:
	//用来存放路径
	Stack<mazeBlock> mazeStack;
	//迷宫
	char** map;
	//迷宫属性
	int rows;
	int cols;
	//标记墙还有路，出入口；
	char wall, path, entranceMarker, exitMarker,visited;
	//迷宫的出入口
	mazeBlock entranceBlock, exitBlock;
	//判断当前方块是否可以走
	bool judgeBlock(mazeBlock block);
	//判断能否找到下一个可走方块
	bool findNextBlock(mazeBlock* nextBlock,mazeBlock* currBlock);
	//重载打印函数，可以使用<<来打印出迷宫
	ostream& printMaze(ostream& os) const;

};