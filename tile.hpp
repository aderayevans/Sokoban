#pragma once

class Tile
{
private:
    int x;
    int y;
public:
    Tile();
    Tile(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    ~Tile();
};