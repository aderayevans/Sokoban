#pragma once
#include <iostream>
#include <vector>
#include "pusher.hpp"
#include "box.hpp"
#include "goal.hpp"

using namespace std;

struct State
{
    vector<Box> box;                                                        //3
    Pusher pusher;                                                              //4
    vector<Goal> goal;                                                              //5
    int box_num, goal_num;

    State();
    void operator = (const State& A);
    bool isIdentical(State A);
    bool isBox(int x, int y);
    bool isGoal(int x, int y);
    int goalAt(int x, int y);
    int boxAt(int x, int y);
    void print();
    int checkedGoalNumber();
    int euclideanDistance();
    int manhattanDistance();
    bool checkedAllGoals();

    //~State();
};