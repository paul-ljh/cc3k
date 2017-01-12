#ifndef __POTION_H__
#define __POTION_H__

#include "itemtype.h"
#include "potiontype.h"
#include "item.h"

class Potion : public Item {
protected:
    itemType t;
    potionType p;
    int value;

public:
    Potion(potionType, int);
    ~Potion();

    potionType getType();
    int getValue();

    void setValue(int);

    char getFieldIdentity() override;

    string objectType() const override;
};

#endif