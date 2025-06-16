#ifndef INFLUENCERGUEST_H
#define INFLUENCERGUEST_H

#include "Guest.h"
#include<sstream>

class InfluencerGuest : public Guest {
private:
	int followerCount;
	static constexpr double profitPerFollower = 0.05;
public:
	InfluencerGuest(const std::string& name, const std::string& id, int followers)
	:Guest(name, id), followerCount(followers){}

	std::string getType() const override;
	double guestDiscount(int nights) const override;
	std::map<std::string, double> getAvailableBenefits() const override;
	std::vector<std::string> excludedBenefits() const override;
	std::string getFullId() const override;

	std::string getSummary() const {
		std::ostringstream os;
		os << "Influencer Guest - " << name << " (" << id << ")\n";
		os << "Followers: " << followerCount << "\n";
		os << "Estimated indirect profit: $" << estimatedProfit();
		return os.str();
	}
	double estimatedProfit() const;
	int getFollowerCount() const;

	std::shared_ptr<Guest> clone() const override;
	bool isValidId() const override;
};

#endif
