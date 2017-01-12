#include "cell.h"
#include <algorithm>
#include "subscriptions.h"
#include "cstdlib"
#include "enemyfactory.h"
#include "playerfactory.h"
#include "itemfactory.h"
#include "map.h"

using namespace std;

Cell::Cell(char ct, char ch, Map* m):chamber(ch), isOccupied(false), whatIsOccupied(nullptr), map(m) {
    //to do: repalce this with try catch
    if(find(validCellType.begin(), validCellType.end(), ct) != validCellType.end()){
        cellType = ct;
    } else {
        cellType = ' ';
    }
}

Cell::~Cell(){}

void Cell::occupy(FieldObject* fo){
    whatIsOccupied = fo;
    isOccupied = true;
    notifyObservers(SubscriptionType::textDisplay);
}

void Cell::unOccupy(){
    whatIsOccupied = nullptr;
    isOccupied = false;
    notifyObservers(SubscriptionType::textDisplay);
}

Player* Cell::spawnPlayer(string playerRace){

    int playerType = 100;

    if(playerRace == "drow") {
        playerType = 1;
    } else if (playerRace == "troll") {
        playerType = 2;
    } else if (playerRace == "vampire") {
        playerType = 3;
    } else if (playerRace == "goblin") {
        playerType = 4;
    } else if (playerRace == "Admin"){
        playerType = 100;
    } else {
        // default is shade;
        playerType = 0;
    }
    Player* p = PlayerFactory(playerType, this, row, col);
    p->attach(map);
    Cell::occupy(p);
    return p;
}

// spawn a random enemy in the cell
Enemy* Cell::spawnEnemy(){

    //enemy is always a human for now
    int enemyType =  rand()%18;
    Enemy* e = EnemyFactory(enemyType, this, row, col);

    //attach the map so the map knows when an enemy dies
    e->attach(map);
    Cell::occupy(e);

    return e;
}

Item* Cell::spawnItem(itemType t){
    Item* item = ItemFactory(t);
    Cell::occupy(item);
    return item;
}

Item* Cell::spawnItem(itemType t, int v){
    Item* item = ItemFactory(t, v);
    Cell::occupy(item);
    return item;
}


//cell type
void Cell::setCellType(char ct) {
    if(find(validCellType.begin(), validCellType.end(), ct) != validCellType.end()){
        cellType = ct;
    } else {
        cellType = ' ';
    }
    notifyObservers(SubscriptionType::textDisplay);
}

// getters and setters
void Cell::setCoords(int r, int c) {
    row = r;
    col = c;
}

bool Cell::getIsOccupied() {
    return isOccupied;
}

bool Cell::canMoveTo(Enemy*, int dx, int dy){
    return (map->grid)[row + dx][col + dy].cellType == '.' &&
          !((map->grid)[row + dx][col + dy].getIsOccupied());
}

bool Cell::canMoveTo(Player* p, int dx, int dy){

    if(p->objectType() == "Admin") {
        return (!(map->grid)[row + dx][col + dy].getIsOccupied() 
        && (row + dx) < 24 && (col + dy) < 78  && (row + dx) > 0 && (col + dy) > 0 )||
        ((map->grid)[row + dx][col + dy].getIsOccupied() &&
           ((map->grid)[row + dx][col + dy].whatIsOccupied->getFieldIdentity() == 'G'));
    }

    return(((map->grid)[row + dx][col + dy].cellType == '.' ||
            (map->grid)[row + dx][col + dy].cellType == '+' ||
            (map->grid)[row + dx][col + dy].cellType == '#' ||
            (map->grid)[row + dx][col + dy].cellType == '\\' ) &&
          !((map->grid)[row + dx][col + dy].getIsOccupied())) ||
           ((map->grid)[row + dx][col + dy].getIsOccupied() &&
           ((map->grid)[row + dx][col + dy].whatIsOccupied->getFieldIdentity() == 'G')) ;
}

Cell* Cell::getPtrTo(int dx, int dy){
    return &((map->grid)[row + dx][col + dy]);
}

void Cell::update(Subject &whoNotified) {
    // currently not used
}

Info Cell::getInfo() const {
    return Info{row, col, isOccupied, cellType, chamber, whatIsOccupied};
}

SubscriptionType Cell::subType() const {
  return SubscriptionType::cell;
}