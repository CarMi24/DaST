#ifndef GROUP_H
#define GROUP_H

#include "AVLTree.h"
#include "player.h"

class Group
{
    int id;
    int n;
    AVLTree<Player> players;
    public:
    Group();
    ~Group()=default;
    Group(const Group& player);
    Group& operator=(const Group& group) = default;
    Group& operator<(const Group& group);
    
};

#endif