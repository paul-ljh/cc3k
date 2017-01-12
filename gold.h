#ifndef __GOLD_H__
#define __GOLD_H__

#include "itemtype.h"
#include "item.h"

class Gold : public Item {
protected:
    itemType t;
    int value;

public:
    Gold(int);
    ~Gold();

    int getValue();

    char getFieldIdentity() override;

    string objectType() const override;
};

#endif