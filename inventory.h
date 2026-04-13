#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "item.h"
using namespace std;

class Inventory {
public:
    Item** items;
    int top;
    int size;

    Inventory(int s = 5);
    ~Inventory();

    void additem(Item* value);
    void removeitem();
    void resize();
    Item* gettopitem();
    void showInventory();
    bool isempty();
};

#endif
