#include <iostream>
#include "game.h"

int main() {
    string name;
    cout << "--------------------------------------" << endl;
    cout << "     WELCOME TO DARK SIDE STATION     " << endl;
    cout << "--------------------------------------" << endl;
    cout << "Enter your name to begin: ";
    cin >> name;

    player Player(name);
    game Game;

    Game.addportal(1, "You awaken to a broken station...", "", 0, "oxygenmask");
    Game.addportal(2, "Two identical pathways appear...", "", 0, "energydrink");
    Game.addportal(3, "A monstrous alien blocks your path.", "WAR HAMMER", 30);
    Game.addportal(4, "Another portal... another alien.", "alien x", 40);
    Game.addportal(5, "You reach the control deck... a voice?", "", 0, "", true);

    Game.connection(1, 2);
    Game.connection(2, 3);
    Game.connection(3, 4);
    Game.connection(4, 5);

    Game.playgame(Player);
    return 0;
}
