#include "../includes/Guest.h"
#include "../includes/VIPGuest.h"
#include "../includes/CorporateGuest.h"
#include "../includes/EventGuest.h"
#include "../includes/InfluencerGuest.h"
#include "../includes/Exceptions.h"
#include <cctype>

// Constructor
Guest::Guest(const std::string& name, const std::string& id)
    : name(name), id(id) {}

// Getters
const std::string& Guest::getName() const {
    return name;
}

const std::string& Guest::getId() const {
    return id;
}

std::vector<std::string> Guest::getFreeBenefits() const {
    std::vector<std::string> free;
    const auto& benefits = getAvailableBenefits();

    for (const auto& [benefitName, price] : benefits) {
        if (price == 0.0)
            free.push_back(benefitName);
    }
    return free;
}


// Virtuals
bool Guest::isValidId() const {
    if (id.length() != 6) return false;
    for (int i = 0; i < 3; ++i) {
        if (!isalpha(id[i])) return false;
    }
    for (int i = 3; i < 6; ++i) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

std::string Guest::getFullId() const {
    return id;
}

std::string Guest::getType() const {
    return "Standard";
}
std::string Guest::getSummary() const {
    return "Standard guest with no special benefits.";
}




double Guest::guestDiscount(int nights) const {
    return (nights >= 5) ? 0.05 : 0.0;
}

std::map<std::string, double> Guest::getStandardBenefitPrices() {
    return {
            {"Lounge access", 30.0},
            {"Spa access", 50.0},
            {"Minibar included", 25.0},
            {"Room upgrade", 35.0},
            {"Late checkout", 20.0},
            {"Early check-in", 20.0},
            {"Private dining", 15.0},
            {"Free airport transfer", 40.0},
            {"Laundry service", 10.0},
            {"Welcome gift", 10.0},
            {"Free cancellation", 15.0},
            {"Event hall access", 200.0},
            {"Special decor setup", 150.0},
            {"Sound & lighting system", 180.0}
    };
}



std::map<std::string, double> Guest::getAvailableBenefits() const {
    return getStandardBenefitPrices();
}


bool Guest::isEligibleForBenefit(const std::string& benefitName) const {
    return getAvailableBenefits().contains(benefitName);
}

std::vector<std::string> Guest::excludedBenefits() const{
    return {};
}

// Functions

void Guest::displayBenefits() const {
    auto benefits = getAvailableBenefits();
    if (benefits.empty()) {
        std::cout << "No benefits available.\n";
        return;
    }

    bool hasFree = false, hasPaid = false;

    for (const auto& [benefitName, price] : benefits) {
        if (price == 0.0) hasFree = true;
        else hasPaid = true;
    }

    if (hasFree) {
        std::cout << "Included benefits:\n";
        for (const auto& [benefitName, price] : benefits) {
            if (price == 0.0)
                std::cout << "- " << benefitName << "\n";
            }
    }
    if (hasPaid) {
        std::cout << "Optional (paid) benefits:\n";
        for (const auto& [benefitName, price] : benefits) {
          if (price > 0.0)
              std::cout << "- " << benefitName << ": $" << price << "\n";
        }
    }
}


 std::shared_ptr<Guest>Guest::clone() const {
    return std::make_shared<Guest>(*this);
}


// Operators
std::ostream& operator<<(std::ostream& os, const Guest& guest) {
    os << "Guest name: " << guest.getName()
       << ", Guest ID: " << guest.getId()
       << ", Category: " << guest.getType();
    return os;
}