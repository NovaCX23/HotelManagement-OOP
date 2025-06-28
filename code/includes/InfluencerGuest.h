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
	std::string getSummary() const override;

	double estimatedProfit() const;

	std::shared_ptr<Guest> clone() const override;
	bool isValidId() const override;


	//parsing
	static std::shared_ptr<Guest> createFromInput(const std::string& name, const std::string& id);
	static std::shared_ptr<Guest> createFromCSV(const std::string& name, const std::string& fullId);

};

#endif
