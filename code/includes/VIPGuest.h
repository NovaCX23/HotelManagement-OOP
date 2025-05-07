#ifndef VIPGUEST_H
#define VIPGUEST_H

#include "Guest.h"

class VIPGuest : public Guest {
    std::string tier;
public:
    VIPGuest(const std::string& name, const std::string& id, const std::string& tier);

    // override
    double guestDiscount(int nights) const override;
    std::string getType() const override;
    std::map<std::string, double> getAvailableBenefits() const override;
    bool isValidId() const override;
};

#endif // VIPGUEST_H
