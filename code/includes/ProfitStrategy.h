#ifndef PROFITSTRATEGY_H
#define PROFITSTRATEGY_H

#include "Booking.h"
#include <memory>

class ProfitStrategy {
public:
	virtual double computeProfit(const Booking& booking) const = 0;
	virtual ~ProfitStrategy() = default;
};

// Strategie simplă: cat platește clientul (deja cu discount)
class SimpleProfitStrategy : public ProfitStrategy {
public:
	double computeProfit(const Booking& booking) const override {
		return booking.getTotalPrice();
	}
};

#endif // PROFITSTRATEGY_H
