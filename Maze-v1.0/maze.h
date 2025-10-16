#pragma once
#include <stack>
#include <iostream>
using namespace std;
class Maze_block
{
    public:
    int m_i;
    int m_j;
    int m_d;
    Maze_block():m_i(0),m_j(0),m_d(-1){}
    Maze_block(int i,int j):m_i(i),m_j(j),m_d(-1){}
};
class Maze
{
    public:
    stack<Maze_block> stc;
    int maze[4 + 2][5 + 2] =
    {
    {0, 0, 0, 0, 0, 0, 0},  // 行0：外层围墙（顶部）
    {0, 1, 1, 0, 0, 0, 0},  // 行1：入口位置（1,1）为1
    {0, 0, 1, 1, 0, 0, 0},  // 行2
    {0, 0, 1, 1, 1, 0, 0},  // 行3
    {0, 0, 1, 1, 1, 1, 0},  // 行4：出口位置（4,5）为1
    {0, 0, 0, 0, 0, 0, 0}   // 行5：外层围墙（底部）
    };
    int display_maze[4 + 2][5 + 2];
    int top;
    Maze():top(-1){}
    void find_way(Maze_block&entrance,Maze_block&exit);
    bool find_value_block(Maze_block&c_blcock,Maze_block &n_block);
    void show_way(Maze_block&exit);
};
ostream & operator<<(ostream&os,Maze_block&data)
{
    os<<"("<<data.m_i<<","<<data.m_j<<")";
    return os;
}
bool operator==(Maze_block&data1,Maze_block&data2)
{
    if (data1.m_i==data2.m_i&&data1.m_j==data2.m_j)
    {
        return true;
    }
    return false;
}

void Maze::show_way(Maze_block& exit)
{

    stack<Maze_block> temp;
    Maze_block data;
    int i=0, j=0;

    // 创建临时栈的副本
    stack<Maze_block> copy = this->stc;

    // 将原栈内容倒入临时栈，实现反转
    while (!copy.empty())
    {
        temp.push(copy.top());
        copy.pop();
    }
    //不带箭头的初版图像
    /*
    for (int i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            int a = this->maze[i][j];
            switch (a)
            {
            case 1: cout << " 1 " ;break;
            case 2:cout << " . ";break;
            case 0:cout << " 0 ";break;
            }
        }
        cout << endl;
    }
    */
    int copy_maze[4 + 2][5 + 2];
    for (i = 0;i < 6;i++)
    {
        for (j = 0;j < 7;j++)
        {
            copy_maze[i][j] = maze[i][j];
        }
    }
    while (!temp.empty())
    {
        int d = (temp.top()).m_d;
        switch (d)
        {
        case 0:copy_maze[temp.top().m_i][temp.top().m_j] = 2;break;//2表示向上探索
        case 1:copy_maze[temp.top().m_i][temp.top().m_j] = 3;break;//3表示向右探索
        case 2:copy_maze[temp.top().m_i][temp.top().m_j] = 4;break;//4表示向下探索
        case 3:copy_maze[temp.top().m_i][temp.top().m_j] = 5;break;//5表示向左探索
        }
        temp.pop();
    }
    for (i = 0;i < 6;i++)
    {
        for (j = 0;j < 7;j++)
        {
            int a = copy_maze[i][j];
            switch (a)
            {
            case 0: cout << " 0 ";break;
            case 1:cout << " 1 ";break;
            case 2:cout << " ↑ ";break;
            case 3:cout << " → ";break;
            case 4:cout << " ↓ ";break;
            case 5:cout << " ← ";break;
            }
        }
        cout << endl;
    }
    //重新加载temp
    copy = this->stc;
    while (!copy.empty())
    {
        temp.push(copy.top());
        copy.pop();
    }
    // 输出文字路径
    while (!temp.empty())
    {
        if (temp.top() == exit)
        {
            cout << temp.top() << endl;
            temp.pop();
        }
        else
        {
            cout << temp.top() << "->";
            temp.pop();
        }
    }

    cout << endl;
}
bool Maze::find_value_block(Maze_block&c_block,Maze_block&n_block)
{
    int ni,nj;
    int i;
    for (i=c_block.m_d+1;i<4;i++)
    {
        switch(i)
        {
            case 0:ni=c_block.m_i-1;nj=c_block.m_j;break;
            case 1:ni=c_block.m_i;nj=c_block.m_j+1;break;
            case 2:ni=c_block.m_i+1;nj=c_block.m_j;break;
            case 3:ni=c_block.m_i;nj=c_block.m_j-1;break;
        }
        
        if (this->maze[ni][nj]==1)
        {
            n_block.m_i=ni;
            n_block.m_j=nj;
            n_block.m_d=-1;
            c_block.m_d=i;
            return true;
        }
    }
    return false;
}
void Maze::find_way(Maze_block&entrance,Maze_block&exit)
{
    int number=0;
    this->stc.push(entrance);
    this->maze[entrance.m_i][entrance.m_j]=2;//2表示访问并且可行的方块
    Maze_block c_block,n_block;
    while (!this->stc.empty())
    {
        c_block=this->stc.top();
        if (c_block==exit)
        {
            number++;
            cout<<"第"<<number<<"条路径"<<endl;
            show_way(exit);
            
            // 找到出口后，将当前位置标记为已访问但可通行，然后回溯
            this->maze[c_block.m_i][c_block.m_j] = 1;
            this->stc.pop();
            continue;
        }
        if (this->find_value_block(c_block,n_block))
        {
            //跟新top的内容，c_block只是一个临时变量，用来存储当前的位置，如果不更新，回溯的时候，top的m_d实际没有改变            
            this->stc.pop();
            this->stc.push(c_block);
            this->stc.push(n_block);
            this->maze[n_block.m_i][n_block.m_j]=2;//2表示访问并且可行的方块
        }
        else
        {
            this->maze[this->stc.top().m_i][this->stc.top().m_j]=1;
            //将方块重置为1，以便于其他路径使用
            this->stc.pop();
        }
    }
    if (number==0)
    {
        cout<<"No Way!!"<<endl;
        return ;
    }
    else
    {
        cout<<"Total Way:"<<number<<endl;
    }
}