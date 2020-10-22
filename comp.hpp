#pragma once
#include "astarnode.hpp"

struct Comp
{
    bool operator () (AStarNode* A, AStarNode* B) const
    {
        return A->f < B->f;
    }
};