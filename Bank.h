#ifndef BANK_H
#define BANK_H

// Bank class
class Bank {
    static int money; // Total money in the bank

    public:
        // Ctor for Bank
        Bank();

        // Dtor for Bank
        ~Bank();

        // Getters
        // Returns the total money in the bank
        static int getMoney();

        // Setters
        // Adds amount to the bank
        static void addMoney(int amount);

        // Subtracts amount from the bank
        static void subtractMoney(int amount);
};

#endif