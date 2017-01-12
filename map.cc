#include "map.h"
#include "textdisplay.h"
#include <cstdlib>
#include "cellinfo.h"
#include "potion.h"
#include <algorithm>
#include <iterator>
#include "itemtype.h"
#include "actiontype.h"

Map::Map():COL_NUM(79), ROW_NUM(25), p(nullptr), enemy_num(0), td(nullptr), s(mapState::normal) {};

Map::~Map(){
    delete td;
};


// init
void Map::init(string& map_layout, string& cl, int f){

    //initializes the text display;
    td = new TextDisplay(ROW_NUM, COL_NUM, f, map_layout);

    string::iterator it=map_layout.begin();
    char cell_layout;

    string::iterator cit=cl.begin();
    char chamber_layout;

    //initializes a 2-D vector of Cells
    for(int i = 0; i < ROW_NUM; i++) {

        vector<Cell> tmp;

        for (int j = 0; j < COL_NUM; j++){

            cell_layout = *it;
            chamber_layout = *cit;

            //constructs a cell with the cell_layout
            // for example if cell_layout is '-' or '|' it means that this cell is part of the wall
            tmp.push_back(Cell{cell_layout, chamber_layout, this});
            tmp.back().setCoords(i, j);
            tmp.back().attach(td);

            ++it;
            ++cit;
        }

        grid.push_back(tmp);
    }

}

void Map::spawnStair(){

    while(true){
        //generates a random coordinate
        int randRow = rand()%ROW_NUM;
        int randCol = rand()%COL_NUM;

        Info randGridInfo = grid[randRow][randCol].getInfo();

        if(randGridInfo.cellType == '.' && randGridInfo.chamber != playerChamber) {
           grid[randRow][randCol].setCellType('\\');
           return;
        }
    }
}

void Map::spawnPlayer(string playerRace){

    td->setAction(actionType::flush);

    bool foundCell = false;

    int randRow;
    int randCol;

    int chamber = 48 + rand()%4;

    while(!foundCell) {
        randRow = rand()%ROW_NUM;
        randCol = rand()%COL_NUM;

        Info randGridInfo = grid[randRow][randCol].getInfo();

        if(    randGridInfo.isOccupied
            || randGridInfo.cellType == '|'
            || randGridInfo.cellType == '_'
            || randGridInfo.cellType == ' '
            || randGridInfo.cellType == '+'
            || randGridInfo.cellType == '#'
            || randGridInfo.cellType == '\\'
            || randGridInfo.chamber != chamber) {

        } else {
            foundCell = true;
            //sets player chamber
            playerChamber = randGridInfo.chamber;
        }

    }

    // attach the player to the text display and notify it
    p = grid[randRow][randCol].spawnPlayer(playerRace);
    p->attach(td);
    p->notifyObservers(SubscriptionType::textDisplay);
    td->setAction(actionType::spawn);

}

void Map::spawnPlayer(Player* p){

    td->setAction(actionType::flush);

    bool foundCell = false;

    int randRow;
    int randCol;

    int chamber = 48 + rand()%4;

    while(!foundCell) {

        randRow = rand()%ROW_NUM;
        randCol = rand()%COL_NUM;

        Info randGridInfo = grid[randRow][randCol].getInfo();

        if(    randGridInfo.isOccupied
            || randGridInfo.cellType == '|'
            || randGridInfo.cellType == '_'
            || randGridInfo.cellType == ' '
            || randGridInfo.cellType == '+'
            || randGridInfo.cellType == '#'
            || randGridInfo.cellType == '\\'
            || randGridInfo.chamber != chamber) {

        } else {
            foundCell = true;
            //sets player chamber
            playerChamber = randGridInfo.chamber;
        }

    }

    // attach the player to the text display and notify it
    grid[randRow][randCol].occupy(p);
    p->attach(td);
    p->notifyObservers(SubscriptionType::textDisplay);
    td->setAction(actionType::newFloor);

}

void Map::spawnEnemies(){

    int enemiesSpawned = 0;

    while(enemiesSpawned < 20){

         // generates a random chamber
        char randChamber = 48 + rand()%5;

        Info randGridInfo;
        int randRow;
        int randCol;

        do {

            //generates a random coordinate
            randRow = rand()%ROW_NUM;
            randCol = rand()%COL_NUM;

            randGridInfo = grid[randRow][randCol].getInfo();

        } while (randGridInfo.chamber != randChamber );

        //
        if(randGridInfo.isOccupied || randGridInfo.cellType == '|'
                                   || randGridInfo.cellType == '_'
                                   || randGridInfo.cellType == ' '
                                   || randGridInfo.cellType == '+'
                                   || randGridInfo.cellType == '#'
                                   || randGridInfo.cellType == '\\') {
        } else {
            // spawns an enemy in the selected grid
            enemies.push_back(grid[randRow][randCol].spawnEnemy());
            enemiesSpawned++;
        }
    }
}

void Map::spawnItems(itemType t, int n){

    int itemsSpawned = 0;

    while(itemsSpawned < n) {

        //generates a random coordinate
        int randRow = rand()%ROW_NUM;
        int randCol = rand()%COL_NUM;

        Info randGridInfo = grid[randRow][randCol].getInfo();

         if( (!randGridInfo.isOccupied) && randGridInfo.cellType == '.' ){
            grid[randRow][randCol].spawnItem(t);
            itemsSpawned++;
         }

    }
}

// moves the pplayer
void Map::movePlayer(int dx, int dy){

    td->setAction(actionType::flush);

    p->move(dx, dy);

    td->setAction(actionType::move);

    int newPlayerRow = p->getRow();
    int newPlayerCol = p->getCol();

    for(int dr = -1; dr < 2; dr++) {
        for(int dc = -1; dc < 2; dc++) {

            Info ci = grid[newPlayerRow + dr][newPlayerCol + dc].getInfo();
            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Enemy"){

                Enemy* e = static_cast<Enemy*>(ci.whatIsOccupied);
                e->attack(*p);
                td->setAction(actionType::beAttacked);

            }
        }
    }
}

void Map::movePlayer(string direction){

    td->setAction(actionType::flush);

    int dx;
    int dy;

    if(direction == "no") {
        dx = -1;
        dy = 0;
    } else if (direction == "so") {
        dx = 1;
        dy = 0;
    } else if(direction == "ea") {
        dx = 0;
        dy = 1;
    } else if (direction == "we") {
        dx = 0;
        dy = -1;
    } else if (direction == "ne") {
        dx = -1;
        dy = 1;
    } else if (direction == "nw") {
        dx = -1;
        dy = -1;
    } else if (direction == "se") {
        dx = 1;
        dy = 1;
    } else if (direction == "sw") {
        dx = 1;
        dy = -1;
    } else {
        dx = 0;
        dy = 0;
    }

    p->move(dx, dy);
    td->setAction(actionType::move);

    int newPlayerRow = p->getRow();
    int newPlayerCol = p->getCol();

    for(int dr = -1; dr < 2; dr++) {
        for(int dc = -1; dc < 2; dc++) {

            Info ci = grid[newPlayerRow + dr][newPlayerCol + dc].getInfo();

            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Potion") {

                td->setAction(actionType::seePotion);
            }

            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Enemy"){

                Enemy* e = static_cast<Enemy*>(ci.whatIsOccupied);
                e->attack(*p);
                td->setAction(actionType::beAttacked);

            }
        }
    }

}

void Map::attack(int dx, int dy){

    td->setAction(actionType::flush);

    int r = p->getRow() + dx;
    int c = p->getCol() + dy;

    if(!grid[r][c].getIsOccupied()) return;

    Info ci = grid[r][c].getInfo();

    string ot = ci.whatIsOccupied->objectType();

    if(ot == "Enemy") {
        Enemy* e = static_cast<Enemy*>(ci.whatIsOccupied);
        p->attack(*e);
        td->setAction(actionType::attacked);
    }
}

// next turn
mapState Map::nextTurn(){

    // vector<Enemy*> tmp(enemies.size());
    // auto it = copy_if(enemies.begin(), enemies.end(), tmp.begin() , [](Enemy* e) {
    //     if(e->isDead()){

    //         Info ci = e->getInfo();
    //         delete grid[ci.row][ci.col].whatIsOccupied;
    //         grid[ci.row][ci.col].unOccupy();

    //         return false;
    //     } else {
    //         return true;
    //     }
    // } );

    // tmp.resize(distance(tmp.begin(),it));
    // enemies = tmp;

    for(auto &e : enemies){

        int dx = rand()%3 - 1;
        int dy = rand()%3 - 1;

        e->move(dx, dy);
    }

    return s;

}

void Map::usePotion(int dx, int dy){

    td->setAction(actionType::flush);

    int r = p->getRow() + dx;
    int c = p->getCol() + dy;

    if(!grid[r][c].getIsOccupied()) return;

    Info ci = grid[r][c].getInfo();

    string ot = ci.whatIsOccupied->objectType();
    if(ot == "Potion") {
        // the occupied object is checked to be potion, hence can be casted
        Potion* potionPtr = static_cast<Potion*>(ci.whatIsOccupied);
        // updates player stats
        p->usePotion(potionPtr);
        p->notifyObservers(SubscriptionType::textDisplay);
        td->setAction(actionType::usePotion);
        // unoccupy the potion cell
        grid[r][c].unOccupy();
    }
}


// used when a character is killed
void Map::update(Subject &whoNotified) {

    // get the row and col of the enemy that is killed
    Info enemy_info = whoNotified.getInfo();

    // check if the character killed is a player
    if(enemy_info.cellType == '@') {
        s = mapState::playerDead;
        return;
    }

    int r = enemy_info.row;
    int c = enemy_info.col;
    string race = enemy_info.race;

    // this actually gets the pointer to the enemy, by asking the cell
    // what is occupying it
    Info ci = grid[r][c].getInfo();

    Enemy* toBeDeleted = static_cast<Enemy*>(ci.whatIsOccupied);


    grid[ci.row][ci.col].unOccupy();

    // human drops gold while other races automatilly add gold
    if(race == "human") {
        grid[ci.row][ci.col].spawnItem(itemType::gold, 4);
    }
    else if(race == "merchant") {
        grid[ci.row][ci.col].spawnItem(itemType::gold, 4);
    }
    else {
        p->changeGold(rand()%2 + 1);
    }

     // deletes the enemy from the list of enemies in the map
    vector<Enemy*>::iterator newEnd = std::remove(enemies.begin(), enemies.end(), toBeDeleted);
    enemies.erase(newEnd, enemies.end());

    // delete the ACTUAL enemy;
    // THE LINE BELOW CAUSES SEGMENATION FAULT
    //delete toBeDeleted;


}

SubscriptionType Map::subType() const {
  return SubscriptionType::map;
}


// returns a pointer to the current player on map
Player* Map::getPlayerPtr(){
    return p;
}

ostream &operator<<(ostream &out, const Map &m){

    if(m.td == nullptr) {
        out << "display failed to initialize";
        return out;
    }

    out << *(m.td);
    return out;
}