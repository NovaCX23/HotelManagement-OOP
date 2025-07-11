#ifndef CORPORATEGUEST_H
#define CORPORATEGUEST_H

#include "Guest.h"
#include "GuestFactory.h"

class CorporateGuest : public Guest {
    std::string companyName;
    int nrEmployees;

public:
    CorporateGuest(const std::string& name,const std::string& id,const std::string& companyName,int nrEmployees);

    //override
    std::string getType() const override;
    double guestDiscount(int nights) const override;
    std::map<std::string, double> getAvailableBenefits() const override;
    std::vector<std::string> excludedBenefits() const override;
    bool isEligibleForBenefit(const std::string& benefitName) const override;
    bool isValidId() const override;
    std::string getFullId() const override;
    std::shared_ptr<Guest> clone() const override;
    std::string getSummary() const override;

    //parsing
    static std::shared_ptr<Guest> createFromInput(const std::string& name, const std::string& id);
    static std::shared_ptr<Guest> createFromCSV(const std::string& name, const std::string& fullId);


};

#endif // CORPORATEGUEST_H
