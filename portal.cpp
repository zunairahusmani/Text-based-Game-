#include "portal.h"

portals::portals(string d, string an, int da, bool hs)
    : desc(d), alienname(an), dam(da), item(nullptr), hascaptain(hs) {}

portals::portals() : desc(""), alienname(""), dam(0), item(nullptr), hascaptain(false) {}

portals::~portals() {
    if (item) delete item;
}

string portals::getDesc() const { return desc; }
string portals::getAlienName() const { return alienname; }
int portals::getDamage() const { return dam; }
Item* portals::getItem() const { return item; }
bool portals::gethascaptain() const { return hascaptain; }

void portals::setItem(Item* i) {
    cout << "DEBUG: Setting item for portal" << endl;
    item = i;
}
