#include "../includes/Guest.h"
#include "../includes/VIPGuest.h"
#include "../includes/CorporateGuest.h"
#include "../includes/EventGuest.h"
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
            {"Private dining", 15.0},
            {"Free airport transfer", 40.0},
            {"Laundry service", 10.0},
            {"Welcome gift", 10.0},
            {"Free cancellation", 15.0}
    };
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

std::shared_ptr<Guest> Guest::createFromInput(const std::string& name, const std::string& id) {
    if (id.starts_with("VIP")) {
        std::string tier;
        std::cout << "Enter VIP tier (Bronze/Silver/Gold): ";
        std::cin >> tier;
        auto guest = std::make_shared<VIPGuest>(name, id, tier);
        if (!guest->isValidId()) {
            throw InvalidGuestIdException(id);
        }
        return guest;


    } else if (id.starts_with("COR")) {
        std::string companyName;
        int nrEmployees;
        std::cout << "Enter company name: ";
        std::getline(std::cin >> std::ws, companyName);
        std::cout << "Enter number of employees: ";
        std::cin >> nrEmployees;
        auto guest = std::make_shared<CorporateGuest>(name, id, companyName, nrEmployees);
        if (!guest->isValidId()) {
            throw InvalidGuestIdException(id);
        }
        return guest;


    } else if (id.starts_with("EVT")) {
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

    // Default: standard guest
    auto guest = std::make_shared<Guest>(name, id);
    if (!guest->isValidId()) {
        throw InvalidGuestIdException(id);
    }
    return guest;

}

std::shared_ptr<Guest> Guest::createFromCSV(const std::string& name, const std::string& id) {
    // Split id după '|'
    auto split = [](const std::string& s, char delim) {
        std::vector<std::string> out;
        std::string temp;
        for (char c : s) {
            if (c == delim) { out.push_back(temp); temp.clear(); }
            else temp += c;
        }
        out.push_back(temp);
        return out;
    };

    auto parts = split(id, '|');
    const std::string& raw_id = parts[0];

    if (raw_id.rfind("VIP", 0) == 0) {
        std::string tier = (parts.size() >= 2 && !parts[1].empty()) ? parts[1] : "Bronze";
        auto guest = std::make_shared<VIPGuest>(name, raw_id, tier);
        if (!guest->isValidId())
            throw InvalidGuestIdException(raw_id);
        return guest;

    } else if (raw_id.rfind("COR", 0) == 0) {
        std::string company = (parts.size() >= 2) ? parts[1] : "Unknown";
        int employees = (parts.size() >= 3) ? std::stoi(parts[2]) : 1;
        auto guest = std::make_shared<CorporateGuest>(name, raw_id, company, employees);
        if (!guest->isValidId())
            throw InvalidGuestIdException(raw_id);
        return guest;

    } else if (raw_id.rfind("EVT", 0) == 0) {
        std::string eventName = (parts.size() >= 2) ? parts[1] : "Event";
        int expectedGuests = (parts.size() >= 3) ? std::stoi(parts[2]) : 1;
        int eventDays = (parts.size() >= 4) ? std::stoi(parts[3]) : 1;
        bool isCatered = (parts.size() >= 5) ? (parts[4] == "1" || parts[4] == "y" || parts[4] == "true") : false;
        auto guest = std::make_shared<EventGuest>(name, raw_id, eventName, expectedGuests, eventDays, isCatered);
        if (!guest->isValidId())
            throw InvalidGuestIdException(raw_id);
        return guest;
    }
    // Standard guest
    auto guest = std::make_shared<Guest>(name, raw_id);
    if (!guest->isValidId())
        throw InvalidGuestIdException(raw_id);
    return guest;

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