#include "../includes/VIPGuest.h"
VIPGuest::VIPGuest(const std::string& name, const std::string& id, const std::string& tier)
    : Guest(name, id), tier(tier) {
    if (tier != "Bronze" && tier != "Silver" && tier != "Gold") {
        throw std::invalid_argument("Invalid VIP tier: " + tier);
    }
}

double VIPGuest::guestDiscount(int nights) const {
    if (tier == "Bronze") return 0.10;
    if (tier == "Silver") return 0.20;
    if (tier == "Gold")   return 0.30;
    return 0.0;
}

std::string VIPGuest::getType() const {
    return "VIP (" + tier + ")";
}

std::map<std::string, double> VIPGuest::getAvailableBenefits() const {
    auto benefits = Guest::getAvailableBenefits();
    for (auto& [name, price] : benefits) {
        price = 0.0; // all free for vip
    }
    return benefits;
}

bool VIPGuest::isValidId() const {
    return id.substr(0, 3) == "VIP" && Guest::isValidId();
}