#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

// Administration class
class Administration {
    static int money; // Total money in the administration

    public:
        // Ctor for Administration
        Administration();

        // Getters
        // Returns the total money in the administration
        static int getMoney();

        // Setters
        // Adds amount to the administration
        static void addMoney(int amount);

        // Subtracts amount from the administration
        static void subtractMoney(int amount);
};

#endif