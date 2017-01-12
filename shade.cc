#include "shade.h"
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

Shade::Shade(Cell* spawnedIn, int x, int y): Player(spawnedIn, x, y){
    Player::init(125, 25, 25);
    Character::setHPBoundary(0, 125);
};

Shade::~Shade(){};

void Shade::attack(Enemy& e) {
    e.beAttackedBy(*this);
};

void Shade::beAttackedBy (Human& h) {

    int damage = ceil(100.0 / (100 + Character::def)) * h.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
}

void Shade::beAttackedBy (Dwarf& d) {

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
}

void Shade::beAttackedBy(Halfling& l) {
    int damage = ceil(100.0 / (100 + Character::def)) * l.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
};

void Shade::beAttackedBy(Elf& e) {
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

void Shade::beAttackedBy(Orcs& o) {
    int damage = ceil(100.0 / (100 + Character::def)) * o.getAtk();

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);



    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
};

void Shade::beAttackedBy(Merchant& m) {
    int damage = ceil(100.0 / (100 + Character::def)) * m.getAtk();

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

int Shade::getGold() {
    return Player::gold * 1.5;
}

string Shade::objectType() const {
    return "Shade";
}


Info Shade::getInfo() const {
    return Info{-1, -1, true, '@', ' ', nullptr, "Shade", Character::hp, Character::atk, Character::def, Player::gold};
}
