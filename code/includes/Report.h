#ifndef REPORT_H
#define REPORT_H

#include "Booking.h"
#include "ProfitStrategy.h"
#include <memory>
#include <iostream>

template<typename T>
class Report {
public:
	void generate(const std::vector<Booking>& bookings) const {
		int count = 0;
		std::cout << "\n--- Report for selected guest type ---\n";

		for (const auto& booking : bookings) {
			auto guestPtr = std::dynamic_pointer_cast<T>(booking.getGuest());
			if (guestPtr) {
				// std::cout << booking << "\n";
				++count;
			}
		}

		std::cout << "Total guests of selected type: " << count << "\n";
	}
};

template <typename T>
double calculateProfitForType(const std::vector<Booking>& bookings, const ProfitStrategy& strategy) {
	double total = 0.0;
	for (const auto& b : bookings) {
		if (std::dynamic_pointer_cast<T>(b.getGuest())) {
			total += strategy.computeProfit(b);
		}
	}
	return total;
}

template <typename T>
double calculateLossForType(const std::vector<Booking>& bookings) {
	double totalLoss = 0.0;

	auto standardPrices = Guest::getStandardBenefitPrices();

	for (const auto& b : bookings) {
		auto guestPtr = std::dynamic_pointer_cast<T>(b.getGuest());
		if (guestPtr) {
			auto guestBenefits = guestPtr->getAvailableBenefits();
			for (const auto& [benefitName, standardPrice] : standardPrices) {
				auto it = guestBenefits.find(benefitName);
				if (it != guestBenefits.end() && it->second == 0.0) {
					totalLoss += standardPrice;
				}
			}
		}
	}
	return totalLoss;
}


#endif // REPORT_H
