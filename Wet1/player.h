#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    int id;
    int lvl;
    public:
    Player(int id, int lvl):id(id), lvl(lvl){}
    ~Player()=default;
    Player(const Player& player) = default;
    Player& operator=(const Player& player) = default;
};



#endif