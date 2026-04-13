#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>
#include <string>
#include "portal.h"
#include "inventory.h"
#include "alien.h"

class game {
private:
    map<int, portals> station;
    map<int, vector<int>> p_connection;
    Inventory inv;
    alienlist aliens;
    bool ispathchoosen;
    int currentportal;
    bool repeardthesystem;
    bool cap;

    void repairSystem(int t);
    void showmenu(player& Player);

public:
    game(bool p = false, int c = 1, bool rs = false, bool ca = false);
    ~game();

    void addportal(int portalnum, string desc, string alienname, int dam, string itemtype = "", bool hascap = false);
    void connection(int from, int to);
    void playgame(player& Player);
};

#endif
