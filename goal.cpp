#include "goal.hpp"

Goal::Goal()
    : Tile(), checker(false)
{
}
Goal::Goal(int x, int y, bool checker)
    : Tile(x, y), checker(checker)
{
}
void Goal::check()
{
    checker = true;
}
void Goal::unCheck()
{
    checker = false;
}
bool Goal::isChecked()
{
    return checker;
}