#pragma once
#include "tile.hpp"

class Pusher : public Tile
{
public:
    Pusher();
    Pusher(int x, int y);
    void operator = (const Pusher& A);
    void goUp();
    void goDown();
    void goLeft();
    void goRight();

    ~Pusher();
};