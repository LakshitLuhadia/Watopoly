#ifndef CHANCESQUARE_H
#define CHANCESQUARE_H
#include "Nonproperty.h"
#include <vector>
#include <memory>
#include <string>


class ChanceSquare : public NonProperty {
    public:
        // ctor
        ChanceSquare(const std::string name, const int index, const bool isProperty);

        // Performs the action of the property
        void performAction(std::shared_ptr<Player> player) const override;
};

#endif

