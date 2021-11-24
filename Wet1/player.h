#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    int id;
    int lvl;
    public:
    class lvlComp
    {
        public:
        int operator()(const Player& p1, const Player& p2)
        {
            return p1.id;
        }
    }
    Player(int id, int lvl):id(id), lvl(lvl){}
    ~Player()=default;
    Player(const Player& player) = default;
    Player& operator=(const Player& player) = default;
};



#endif