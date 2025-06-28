#include "../includes/VIPGuest.h"
#include <sstream>

VIPGuest::VIPGuest(const std::string& name, const std::string& id, const std::string& tier)
    : Guest(name, id), tier(tier) {
    if (tier != "Bronze" && tier != "Silver" && tier != "Gold") {
        throw std::invalid_argument("Invalid VIP tier: " + tier);
    }
}

double VIPGuest::guestDiscount(int nights) const {
    double discount = 0.0;
    if (tier == "Gold") discount = 0.3;
    else if (tier == "Silver") discount = 0.2;
    else if (tier == "Bronze") discount = 0.1;

    if (nights > 5) discount += 0.05; // Bonus extra
    return discount;
}

std::string VIPGuest::getType() const {
    return "VIP (" + tier + ")";
}

std::map<std::string, double> VIPGuest::getAvailableBenefits() const {
    auto benefits = Guest::getAvailableBenefits();
    for (auto& [benefitName, price] : benefits) {
        price = 0.0; // all free for vip
    }
    return benefits;
}

bool VIPGuest::isValidId() const {
    return id.substr(0, 3) == "VIP" && Guest::isValidId();
}
std::string VIPGuest::getFullId() const {
    return id + "|" + tier;
}

std::shared_ptr<Guest> VIPGuest::clone() const {
    return std::make_shared<VIPGuest>(*this);
}
std::string VIPGuest::getSummary() const {
    std::ostringstream oss;
    oss << "VIP Guest - Tier: " << tier
        << ". Enjoys full access to all benefits.";
    return oss.str();
}

//Parsing
std::shared_ptr<Guest> VIPGuest::createFromInput(const std::string& name, const std::string& id) {
    std::string tier;
    std::cout << "Enter VIP tier (Bronze/Silver/Gold): ";
    std::cin >> tier;
    auto guest = std::make_shared<VIPGuest>(name, id, tier);
    if (!guest->isValidId()) {
        throw InvalidGuestIdException(id);
    }
    return guest;
}

std::shared_ptr<Guest> VIPGuest::createFromCSV(const std::string& name, const std::string& fullId) {
    auto parts = GuestFactory::split(fullId, '|');
    std::string raw_id = parts[0];
    std::string tier = (parts.size() >= 2) ? parts[1] : "Bronze";
    auto guest = std::make_shared<VIPGuest>(name, raw_id, tier);
    if (!guest->isValidId()) {
        throw InvalidGuestIdException(raw_id);
    }
    return guest;
}

