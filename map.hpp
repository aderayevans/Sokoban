#include <iostream>
#include <vector>
#include "tile.hpp"
#pragma once

using namespace std;

struct Map
{                                                                               
    vector<Tile> out_of_space;                          //0
    vector<Tile> space;                                          //2
    vector<Tile> wall;                                      //1
    int ofs_num, space_num, wall_num, width, height;

    Map();
    bool isOutOfSpace(int x, int y);
    bool isSpace(int x, int y);
    bool isWall(int x, int y);
    bool isDeadEnd(int x, int y);
    int checkType(int x, int y);
    void print();
};