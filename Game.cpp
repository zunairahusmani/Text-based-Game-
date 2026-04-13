#include "game.h"
#include <iostream>
using namespace std;

game::game(bool p, int c, bool rs, bool ca) :
    ispathchoosen(p), currentportal(c), repeardthesystem(rs), cap(ca) {}

game::~game() {}

void game::addportal(int portalnum, string desc, string alienname, int dam, string itemtype, bool hascap) {
    Item* item = nullptr;
    if (itemtype == "energydrink") item = new energydrink();
    if (itemtype == "oxygenmask") item = new oxygenmask();

    station[portalnum] = portals(desc, alienname, dam, hascap);
    if (!alienname.empty()) aliens.addalien(alien(alienname, dam));
    if (item) station[portalnum].setItem(item);
}

void game::connection(int from, int to) {
    p_connection[from].push_back(to);
}

void game::repairSystem(int t) {
    if (t == 0) {
        cout << "System repair failed." << endl;
        return;
    }
    string input;
    cout << "Type 'fix' ";
    cin >> input;
    if (input == "fix") {
        cout << "System repaired!\n";
        repeardthesystem = true;
    } else {
        cout << "Incorrect. Try again.\n";
        repairSystem(t - 1);
    }
}

void game::playgame(player& Player) {
    while (Player.getHealth() > 0 && Player.getOxygenlevel() > 0) {
        portals& current = station[currentportal];
        cout << "Portal " << currentportal << ": " << current.getDesc() << endl;

        if (current.getItem()) {
            cout << "You found a " << current.getItem()->getName() << " in this portal!" << endl;
            inv.additem(current.getItem());
            current.setItem(nullptr);
        }

        if (currentportal == 1 && !repeardthesystem) {
            cout << "Radio is broken. Fix it to proceed.\n";
            repairSystem(2);
            if (!repeardthesystem) {
                cout << "Failed to repair. Game Over.\n";
                break;
            }
            currentportal++;
            continue;
        }

        if (currentportal == 2 && !ispathchoosen) {
            cout << "Choose: blackhole (b) or zero gravity corridor (g): ";
            string ans; cin >> ans;
            if (ans == "b") {
                cout << "Lost in space. Game over.\n"; return;
            }
            else if (ans == "g") {
                cout << "10 damage taken.\n";
                try {
                    Player.takeDamage(10);
                    Player.status();
                } catch (const runtime_error& e) {
                    cout << e.what() << endl; return;
                }
                ispathchoosen = true;
            } else {
                cout << "Invalid input.\n"; continue;
            }
        }

        if (!current.getAlienName().empty() && aliens.hasalien()) {
            cout << "You are attacked by " << current.getAlienName() << ". Fight? (y/n): ";
            string choice; cin >> choice;
            if (choice == "y") {
                cout << "You killed the alien.\n";
                aliens.removeAlien();
                try {
                    Player.takeDamage(current.getDamage());
                    Player.status();
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                    return;
                }
            } else if (choice == "n") {
                cout << "You ran away.\n";
            } else {
                cout << "Invalid choice.\n"; continue;
            }
        }

        if (current.gethascaptain()) {
            cap = true;
            cout << "You found the Captain!\n";
        }

        if (cap) {
            cout << "You escaped with the Captain. You win!\n";
            return;
        }

        showmenu(Player);
    }
}

void game::showmenu(player& Player) {
    int choice;
    do {
        cout << "\nWhat next?\n1. Go forward\n2. Show inventory\n3. Show status\n4. Show map\n5. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: currentportal++; break;
            case 2:
                inv.showInventory();
                if (!inv.isempty()) {
                    cout << "Use top item? (y/n): ";
                    string ans; cin >> ans;
                    if (ans == "y") {
                        Item* item = inv.gettopitem();
                        if (item) {
                            item->use(Player);
                            inv.removeitem();
                        }
                    }
                }
                break;
            case 3: Player.status(); break;
            case 4:
                for (auto& entry : p_connection) {
                    cout << entry.first << " connects to: ";
                    for (int to : entry.second) cout << to << " ";
                    cout << endl;
                }
                break;
            case 5:
                cout << "You quit the game. Coward.\n";
                exit(0);
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 1);
}
