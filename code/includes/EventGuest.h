#ifndef EVENTGUEST_H
#define EVENTGUEST_H

#include "Guest.h"
#include "GuestFactory.h"

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
	std::string getFullId() const override;
	std::shared_ptr<Guest> clone() const override;
    std::string getSummary() const override;

	//parsing
	static std::shared_ptr<Guest> createFromInput(const std::string& name, const std::string& id);
	static std::shared_ptr<Guest> createFromCSV(const std::string& name, const std::string& fullId);


};

#endif // EVENTGUEST_H
