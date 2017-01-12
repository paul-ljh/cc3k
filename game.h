#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <string>
#include <vector>
#include "observer.h"

using namespace std;

class Map;
class Player;

class Game: public Observer{

    vector<Map> m;
    int currentFloor;

    const int BEGINNING_FLOOR;
    const int WINNING_FLOOR;

    string mapLayout;
    string chamberLayout;

    Player* p;

public:
    //ctor dtor
    Game(string, string);
    ~Game();

    //init method;
    void init(string);

    //moves the player in the direction specified
    void movePlayer(int, int);
    void movePlayer(string);

    // attacks in the diretion specified
    void attack(string);

    //gets called every turn
    int nextTurn();

    // when a player attempts to use potion;
    void usePotion(string);

    void update(Subject &whoNotified) override;

    int changeFloor(int);

    SubscriptionType subType() const override;

    friend ostream &operator<<(ostream &out, const Game &g);
};

#endif