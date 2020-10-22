#include "pusher.hpp"

Pusher::Pusher()
    : Tile()
{
}

Pusher::Pusher(int x, int y)
    : Tile(x, y)
{
}

void Pusher::operator = (const Pusher& A)
{
    setX(A.getX());
    setY(A.getY());
}

void Pusher::goUp()
{
    int i;
    setX(getX() - 1);
}

void Pusher::goDown()
{
    setX(getX() + 1);
}
void Pusher::goLeft()
{
    setY(getY() - 1);
}
void Pusher::goRight()
{
    setY(getY() + 1);
}

Pusher::~Pusher()
{
}