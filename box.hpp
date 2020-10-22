#include "tile.hpp"
#pragma once

class Box : public Tile
{
public:
    Box();
    Box(int x, int y);
    void isPushedUp();
    void isPushedDown();
    void isPushedLeft();
    void isPushedRight();

    ~Box();
};