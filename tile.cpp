#include "tile.hpp"

Tile::Tile()
    : x(0), y(0)
{
}
Tile::Tile(int x, int y)
    : x(x), y(y)
{
}
int Tile::getX() const {  return x;   }
int Tile::getY() const {  return y;   };
void Tile::setX(int x)
{
    this->x = x;
}
void Tile::setY(int y)
{
    this->y = y;
}
Tile::~Tile()
{
}