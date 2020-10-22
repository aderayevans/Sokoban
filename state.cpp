#include <math.h>
#include "state.hpp"

State::State()
    : box_num(0), goal_num(0)
{
}

void State::operator = (const State& A)
{
    goal_num = A.goal_num;
    box_num = A.box_num;
    pusher = A.pusher;
    for (int i = 0; i < goal_num; i++)
    {
        goal.push_back(A.goal[i]);
    }
    for (int i = 0; i < box_num; i++)
    {
        box.push_back(A.box[i]);
    }
}

int State::checkedGoalNumber()
{
    int total = 0;
    for (int i = 0; i < goal_num; i++)
    {
        total += goal[i].isChecked();
    }
    return total;
}

int State::euclideanDistance()
{
    int count = 0, dist2box_min = 1000, dist2goal_min, dist2box, dist2goal;
    for (int i = 0; i < box_num; i++)
    {
        dist2goal_min = 1000;
        for (int j = 0; j < goal_num; j++)
        {
            dist2goal = sqrt((goal[j].getX() - box[i].getX())*(goal[j].getX() - box[i].getX())
                             + (goal[j].getY() - box[i].getY())*(goal[j].getY() - box[i].getY()));
            if (dist2goal < dist2goal_min) dist2goal_min = dist2goal;
        }
        count += dist2goal_min;
        dist2box = sqrt((pusher.getX() - box[i].getX())*(pusher.getX() - box[i].getX())
                             + (pusher.getY() - box[i].getY())*(pusher.getY() - box[i].getY()));
        if (dist2box < dist2box_min) dist2box_min = dist2box;
    }
    return count + dist2box_min;
}

int State::manhattanDistance()
{
    int count = 0, dist2box_min = 1000, dist2goal_min, dist2box, dist2goal;
    for (int i = 0; i < box_num; i++)
    {
        dist2goal_min = 1000;
        for (int j = 0; j < goal_num; j++)
        {
            dist2goal = abs(goal[j].getX() - box[i].getX()) + abs(goal[j].getY() - box[i].getY());
            if (dist2goal < dist2goal_min) dist2goal_min = dist2goal;
        }
        count += dist2goal_min;
        dist2box = abs(pusher.getX() - box[i].getX()) + abs(pusher.getY() - box[i].getY());
        if (dist2box < dist2box_min) dist2box_min = dist2box;
    }
    return count + dist2box_min;
}

int State::goalAt(int x, int y)
{
    for (int i = 0; i < goal_num; i++)
    {
        if (goal[i].getX() == x && goal[i].getY() == y) return i;
    }
    return 0; //impossible take place
}

int State::boxAt(int x, int y)
{
    for (int i = 0; i < box_num; i++)
    {
        if (box[i].getX() == x && box[i].getY() == y) return i;
    }
    return 0; //impossible take place
}

bool State::isIdentical(State A)
{
    if (A.pusher.getX() == pusher.getX()  &&  A.pusher.getY() == pusher.getY())
    {
        for (int i = 0; i < box_num; i++)
        {
            if (A.box[i].getX() == box[i].getX()  &&  A.box[i].getY() == box[i].getY());
            else goto isDifferent;
        }
    }
    else
isDifferent:    return 0;
    return 1;
}

void State::print()
{
    cout << "Pusher: " << pusher.getX() << ", " << pusher.getY() << endl;
}

bool State::isBox(int x, int y)
{
    for (int i = 0; i < box_num; i++)
    {
        if (box[i].getX() == x && box[i].getY() == y) return true;
    }
    return false;
}

bool State::isGoal(int x, int y)
{
    for (int i = 0; i < goal_num; i++)
    {
        if (goal[i].getX() == x && goal[i].getY() == y) return true;
    }
    return false;
}

bool State::checkedAllGoals()
{
    for (int i = 0; i < goal_num; i++)
    {
        if (!goal[i].isChecked()) return 0;
    }
    return true;
}