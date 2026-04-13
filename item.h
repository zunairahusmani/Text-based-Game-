#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "player.h"
using namespace std;

class Item {
public:
    virtual void use(player& p) = 0;
    virtual string getName() const = 0;
    virtual ~Item() {}
};

class energydrink : public Item {
public:
    void use(player& p) override;
    string getName() const override;
};

class oxygenmask : public Item {
public:
    void use(player& p) override;
    string getName() const override;
};

#endif
