#include "player.h"
#include <iostream>
#include <stdexcept>
using namespace std;

player::player(string n, int h, int ol) : name(n), health(h), oxygenlevel(ol) {}

int player::getHealth() const { return health; }
int player::getOxygenlevel() const { return oxygenlevel; }

void player::addhealth(int h) {
    oxygenlevel += h;
    if (oxygenlevel > 100) oxygenlevel = 100;
}

void player::energydrinkInc(int energy) {
    health += energy;
    if (health > 100) health = 100;
}

void player::takeDamage(int damage) {
    health -= damage;
    oxygenlevel -= damage;
    if (oxygenlevel <= 20)
        throw runtime_error("You couldn't survive. You died. Game over.");
}

void player::status() const {
    cout << "Your health is: " << health << "% and Your oxygen is " << oxygenlevel << "%\n";
}
