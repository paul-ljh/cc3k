#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
#include <string>
#include <vector>
#include "cellinfo.h"
#include "subject.h"
#include "observer.h"
#include "itemtype.h"

using namespace std;

class FieldObject;
class Map;
class Enemy;
class Player;
class Admin;
class Item;

struct Info;

class Cell: public Subject, public Observer {

    char cellType;
    char chamber;
    bool isOccupied;
    FieldObject* whatIsOccupied;

    int row;
    int col;

    Map* map;

    const vector<char> validCellType = {'|', '_', '#', '+', '.', ' ', '\\'};
public:
    //ctor dtor
    //CellType is one of ('|' , '_', '#', '+', '.', ' ') 
    Cell(char cellType, char, Map* m);
    ~Cell();

    bool getIsOccupied();

    //getters and setters
    void setCoords(int, int);
    Info getInfo() const override;

    //sets the chamber number
    void setChamber(int);

    //set cellType;
    void setCellType(char);

    //cell actions
    void occupy(FieldObject*);
    void unOccupy();


    // spwawns the player in this cell
    Player* spawnPlayer(string);

    // spawns an enemy in this cell
    Enemy* spawnEnemy();

    // spawn an item, gold or potion, in this cell
    Item* spawnItem(itemType);
    Item* spawnItem(itemType, int);

    // move restrictions
    bool canMoveTo(Enemy*, int, int);
    bool canMoveTo(Player*, int, int);

    // gets the pointer to Cell at row+dx, col+dy
    // Requires : canMoveTo(dx, dy) == true
    Cell* getPtrTo(int , int );

    void update(Subject &whoNotified) override;

    SubscriptionType subType() const override;

};

#endif