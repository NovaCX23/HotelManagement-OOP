#include "../includes/Guest.h"
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

std::string Guest::getType() const {
    return "Standard";
}

double Guest::guestDiscount(int nights) const {
    return (nights >= 5) ? 0.05 : 0.0;
}

std::map<std::string, double> Guest::getAvailableBenefits() const {
    return {
            {"Lounge access", 30.0},
            {"Spa access", 50.0},
            {"Minibar included", 25.0},
            {"Room upgrade", 35.0},
            {"Late checkout", 20.0},
            {"Early check-in", 20.0},
            {"Premium menu", 15.0},
            {"Free airport transfer", 40.0},
            {"Meeting room access", 30.0},
            {"Laundry service", 10.0},
            {"Welcome gift", 10.0},
            {"Free cancellation", 15.0}
    };
}

bool Guest::hasFreeBenefit(const std::string& benefitName) const {
    auto benefits = getAvailableBenefits();
    auto it = benefits.find(benefitName);
    return it != benefits.end() && it->second == 0.0;
}

bool Guest::isEligibleForBenefit(const std::string& benefitName) const {
    return getAvailableBenefits().count(benefitName) > 0;
}

void Guest::displayBenefits() const {
    auto benefits = getAvailableBenefits();
    if (benefits.empty()) {
        std::cout << "No benefits available.\n";
        return;
    }
    std::cout << "Available benefits (standard rates):\n";
    for (const auto& [name, price] : benefits) {
        std::cout << "- " << name << ": $" << price << "\n";
    }
}


// Operators
std::ostream& operator<<(std::ostream& os, const Guest& guest) {
    os << "Guest name: " << guest.getName()
       << ", Guest ID: " << guest.getId()
       << ", Category: " << guest.getType();
    return os;
}