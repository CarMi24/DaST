#ifndef SQUID_GAME_DS_H
#define SQUID_GAME_DS_H

#include "genericRankTree.h"
#include "player.h"
#include "group.h"


class squidGameDS
{
    genericRankTree<Player,Player,Player::lvlComp()> all_players;
    genericRankTree<Group> players_groups;
    genericRankTree<Group> empty_groups;
};



#endif