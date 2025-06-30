#ifndef REPORT_H
#define REPORT_H

#include "Booking.h"
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

#endif // REPORT_H
