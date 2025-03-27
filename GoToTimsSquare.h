#ifndef GOTOTIMSSQUARE_H
#define GOTOTIMSSQUARE_H
#include "Nonproperty.h"
#include <vector>
#include <memory>
#include <string>

class GoToTimsSquare : public NonProperty {
    int timsLineIndex;
    public:
        // ctor
        GoToTimsSquare(const std::string name, const int index, const bool isProperty, int timsLineIndex);
        // Performs the action of the property
        void performAction(std::shared_ptr<Player> player) const override;
};

#endif
