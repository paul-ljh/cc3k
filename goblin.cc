#include "goblin.h"
#include "enemy.h"
#include <cmath>
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orcs.h"
#include "merchant.h"
#include <iostream>

using namespace std;

Goblin::Goblin(Cell* spawnedIn, int x, int y): Player(spawnedIn, x, y),perRob(5){
    Player::init(110, 15, 20);
    Character::setHPBoundary(0, 110);
};

Goblin::~Goblin(){};

void Goblin::rob(){
    Player::gold+=perRob;
    notifyObservers(SubscriptionType::textDisplay);
}

void Goblin::attack(Enemy& e) {
    e.beAttackedBy(*this);
};

void Goblin::beAttackedBy (Human& h) {

    int damage = ceil(100.0 / (100 + Character::def)) * h.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
}

void Goblin::beAttackedBy (Dwarf& d) {

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
}

void Goblin::beAttackedBy(Halfling& l) {
    int damage = ceil(100.0 / (100 + Character::def)) * l.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
};

void Goblin::beAttackedBy(Elf& e) {
    int damage = ceil(100.0 / (100 + Character::def)) * e.getAtk();

    // elf gets two attacks against every race except drow
    for (int i = 0; i < 2; ++i) {
        if (rand() / 2 == 0) {
            damage = 0;
        }
        Character::hp-=damage;
        if(Character::hp < 0) Character::hp = 0;
        notifyObservers(SubscriptionType::textDisplay);
    }


    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
};

void Goblin::beAttackedBy(Orcs& o) {
    int damage = ceil(100.0 / (100 + Character::def)) * o.getAtk();

    // elf gets two attacks against every race except drow
    for (int i = 0; i < 2; ++i) {
        if (rand() / 2 == 0) {
            damage = 0;
        }
        Character::hp-=damage;
        if(Character::hp < 0) Character::hp = 0;
        notifyObservers(SubscriptionType::textDisplay);
    }


    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
};

void Goblin::beAttackedBy(Merchant& m) {
    int damage = ceil(100.0 / (100 + Character::def)) * m.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
};

int Goblin::getGold() {
    return Player::gold;
}

string Goblin::objectType() const {
    return "Goblin";
}


Info Goblin::getInfo() const {
    return Info{-1, -1, true, '@', ' ', nullptr, "Goblin", Character::hp, Character::atk, Character::def, Player::gold};
}
