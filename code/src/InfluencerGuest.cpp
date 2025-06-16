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

