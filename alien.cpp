#include "alien.h"
#include <iostream>
using namespace std;

alien::alien(string n, int d) : aname(n), adamage(d) {}

string alien::getaname() const {
    return aname;
}

void alien::playerATTACKED(player& p) {
    cout << "You got attacked by " << aname << " and you took " << adamage << " damage!" << endl;
    p.takeDamage(adamage);
}

alienlist::alienlist(int cap, int s) : capacity(cap), size(s) {
    aliens = new alien*[capacity];
}

alienlist::~alienlist() {
    for (int i = 0; i < size; i++) delete aliens[i];
    delete[] aliens;
}

void alienlist::resize() {
    capacity *= 2;
    alien** newlist = new alien*[capacity];
    for (int i = 0; i < size; i++) newlist[i] = aliens[i];
    delete[] aliens;
    aliens = newlist;
}

void alienlist::addalien(const alien& a) {
    if (size == capacity) resize();
    aliens[size++] = new alien(a);
}

void alienlist::removeAlien() {
    if (size == 0) {
        cout << "No aliens to remove" << endl;
        return;
    }
    delete aliens[0];
    for (int i = 0; i < size - 1; i++) aliens[i] = aliens[i + 1];
    size--;
    cout << "Alien defeated " << endl;
}

bool alienlist::hasalien() const {
    return size > 0;
}
