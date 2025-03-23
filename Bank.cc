#include "Bank.h"

// Constructor for Bank
int Bank::money = 0; // Bank::Bank

// Destructor for Bank
Bank::~Bank() {} // Bank::~Bank

// Returns the total money in the bank
int Bank::getMoney() {
    return money;
} // Bank::getMoney

// Adds amount to the bank
void Bank::addMoney(int amount) {
    money += amount;
} // Bank::addMoney

// Subtracts amount from the bank
void Bank::subtractMoney(int amount) {
    money -= amount;
} // Bank::subtractMoney