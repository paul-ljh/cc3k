#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <string>
#include <vector>
#include "cell.h"
#include "enemy.h"
#include "player.h"
#include "itemtype.h"
#include "mapstate.h"

using namespace std;

class TextDisplay;

class Map : public Observer {

    const int COL_NUM;
    const int ROW_NUM;

    vector<vector<Cell>> grid;

    Player* p;

    vector<Enemy*> enemies;
    int enemy_num;

    TextDisplay* td;

    int stairChamber;

    mapState s;

    char playerChamber = '0';

    friend Cell;
public:
    //ctor dtor
    Map();
    ~Map();

    //init method;
    void init(string&, string&, int);

    // generates character
    void spawnPlayer(string);
    void spawnPlayer(Player*p);

    //generates staircase
    void spawnStair();

    //speciefic spanwns
    void spawnEnemies();

    // spawn items, gold or potion
    void spawnItems(itemType, int);

    // moves the player;
    void movePlayer(int, int);
    void movePlayer(string);

    void attack(int, int);

    //turn method;
    mapState nextTurn();

    SubscriptionType subType() const override;

    void update(Subject&) override;

    // use potion
    void usePotion(int, int);

    Player* getPlayerPtr();


    friend ostream &operator<<(ostream &out, const Map &m);
};

#endif