#include "potion.h"

Potion::Potion(potionType p, int val):t(itemType::potion), p(p), value(val){};
Potion::~Potion(){};

potionType Potion::getType() {
    return p;
}

int Potion::getValue() {
    return value;
}

void Potion::setValue(int v) {
    value = v;
}

char Potion::getFieldIdentity(){
    return 'P';
}


string Potion::objectType() const {
    return "Potion";
}
