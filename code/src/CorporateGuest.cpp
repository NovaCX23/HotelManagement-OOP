#include "../includes/CorporateGuest.h"
#include <vector>
#include <sstream>

CorporateGuest::CorporateGuest(const std::string& name, const std::string& id,const std::string& companyName, int nrEmployees)
    : Guest(name, id), companyName(companyName), nrEmployees(nrEmployees) {}

std::string CorporateGuest::getType() const {
    return "Corporate";
}

double CorporateGuest::guestDiscount(int nights) const {
    double discount = 0.0;
    if (nrEmployees >= 30) discount = 0.25;
    else if (nrEmployees >= 20) discount = 0.15;
    else if (nrEmployees >= 10) discount = 0.10;

    if (nights >= 7) discount += 0.05; // extra discount
    return discount;
}

std::vector<std::string> CorporateGuest::excludedBenefits() const {
    return {
        "Welcome gift",
        "Minibar included",
        "Private dining",
        "Room upgrade",
        "Free cancellation"
    };
}

std::map<std::string, double> CorporateGuest::getAvailableBenefits() const {
    auto all = Guest::getAvailableBenefits();
    for (const auto& benefit : excludedBenefits()) {
        all.erase(benefit);
    }
    all["Conference room"] = 0.0;
    return all;
}

bool CorporateGuest::isEligibleForBenefit(const std::string& benefitName) const {
    for (const auto& b : excludedBenefits()) {
        if (b == benefitName)
            return false;
    }
    return Guest::isEligibleForBenefit(benefitName);
}

bool CorporateGuest::isValidId() const {
    return id.substr(0, 3) == "COR" && Guest::isValidId();
}

std::string CorporateGuest::getSummary() const {
    const int persoanePerCamera = 2; 
    int nrCamere = (nrEmployees + persoanePerCamera - 1) / persoanePerCamera;

    std::ostringstream oss;
    oss << "Bookings made for company: " << companyName
        << " — " << nrEmployees << " employee" << (nrEmployees != 1 ? "s" : "")
        << " accommodated in " << nrCamere
        << " room" << (nrCamere != 1 ? "s" : "") << ".";
    return oss.str();
}
