#ifndef SQUID_GAME_DS_H
#define SQUID_GAME_DS_H

#include "AVLTree.h"
#include "player.h"
#include "group.h"


class squidGameDS
{
    AVLTree<Player> players_by_id;
    AVLTree<Player> players_by_lvl;
    AVLTree<Group> players_groups;
    AVLTree<Group> empty_groups;
};



#endif