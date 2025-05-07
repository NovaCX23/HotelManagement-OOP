#ifndef EVENTGUEST_H
#define EVENTGUEST_H

#include "Guest.h"

class EventGuest : public Guest {
    std::string eventName;
    int expectedGuests;
    int eventDays;
    bool isCatered;

public:
    EventGuest(const std::string& name,const std::string& id,const std::string& eventName,
               int expectedGuests,int eventDays,bool isCatered);

    // Override
    std::string getType() const override;
    double guestDiscount(int nights) const override;
    std::map<std::string, double> getAvailableBenefits() const override;
    std::vector<std::string> excludedBenefits() const override;
    bool isEligibleForBenefit(const std::string& benefitName) const override;
    bool isValidId() const override;


    std::string getEventSummary() const;
};

#endif // EVENTGUEST_H
