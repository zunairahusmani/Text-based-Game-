#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class player {
private:
    string name;
    int health, oxygenlevel;

public:
    player(string n, int h = 100, int ol = 100);
    int getHealth() const;
    int getOxygenlevel() const;
    void addhealth(int h);
    void energydrinkInc(int energy);
    void takeDamage(int damage);
    void status() const;
};

#endif
