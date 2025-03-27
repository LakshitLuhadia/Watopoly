#ifndef OSAPSQUARE_H
#define OSAPSQUARE_H
#include "Nonproperty.h"
#include <vector>
#include <memory>

class OSAPSquare : public NonProperty {
    int collectAmount;
    public:
        // ctor
        OSAPSquare();
        // Performs the action of the property
        void performAction(std::shared_ptr<Player> player) const override;
};

#endif

