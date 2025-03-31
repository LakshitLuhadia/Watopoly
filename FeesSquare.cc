#include "FeesSquare.h"
#include <memory>
#include <vector>
#include <string>
#include "Academic.h"
using namespace std;

// ctor
FeesSquare::FeesSquare(const string name, const int index, const bool isProperty, int fees) : NonProperty{name, index, isProperty}, fees{fees} {}

// performAction for FeesSquare
void FeesSquare::performAction(shared_ptr<Player>& player) const {
    if (getName() == "TUITION") {
        int totSavings = player->getMoney();
        vector<shared_ptr<Property>> properties = player->getProperties();
        for (const auto& property : properties) {
            if (property->getIsAcademic()) {
                shared_ptr<Academic> academicBuilding = dynamic_pointer_cast<Academic>(property);
                totSavings += academicBuilding->getCost();
                for (int i = 0; i < academicBuilding->getNumImprovements(); ++i) {
                    totSavings += academicBuilding->getImprovementCost();
                }
            } else {
                totSavings += property->getCost();
            }
        }
        cout << "Your total savings are " << totSavings << "!" << endl;
        totSavings = 0.1 * totSavings;
        if (totSavings > fees) {
            cout << "You have to pay the fee of " << fees << "." << endl;
            player->subtractMoney(fees);
        } else {
            cout << "You have to pay 10\% of your total savings: " << totSavings << "." << endl;
            player->subtractMoney(totSavings);
        }
    } else {
        cout << "You have to pay the fee of " << fees << "." << endl;
        player->subtractMoney(fees);
    }
}

