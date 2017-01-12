#include "game.h"
#include "map.h"
#include "itemtype.h"
#include "mapstate.h"

using namespace std;

Game::Game(string inputLayout, string cl):BEGINNING_FLOOR(1), WINNING_FLOOR(5), p(nullptr){
    mapLayout = inputLayout;
    chamberLayout = cl;
    currentFloor = BEGINNING_FLOOR;
    m.reserve(5);
    m.emplace_back(Map{});
};

Game::~Game(){
};

void Game::init(string playerRace) {
    m.back().init(mapLayout, chamberLayout, currentFloor);
    m.back().spawnPlayer(playerRace);
    m.back().spawnStair();
    m.back().spawnItems(itemType::potion, 10);
    m.back().spawnItems(itemType::gold, 10);
    m.back().spawnEnemies();
}

int Game::changeFloor(int change){

    p = m.back().getPlayerPtr();

    p->dettach(&m.back());
    p->leaveMap();

    if(currentFloor == WINNING_FLOOR) return p->getGold();

    currentFloor++;

    m.emplace_back(Map());
    m.back().init(mapLayout, chamberLayout, currentFloor);
    m.back().spawnPlayer(p);
    m.back().spawnStair();
    m.back().spawnItems(itemType::potion, 10);
    m.back().spawnItems(itemType::gold, 10);
    m.back().spawnEnemies();

    return -1;
}

void Game::movePlayer(int dx, int dy){
    m.back().movePlayer(dx, dy);
}

void Game::movePlayer(string direction){
    m.back().movePlayer(direction);
}

void Game::attack(string direction){
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

    m.back().attack(dx, dy);
}

// turns the game to the next frame and return the status of the game
int Game::nextTurn(){

    mapState s = m.back().nextTurn();

    if(s == mapState::normal) return 1;

    if(s == mapState::playerDead) return 0;

    return -1;

}

void Game::usePotion(string direction){

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

    m.back().usePotion(dx, dy);
}

void Game::update(Subject &whoNotified) {
    Game::changeFloor(1);
}

SubscriptionType Game::subType() const {
  return SubscriptionType::game;
}

ostream &operator<<(ostream &out, const Game &g){

    if(g.m.empty()) {
        out << "map failed to load" << endl;
        return out;
    }

    out << g.m.back();
    return out;
}