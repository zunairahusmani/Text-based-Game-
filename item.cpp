#include "item.h"
#include <iostream>
using namespace std;

void energydrink::use(player& p) {
    p.energydrinkInc(30);
    cout << "You drank the energy drink. Your health is now " << p.getHealth() << endl;
}

string energydrink::getName() const {
    return "energydrink";
}

void oxygenmask::use(player& p) {
    p.addhealth(20);
    cout << "You used an oxygen mask. Your oxygen is now " << p.getOxygenlevel() << endl;
}

string oxygenmask::getName() const {
    return "Oxygen Mask";
}
