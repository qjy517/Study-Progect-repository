#include <iostream>
#include "maze.h"
using namespace std;
int main()
{
    Maze m;
    Maze_block entrance(1, 1);
    Maze_block exit(4, 5);
    m.find_way(entrance, exit);
    return 0;
}