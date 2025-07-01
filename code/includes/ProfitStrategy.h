#ifndef PROFITSTRATEGY_H
#define PROFITSTRATEGY_H

#include "Booking.h"
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

		// Pierderi din beneficii incluse
		auto guest = booking.getGuest();
		double loss = 0.0;

		auto free = guest->getFreeBenefits();
		auto all = guest->getAvailableBenefits();

		for (const auto& benefit : free) {
			if (all.contains(benefit)) {
				loss += all[benefit];
			}
		}

		return total - loss;
	}

};

#endif // PROFITSTRATEGY_H
