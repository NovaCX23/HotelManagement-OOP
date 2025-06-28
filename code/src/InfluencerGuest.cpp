#include "../includes/InfluencerGuest.h"
#include <sstream>

std::string InfluencerGuest::getType() const {
	return "Influencer";
}

double InfluencerGuest::guestDiscount(int nights) const {
		double discount = 0.0;
		if (followerCount >= 100000)
			discount = 0.25;
		else if (followerCount >= 50000)
			discount = 0.20;
		else
			discount = 0.15;

		// extra bonus dacă stă mai mult
		if (nights >= 5)
			discount += 0.05;

		return discount;

}

std::map<std::string, double> InfluencerGuest::getAvailableBenefits() const {
	auto benefits = Guest::getAvailableBenefits();
	for (auto& [benefitName, price] : benefits) {
		if (benefitName != "Conference room") {
			price = 0.0;
		}
	}
	return benefits;
}

std::vector<std::string> InfluencerGuest::excludedBenefits() const {
	return {"Conference room"};
}

double InfluencerGuest::estimatedProfit() const {
	return followerCount * profitPerFollower;
}


bool InfluencerGuest::isValidId() const {
	return id.substr(0, 3) == "INF" && Guest::isValidId();
}

std::shared_ptr<Guest> InfluencerGuest::clone() const {
	return std::make_shared<InfluencerGuest>(*this);
}

std::string InfluencerGuest::getFullId() const {
	return id + "|" + std::to_string(followerCount);
}
std::string InfluencerGuest::getSummary() const {
	std::ostringstream os;
	os << "Influencer Guest - " << name << " (" << id << ")\n";
	os << "Followers: " << followerCount << "\n";
	os << "Estimated indirect profit: $" << estimatedProfit();
	return os.str();
}


// Parsing
std::shared_ptr<Guest> InfluencerGuest::createFromInput(const std::string& name, const std::string& id) {
	int followers;
	std::cout << "Enter number of followers: ";
	std::cin >> followers;

	auto guest = std::make_shared<InfluencerGuest>(name, id, followers);
	if (!guest->isValidId()) {
		throw InvalidGuestIdException(id);
	}
	return guest;
}

std::shared_ptr<Guest> InfluencerGuest::createFromCSV(const std::string& name, const std::string& fullId) {
	auto parts = split(fullId, '|');
	std::string raw_id = parts[0];
	int followers = (parts.size() >= 2) ? std::stoi(parts[1]) : 0;

	auto guest = std::make_shared<InfluencerGuest>(name, raw_id, followers);
	if (!guest->isValidId()) {
		throw InvalidGuestIdException(raw_id);
	}
	return guest;
}