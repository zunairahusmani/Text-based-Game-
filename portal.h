#ifndef PORTAL_H
#define PORTAL_H

#include <string>
#include <iostream>
#include "item.h"
using namespace std;

class portals {
private:
    string desc;
    string alienname;
    int dam;
    Item* item;
    bool hascaptain;

public:
    portals(string d, string an, int da, bool hs = false);
    portals();  // default constructor
    ~portals();

    string getDesc() const;
    string getAlienName() const;
    int getDamage() const;
    Item* getItem() const;
    bool gethascaptain() const;
    void setItem(Item* i);
};

#endif
