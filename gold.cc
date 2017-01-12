#include "gold.h"

Gold::Gold(int val):t(itemType::gold), value(val){};
Gold::~Gold(){};

int Gold::getValue() {
    return value;
}

char Gold::getFieldIdentity(){
    return 'G';
}

string Gold::objectType() const {
    return "Gold";
}