#ifndef OSAPSQUARE_H
#define OSAPSQUARE_H
#include "Nonproperty.h"
#include <vector>
#include <memory>
#include <string>


class OSAPSquare : public NonProperty {
    int collectAmount; // Amount to collect for OSAP
    public:
        // ctor for OSAPSquare
        OSAPSquare(const std::string name, const int index, const bool isProperty);
        // Performs the action of the property
        void performAction(std::shared_ptr<Player>& player) const override;
};

#endif

