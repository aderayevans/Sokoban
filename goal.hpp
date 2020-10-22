#pragma once
#include "tile.hpp"

class Goal : public Tile
{
private:
    bool checker;
public:
    Goal();
    Goal(int x, int y, bool checker);

    void check();
    void unCheck();
    bool isChecked();
};