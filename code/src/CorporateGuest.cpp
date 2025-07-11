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
    all["Conference room"] = 0.0;
    all["Lounge access"] = 0.0;
    for (const auto& benefit : excludedBenefits()) {
        all.erase(benefit);
    }
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
std::string CorporateGuest::getFullId() const {
    return id + "|" + companyName + "|" + std::to_string(nrEmployees);
}


std::string CorporateGuest::getSummary() const {
    const int persoanePerCamera = 2; 
    int nrCamere = (nrEmployees + persoanePerCamera - 1) / persoanePerCamera;

    std::ostringstream oss;
    oss << "Bookings made for company: " << companyName
        << " - " << nrEmployees << " employee" << (nrEmployees != 1 ? "s" : "")
        << " accommodated in " << nrCamere
        << " room" << (nrCamere != 1 ? "s" : "") << ".";
    return oss.str();
}

std::shared_ptr<Guest> CorporateGuest::clone() const {
    return std::make_shared<CorporateGuest>(*this);
}


// Parsing
std::shared_ptr<Guest> CorporateGuest::createFromInput(const std::string& name, const std::string& id) {
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
}

std::shared_ptr<Guest> CorporateGuest::createFromCSV(const std::string& name, const std::string& fullId) {
    auto parts = GuestFactory::split(fullId, '|');
    std::string raw_id = parts[0];
    std::string company = (parts.size() >= 2) ? parts[1] : "Unknown";
    int employees = (parts.size() >= 3) ? std::stoi(parts[2]) : 1;

    auto guest = std::make_shared<CorporateGuest>(name, raw_id, company, employees);
    if (!guest->isValidId()) {
        throw InvalidGuestIdException(raw_id);
    }
    return guest;
}
