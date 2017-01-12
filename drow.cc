#include "drow.h"
#include "enemy.h"
#include <cmath>
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orcs.h"
#include "merchant.h"
#include "potion.h"
#include <iostream>

using namespace std;

Drow::Drow(Cell* spawnedIn, int x, int y): Player(spawnedIn, x, y){
    Player::init(150, 25, 15);
    Character::setHPBoundary(0, 150);
};

Drow::~Drow(){};

void Drow::usePotion(Potion* p) {

    p->setValue(p->getValue());
    Player::usePotion(p);

}

void Drow::attack(Enemy& e) {
    e.beAttackedBy(*this);
};

void Drow::beAttackedBy (Human& h) {

    int damage = ceil(100.0 / (100 + Character::def)) * h.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
}

void Drow::beAttackedBy (Dwarf& d) {

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
}

void Drow::beAttackedBy(Halfling& l) {
    int damage = ceil(100.0 / (100 + Character::def)) * l.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
};

void Drow::beAttackedBy(Elf& e) {
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

void Drow::beAttackedBy(Orcs& o) {
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

void Drow::beAttackedBy(Merchant& m) {
    int damage = ceil(100.0 / (100 + Character::def)) * m.getAtk();
    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

    cout << "my hp is now " << Character::hp << endl;
};

int Drow::getGold() {
    return Player::gold;
}

string Drow::objectType() const {
    return "Drow";
}


Info Drow::getInfo() const {
    return Info{-1, -1, true, '@', ' ', nullptr, "Drow", Character::hp, Character::atk, Character::def, Player::gold};
}
