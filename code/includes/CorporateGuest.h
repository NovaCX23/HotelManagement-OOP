#ifndef CORPORATEGUEST_H
#define CORPORATEGUEST_H

#include "Guest.h"

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



    const std::string getCompanyName() const { return companyName; }
    int getNrEmployees() const { return nrEmployees; }
    std::string getSummary() const;
};

#endif // CORPORATEGUEST_H
