#pragma once
#include "state.hpp"

struct AStarNode
{
    State state;
    AStarNode* parent;
    int g, h, f;
    int no_function;
    AStarNode()
        : state(State()), parent(NULL), no_function(0), g(0), h(0), f(0)
    {}
    AStarNode(State state, AStarNode* parent, int no_function, int g, int h, int f)
        : state(state), parent(parent), no_function(no_function), g(g), h(h), f(f)
    {}
};