#include "map.hpp"

Map::Map()
    : ofs_num(0), space_num(0), wall_num(0), width(0), height(0)
{
}

bool Map::isOutOfSpace(int x, int y)
{
    for (int i = 0; i < ofs_num; i++)
    {
        if (out_of_space[i].getX() == x && out_of_space[i].getY() == y) return true;
    }
    return false;
}

bool Map::isSpace(int x, int y)
{
    for (int i = 0; i < space_num; i++)
    {
        if (space[i].getX() == x && space[i].getY() == y) return true;
    }
    return false;
}

bool Map::isWall(int x, int y)
{
    for (int i = 0; i < wall_num; i++)
    {
        if (wall[i].getX() == x && wall[i].getY() == y) return true;
    }
    return false;
}

bool Map::isDeadEnd(int x, int y)
{
    if (isWall(x - 1, y) && isWall(x, y - 1)) return true;
    if (isWall(x - 1, y) && isWall(x, y + 1)) return true;
    if (isWall(x + 1, y) && isWall(x, y - 1)) return true;
    if (isWall(x + 1, y) && isWall(x, y + 1)) return true;
    return false;
}

int Map::checkType(int x, int y)
{
    if (isOutOfSpace(x, y)) return 0;
    else if (isWall(x, y)) return 1;
    else return 2;
}

void Map::print()
{
    int type;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            type = checkType(i, j);
            cout << type << " ";
        }
        cout << endl;
    }
}