#ifndef FEESSQUARE_H
#define FEESSQUARE_H
#include "Nonproperty.h"
#include <vector>
#include <memory>
#include <string>


class FeesSquare : public NonProperty {
    int fees;
    public:
        // ctor
        FeesSquare(const std::string name, const int index, const bool isProperty, int fees);
        // Performs the action of the property
        void performAction(std::shared_ptr<Player>& player) const override;
};

#endif

