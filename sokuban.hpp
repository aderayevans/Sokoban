#pragma once
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include "comp.hpp"
#include "map.hpp"
#include "state.hpp"
#include "node.hpp"
#include "astarnode.hpp"


class Sokuban
{
private:
    Map map;
    State state;
    int level;
public:
    Sokuban();
    void initLevel(std::string levelFile);
    void solve();

    int up(State cur_state, State& result);
    int down(State cur_state, State& result);
    int left(State cur_state, State& result);
    int right(State cur_state, State& result);

    int callOperator(State cur_state, State& result, int option);
    int calculate_h(State the_state);

    bool backtrackingDetected(Node* parentNode, State the_state);
    bool contains(stack<Node*> openStack, State the_state);
    Node* depthFS();
    bool contains(queue<Node*> openQueue, State the_state);
    Node* breadthFS();
    void print_WaysToGetGoal(Node* node);

    bool backtrackingDetected(AStarNode* parentNode, State the_state);
    bool contains(stack<AStarNode*> closedStack, State the_state);
    bool contains(multiset<AStarNode*, Comp> openList, State the_state, int g);
    AStarNode* aStar();
    AStarNode* bestFS();
    void print_WaysToGetGoal(AStarNode* node);
};