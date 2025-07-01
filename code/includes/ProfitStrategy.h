#ifndef PROFITSTRATEGY_H
#define PROFITSTRATEGY_H

#include "Booking.h"
#include "CorporateGuest.h"
#include <memory>

class ProfitStrategy {
public:
	virtual double computeProfit(const Booking& booking) const = 0;
	virtual ~ProfitStrategy() = default;
};

class RealisticProfitStrategy : public ProfitStrategy {
public:
	double computeProfit(const Booking& booking) const override {
		double total = booking.getBookingPrice();

		auto guest = booking.getGuest();
		auto guestBenefits = guest->getAvailableBenefits();

		// Preturile standard
		auto standardPrices = Guest::getStandardBenefitPrices();

		double loss = 0.0;
		for (const auto& [benefitName, standardPrice] : standardPrices) {
			auto it = guestBenefits.find(benefitName);
			if (it != guestBenefits.end() && it->second == 0.0) {
				loss += standardPrice;  // beneficiu oferit gratuit → pierdere
			}
		}
		return total - loss;
	}

};

#endif // PROFITSTRATEGY_H
