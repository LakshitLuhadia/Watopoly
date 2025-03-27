#ifndef TIMSLINESQUARE_H
#define TIMSLINESQUARE_H
#include "Nonproperty.h"
#include <vector>
#include <memory>
#include <string>

class TimsLineSquare : public NonProperty {
    int bailCost; // Bail Cost of TimsLine
    public:
        // ctor
        TimsLineSquare(const std::string name, const int index, const bool isProperty);
        // Performs the action of the property
        void performAction(std::shared_ptr<Player> player) const override;
};

#endif

