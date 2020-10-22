#include "box.hpp"

Box::Box()
    : Tile()
{
}
Box::Box(int x, int y)
    : Tile(x, y)
{
}
void Box::isPushedUp()
{
    setX(getX() - 1);
}
void Box::isPushedDown()
{
    setX(getX() + 1);
}
void Box::isPushedLeft()
{
    setY(getY() - 1);
}
void Box::isPushedRight()
{
    setY(getY() + 1);
}
Box::~Box()
{
}