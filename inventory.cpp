#include "inventory.h"

Inventory::Inventory(int s) : size(s), top(-1) {
    items = new Item*[size];
}

Inventory::~Inventory() {
    for (int i = 0; i <= top; i++) delete items[i];
    delete[] items;
}

bool Inventory::isempty() {
    return top == -1;
}

void Inventory::resize() {
    int newSize = size * 2;
    Item** newitems = new Item*[newSize];
    for (int i = 0; i <= top; i++) newitems[i] = items[i];
    delete[] items;
    items = newitems;
    size = newSize;
}

void Inventory::additem(Item* value) {
    if (top == size - 1) resize();
    items[++top] = value;
    cout << "Added: " << value->getName() << " to inventory" << endl;
}

void Inventory::removeitem() {
    if (isempty()) {
        cout << "No item is in the inventory" << endl;
        return;
    }
    cout << "Removed " << items[top]->getName() << " from inventory" << endl;
    top--;
}

Item* Inventory::gettopitem() {
    if (isempty()) {
        cout << "Inventory is empty" << endl;
        return nullptr;
    }
    return items[top];
}

void Inventory::showInventory() {
    if (isempty()) {
        cout << "Inventory is empty" << endl;
        return;
    }
    cout << "Items in Inventory: ";
    for (int i = top; i >= 0; i--) cout << items[i]->getName() << " ";
    cout << endl;
}
