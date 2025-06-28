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

// Parsing
std::shared_ptr<Guest> EventGuest::createFromInput(const std::string& name, const std::string& id) {
    std::string eventName;
    int expectedGuests, eventDays;
    char catering;
    bool isCatered;

    std::cout << "Enter event name: ";
    std::getline(std::cin >> std::ws, eventName);
    std::cout << "Expected number of guests: ";
    std::cin >> expectedGuests;
    std::cout << "Event duration (days): ";
    std::cin >> eventDays;
    std::cout << "Is catering included? (y/n): ";
    std::cin >> catering;
    isCatered = (catering == 'y' || catering == 'Y');

    auto guest = std::make_shared<EventGuest>(name, id, eventName, expectedGuests, eventDays, isCatered);
    if (!guest->isValidId()) {
        throw InvalidGuestIdException(id);
    }
    return guest;
}

std::shared_ptr<Guest> EventGuest::createFromCSV(const std::string& name, const std::string& fullId) {
    auto parts = GuestFactory::split(fullId, '|');
    std::string raw_id = parts[0];
    std::string eventName = (parts.size() >= 2) ? parts[1] : "Event";
    int expectedGuests = (parts.size() >= 3) ? std::stoi(parts[2]) : 1;
    int eventDays = (parts.size() >= 4) ? std::stoi(parts[3]) : 1;
    bool isCatered = (parts.size() >= 5) ? (parts[4] == "1" || parts[4] == "y" || parts[4] == "true") : false;

    auto guest = std::make_shared<EventGuest>(name, raw_id, eventName, expectedGuests, eventDays, isCatered);
    if (!guest->isValidId()) {
        throw InvalidGuestIdException(raw_id);
    }
    return guest;
}