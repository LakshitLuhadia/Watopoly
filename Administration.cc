#include "Administration.h"

// Constructor for Administration
int Administration::money = 0; // Administration::Administration

// Returns the total money in the administration
int Administration::getMoney() {
    return money;
} // Administration::getMoney

// Adds amount to the administration
void Administration::addMoney(int amount) {
    money += amount;
} // Administration::addMoney

// Subtracts amount from the administration
void Administration::subtractMoney(int amount) {
    money -= amount;
} // Administration::subtractMoney