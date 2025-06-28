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
    std::string getFullId() const override;
    std::shared_ptr<Guest> clone() const override;
    std::string getSummary() const override;

    //parsing
    static std::shared_ptr<Guest> createFromInput(const std::string& name, const std::string& id);
    static std::shared_ptr<Guest> createFromCSV(const std::string& name, const std::string& fullId);

};

#endif // VIPGUEST_H
