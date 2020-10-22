#pragma once
#include "state.hpp"

struct Node
{
    State state;
    Node* parent;
    int no_function;
    Node()
        : state(State()), parent(NULL), no_function(0)
    {}
    Node(State state, Node* parent, int no_function)
        : state(state), parent(parent), no_function(no_function)
    {}
};