#include "sokuban.hpp"

const char* action[] = {
    "First State",
    "move up", "move down",
    "move left", "move right"
};

Sokuban::Sokuban()
{
    int pick_level = 0;
    int max_choice = 3;
    while (pick_level < 1 || pick_level > max_choice)
    {
        std::cout << "Choose level: " << std::endl;
        std::cout << "\t1: easy" << std::endl;
        std::cout << "\t2: medium" << std::endl;
        std::cout << "\t3: hard" << std::endl;
        cin >> pick_level;
    }
    level = pick_level;
    std::string levelFile;
    switch (level)
    {
        case 1: levelFile = "level1.txt";
            break;
        case 2: levelFile = "level2.txt";
            break;
        case 3: levelFile = "level3.txt";
            break;
        default: levelFile = "level1.txt";
            break;
    }
    initLevel(levelFile);
}

void Sokuban::solve()
{
    int pick_algorithm = 0;
    int max_choice = 4;
    while (pick_algorithm < 1 || pick_algorithm > max_choice)
    {
        std::cout << "Choose algorithm to solve: " << std::endl;
        std::cout << "\t1: Depth-first search" << std::endl;
        std::cout << "\t2: Breadth-first search" << std::endl;
        std::cout << "\t3: Best-first search" << std::endl;
        std::cout << "\t4: A*" << std::endl;
        cin >> pick_algorithm;
    }
    switch (pick_algorithm)
    {
        case 1: print_WaysToGetGoal(depthFS());
            break;
        case 2: print_WaysToGetGoal(breadthFS());
            break;
        case 3: print_WaysToGetGoal(bestFS());
            break;
        case 4: print_WaysToGetGoal(aStar());
            break;
        default: print_WaysToGetGoal(aStar());
            break;
    }
}

void Sokuban::initLevel(std::string levelFile)
{
    std::ifstream ifs(levelFile);
    std::string str;
    int i = 0;
    int j = 0;
    int cur;
    if (ifs.is_open()) {
        while(!ifs.eof()) {
            ifs >> cur;
            switch(cur)
            {
                case 0:
                    map.out_of_space.push_back(Tile(i, j));
                    map.ofs_num++;
                    break;
                case 1:
                    map.wall.push_back(Tile(i, j));
                    map.wall_num++;
                    break;
                case 2:
                    map.space.push_back(Tile(i, j));
                    map.space_num++;
                    break;
                case 3:
                    map.space.push_back(Tile(i, j));
                    map.space_num++;
                    state.box.push_back(Box(i, j));
                    state.box_num++;
                    break;
                case 4:
                    map.space.push_back(Tile(i, j));
                    map.space_num++;
                    state.pusher = Pusher(i, j);
                    break;
                case 5:
                    map.space.push_back(Tile(i, j));
                    map.space_num++;
                    state.goal.push_back(Goal(i, j, false));
                    state.goal_num++;
                    break;
                case 6:
                    map.space.push_back(Tile(i, j));
                    map.space_num++;
                    state.pusher = Pusher(i, j);
                    state.goal.push_back(Goal(i, j, true));
                    state.goal_num++;
                    break;
                case 7:
                    map.space.push_back(Tile(i, j));
                    map.space_num++;
                    state.box.push_back(Box(i, j));
                    state.box_num++;
                    state.goal.push_back(Goal(i, j, true));
                    state.goal_num++;
                    break;
                default:
                    std::cout << "Strange number appearing in level_file";
                    break;
            }
            j++;
            if (ifs.peek() == '\n')
            {
                i++;
                j = 0;
            }
        }
        ifs.close();
    }
    else {
        cout << "Unable to read file";
    }
    map.width = j, map.height = i + 1;
    /*
    cout << "ofs: " << map.ofs_num << endl;
    cout << "space: " << map.space_num << endl;
    cout << "wall: " << map.wall_num << endl;
    cout << "height: " << map.height << endl;
    cout << "width: " << map.width << endl;*/
}

int Sokuban::up(State cur_state, State& result)
{
    result = cur_state;
    int newX_pusher = cur_state.pusher.getX() - 1, newY_pusher = cur_state.pusher.getY();
    if (!map.isSpace(newX_pusher, newY_pusher)) return 0;
    if (cur_state.isBox(newX_pusher, newY_pusher))
    {
        int oldX_box = newX_pusher, oldY_box = newY_pusher,
            newX_box = oldX_box - 1, newY_box = oldY_box;
        if (cur_state.isGoal(oldX_box, oldY_box)) result.goal[result.goalAt(oldX_box, oldY_box)].unCheck();
        if (!map.isSpace(newX_box, newY_box)) return 0;
        if (cur_state.isBox(newX_box, newY_box)) return 0;
        if (cur_state.isGoal(newX_box, newY_box)) result.goal[result.goalAt(newX_box, newY_box)].check();
        else if (map.isDeadEnd(newX_box, newY_box)) return 0;
        result.box[result.boxAt(oldX_box, oldY_box)].isPushedUp();
    }
    result.pusher.goUp();
    return 1;
}

int Sokuban::down(State cur_state, State& result)
{
    result = cur_state;
    int newX_pusher = cur_state.pusher.getX() + 1, newY_pusher = cur_state.pusher.getY();
    if (!map.isSpace(newX_pusher, newY_pusher)) return 0;
    if (cur_state.isBox(newX_pusher, newY_pusher))
    {
        int oldX_box = newX_pusher, oldY_box = newY_pusher,
            newX_box = oldX_box + 1, newY_box = oldY_box;
        if (cur_state.isGoal(oldX_box, oldY_box)) result.goal[result.goalAt(oldX_box, oldY_box)].unCheck();
        if (!map.isSpace(newX_box, newY_box)) return 0;
        if (cur_state.isBox(newX_box, newY_box)) return 0;
        if (cur_state.isGoal(newX_box, newY_box)) result.goal[result.goalAt(newX_box, newY_box)].check();
        else if (map.isDeadEnd(newX_box, newY_box)) return 0;
        result.box[result.boxAt(oldX_box, oldY_box)].isPushedDown();
    }
    result.pusher.goDown();
    return 1;
}

int Sokuban::left(State cur_state, State& result)
{
    result = cur_state;
    int newX_pusher = cur_state.pusher.getX(), newY_pusher = cur_state.pusher.getY() - 1;
    if (!map.isSpace(newX_pusher, newY_pusher)) return 0;
    if (cur_state.isBox(newX_pusher, newY_pusher))
    {
        int oldX_box = newX_pusher, oldY_box = newY_pusher,
            newX_box = oldX_box, newY_box = oldY_box - 1;
        if (cur_state.isGoal(oldX_box, oldY_box)) result.goal[result.goalAt(oldX_box, oldY_box)].unCheck();
        if (!map.isSpace(newX_box, newY_box)) return 0;
        if (cur_state.isBox(newX_box, newY_box)) return 0;
        if (cur_state.isGoal(newX_box, newY_box)) result.goal[result.goalAt(newX_box, newY_box)].check();
        else if (map.isDeadEnd(newX_box, newY_box)) return 0;
        result.box[result.boxAt(oldX_box, oldY_box)].isPushedLeft();
    }
    result.pusher.goLeft();
    return 1;
}

int Sokuban::right(State cur_state, State& result)
{
    result = cur_state;
    int newX_pusher = cur_state.pusher.getX(), newY_pusher = cur_state.pusher.getY() + 1;
    if (!map.isSpace(newX_pusher, newY_pusher)) return 0;
    if (cur_state.isBox(newX_pusher, newY_pusher))
    {
        int oldX_box = newX_pusher, oldY_box = newY_pusher,
            newX_box = oldX_box, newY_box = oldY_box + 1;
        if (cur_state.isGoal(oldX_box, oldY_box)) result.goal[result.goalAt(oldX_box, oldY_box)].unCheck();
        if (!map.isSpace(newX_box, newY_box)) return 0;
        if (cur_state.isBox(newX_box, newY_box)) return 0;
        if (cur_state.isGoal(newX_box, newY_box)) result.goal[result.goalAt(newX_box, newY_box)].check();
        else if (map.isDeadEnd(newX_box, newY_box)) return 0;
        result.box[result.boxAt(oldX_box, oldY_box)].isPushedRight();
    }
    result.pusher.goRight();
    return 1;
}

int Sokuban::callOperator(State cur_state, State& result, int option)
{
    switch(option)
    {
        case 1: return up(cur_state, result);
        case 2: return down(cur_state, result);
        case 3: return left(cur_state, result);
        case 4: return right(cur_state, result);
        default: printf("Error calls operators");
            return 0;
    }
}

bool Sokuban::backtrackingDetected(Node* parentNode, State the_state)
{
    if (parentNode == NULL) goto end;
    else if (the_state.isIdentical(parentNode->state)) return true;
end:    return false;
}

bool Sokuban::contains(stack<Node*> openStack, State the_state)
{
    while (!openStack.empty())
    {
        if (the_state.isIdentical(openStack.top()->state))
            return 1;
        openStack.pop();
    }
    return 0;
}

Node* Sokuban::depthFS()
{
    stack<Node*> Open_DFS;
    stack<Node*> Closed_DFS;

    Node *root = new Node();
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;
    Open_DFS.push(root);

    Open_DFS.top()->state.print();
    int times = 0;
    while(!Open_DFS.empty())
    //while (times < 15)
    {
        Node *node = Open_DFS.top();
        Open_DFS.pop();
        Closed_DFS.push(node);
        if (node->state.checkedAllGoals())
        {
            cout << "Times loop: " << times << endl;
            return node;
        }
        int opt;
        times++;
        cout << "Times loop: " << times << endl;
        for (opt = 1; opt <= 4; opt++)
        {
            State newState = State();

            if (callOperator(node->state, newState, opt))
            {
                if (backtrackingDetected(node->parent, newState))
                {
                    continue;
                }
                if (contains(Closed_DFS, newState) || contains(Open_DFS, newState))
                    continue;
                Node *newNode = new Node(newState, node, opt);
                Open_DFS.push(newNode);
                cout << "+ Option " << action[opt] << " ";
                Open_DFS.top()->state.print();
                //delete newNode;
            }
        }
    }
    return NULL;
}

bool Sokuban::contains(queue<Node*> openQueue, State the_state)
{
    while (!openQueue.empty())
    {
        if (the_state.isIdentical(openQueue.front()->state))
            return 1;
        openQueue.pop();
    }
    return 0;
}

Node* Sokuban::breadthFS()
{
    queue<Node*> Open_DFS;
    queue<Node*> Closed_DFS;

    Node *root = new Node();
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;
    Open_DFS.push(root);

    Open_DFS.front()->state.print();
    int times = 0;
    while(!Open_DFS.empty())
    //while (times < 15)
    {
        Node *node = Open_DFS.front();
        Open_DFS.pop();
        Closed_DFS.push(node);
        if (node->state.checkedAllGoals())
        {
            cout << "Times loop: " << times << endl;
            return node;
        }
        int opt;
        times++;
        cout << "Times loop: " << times << endl;
        for (opt = 1; opt <= 4; opt++)
        {
            State newState = State();

            if (callOperator(node->state, newState, opt))
            {

                if (backtrackingDetected(node->parent, newState))
                {
                    continue;
                }
                if (contains(Closed_DFS, newState) || contains(Open_DFS, newState))
                    continue;
                Node *newNode = new Node(newState, node, opt);
                Open_DFS.push(newNode);
                cout << "+ Option " << action[opt] << " ";
                Open_DFS.front()->state.print();
                //delete newNode;
            }
        }
    }
    return NULL;
}

void Sokuban::print_WaysToGetGoal(Node* node)
{
    stack<Node*> stackPrint;
    while(node->parent != NULL)
    {
        stackPrint.push(node);
        node = node->parent;
    }
    stackPrint.push(node);
    int no_action = 0;
    while (!stackPrint.empty())
    {
        cout << "\nAction " << no_action << ": " << action[stackPrint.top()->no_function] << ", ";
        stackPrint.top()->state.print();
        stackPrint.pop();
        no_action++;
    }
}

int Sokuban::calculate_h(State state)
{

    //cout << "With manhattan distance = " << state.manhattanDistance() + (state.goal_num - state.checkedGoalNumber()) << " ";
    return state.manhattanDistance() + (state.goal_num - state.checkedGoalNumber());
    //return state.euclideanDistance() - state.checkedGoalNumber();
}

bool Sokuban::contains(stack<AStarNode*> closedStack, State the_state)
{
    while (!closedStack.empty())
    {
        if (the_state.isIdentical(closedStack.top()->state))
            return 1;
        closedStack.pop();
    }
    return 0;
}

bool Sokuban::contains(multiset<AStarNode*, Comp> openList, State the_state, int g)
{
    for (AStarNode* n: openList)
        if (the_state.isIdentical(n->state))
            //if (g > n->g)
                return 1;
    return 0;
}

AStarNode* Sokuban::aStar()
{
    AStarNode* root = new AStarNode(state, NULL, 0, 0, calculate_h(state), calculate_h(state) + 0);
    stack<AStarNode*> explored;
    
    multiset<AStarNode*, Comp> frontiers;
    frontiers.insert(root);
    int times = 0;
    while (!frontiers.empty())
    {
        AStarNode* node = *frontiers.begin();
        frontiers.erase(frontiers.begin());
        explored.push(node);
        if (node->state.checkedAllGoals())
        {
            cout << "Times loop: " << times << endl;
            return node;
        }
        times++;
        cout << "Times loop: " << times << endl;
        for (int opt = 1; opt <= 4; opt++)
        {
            State new_state;
            if (callOperator(node->state, new_state, opt))
            {
                if (backtrackingDetected(node->parent, new_state))
                {
                    continue;
                }
                if (contains(explored, new_state))
                {
                    continue;
                }
                int newG = node->g + 1;
                int newH = calculate_h(new_state);
                if (contains(frontiers, new_state, newG))
                {
                    continue;
                }
                cout << "+ Option " << action[opt] << " ";
                new_state.print();
                AStarNode* n = new AStarNode(new_state, node, opt, newG, newH, newG + newH);
                frontiers.insert(n);
            }
        }
    }
    return NULL;
}

bool Sokuban::backtrackingDetected(AStarNode* parentNode, State the_state)
{
    if (parentNode == NULL) goto end;
    else if (the_state.isIdentical(parentNode->state)) return true;
end:    return false;
}

AStarNode* Sokuban::bestFS()
{
    AStarNode* root = new AStarNode(state, NULL, 0, 0, calculate_h(state), calculate_h(state) + 0);
    stack<AStarNode*> explored;
    
    multiset<AStarNode*, Comp> frontiers;
    frontiers.insert(root);
    int times = 0;
    while (!frontiers.empty())
    {
        AStarNode* node = *frontiers.begin();
        frontiers.erase(frontiers.begin());
        explored.push(node);
        if (node->state.checkedAllGoals())
        {
            cout << "Times loop: " << times << endl;
            return node;
        }
        times++;
        cout << "Times loop: " << times << endl;
        for (int opt = 1; opt <= 4; opt++)
        {
            State new_state;
            if (callOperator(node->state, new_state, opt))
            {
                if (backtrackingDetected(node->parent, new_state))
                {
                    continue;
                }
                if (contains(explored, new_state))
                {
                    continue;
                }
                int newG = 0;
                int newH = calculate_h(new_state);
                if (contains(frontiers, new_state, newG))
                {
                    continue;
                }
                cout << "+ Option " << action[opt] << " ";
                new_state.print();
                AStarNode* n = new AStarNode(new_state, node, opt, newG, newH, newG + newH);
                frontiers.insert(n);
            }
        }
    }
    return NULL;
}

void Sokuban::print_WaysToGetGoal(AStarNode* node)
{
    stack<AStarNode*> stackPrint;
    while(node->parent != NULL)
    {
        stackPrint.push(node);
        node = node->parent;
    }
    stackPrint.push(node);
    int no_action = 0;
    while (!stackPrint.empty())
    {
        cout << "\nAction " << no_action << ": " << action[stackPrint.top()->no_function] << ", ";
        stackPrint.top()->state.print();
        stackPrint.pop();
        no_action++;
    }
}