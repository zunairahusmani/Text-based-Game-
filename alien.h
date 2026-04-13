#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include "player.h"
using namespace std;

class alien {
private:
    string aname;
    int adamage;

public:
    alien(string n, int d);
    string getaname() const;
    void playerATTACKED(player& p);
};

class alienlist {
private:
    alien** aliens;
    int capacity;
    int size;
    void resize();

public:
    alienlist(int cap = 2, int s = 0);
    ~alienlist();
    void addalien(const alien& a);
    void removeAlien();
    bool hasalien() const;
};

#endif
