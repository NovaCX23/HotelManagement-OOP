#include "../includes/EventGuest.h"
#include <sstream>
#include <vector>

EventGuest::EventGuest(const std::string& name, const std::string& id,const std::string& eventName,
                       int expectedGuests, int eventDays, bool isCatered)
    : Guest(name, id),eventName(eventName),expectedGuests(expectedGuests),
      eventDays(eventDays),isCatered(isCatered) {}

std::string EventGuest::getType() const {
    return "Event";
}

double EventGuest::guestDiscount(int nights) const {
    double discount = 0.0;
    if (expectedGuests >= 100) discount = 0.15;
    else if (eventDays >= 2) discount = 0.10;

    if (nights > eventDays) discount += 0.05; // extra dacă stau și în afara evenimentului
    return discount;
}

std::vector<std::string> EventGuest::excludedBenefits() const {
    return {
        "Welcome gift",
        "Minibar included",
        "Room upgrade",
        "Spa access"
    };
}

std::map<std::string, double> EventGuest::getAvailableBenefits() const {
    auto all = Guest::getAvailableBenefits();
    for (const auto& key : excludedBenefits()) {
        all.erase(key);
    }

    all["Event hall access"] = 0.0;
    all["Special decor setup"] = 0.0;
    all["Sound & lighting system"] = 0.0;

    return all;
}

bool EventGuest::isEligibleForBenefit(const std::string& benefitName) const {
    for (const auto& b : excludedBenefits()) {
        if (b == benefitName)
            return false;
    }
    return Guest::isEligibleForBenefit(benefitName);
}

bool EventGuest::isValidId() const {
    return id.substr(0, 3) == "EVT" && Guest::isValidId();
}

std::string EventGuest::getFullId() const {
    std::ostringstream oss;
    oss << id << "|" << eventName << "|" << expectedGuests
        << "|" << eventDays << "|" << (isCatered ? "1" : "0");
    return oss.str();
}


std::string EventGuest::getSummary() const {
    std::ostringstream oss;
    oss << "Event: " << eventName
        << " - " << expectedGuests << " guest" << (expectedGuests != 1 ? "s" : "")
        << " over " << eventDays << " day" << (eventDays != 1 ? "s" : "");
    if (isCatered) oss << ", catering included";
    return oss.str();
}

std::shared_ptr<Guest> EventGuest::clone() const {
    return std::make_shared<EventGuest>(*this);
}
