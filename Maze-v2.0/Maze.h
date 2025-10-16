#pragma once
#include <iostream>
#include <stack>
using namespace std;

//���ر�׼���popʹ�䷵��ֵ��ע����д��ʽ
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

//·�ߵĻ���Ԫ�أ����Ҫ���ȫ����·�ߣ��Ǿ�Ҫ��¼ÿ��Ԫ�ص�̽�����򣬱����ظ�̽��
//����·�߿��Ժ��ԣ�����ʹ�õݹ�
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

//�Թ��࣬���Ĺ��ܣ��ֶ������Թ������ȫ��·��
class Maze
{
public:
	//�ֶ������Թ�,���캯��
	Maze();
	~Maze();
	//���ĺ��������߳��Թ�,��ά������·��
	void exitMaze();
	//��װ������<<������Թ�ͼ��
	friend ostream& operator<<(ostream& os, const Maze& maze)
	{
		return maze.printMaze(os);
	}
private:
	//�������·��
	Stack<mazeBlock> mazeStack;
	//�Թ�
	char** map;
	//�Թ�����
	int rows;
	int cols;
	//���ǽ����·������ڣ�
	char wall, path, entranceMarker, exitMarker,visited;
	//�Թ��ĳ����
	mazeBlock entranceBlock, exitBlock;
	//�жϵ�ǰ�����Ƿ������
	bool judgeBlock(mazeBlock block);
	//�ж��ܷ��ҵ���һ�����߷���
	bool findNextBlock(mazeBlock* nextBlock,mazeBlock* currBlock);
	//���ش�ӡ����������ʹ��<<����ӡ���Թ�
	ostream& printMaze(ostream& os) const;

};