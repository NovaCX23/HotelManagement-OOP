#include "../includes/Hotel.h"
#include<iostream>

void Hotel::addBooking(const Booking &booking) {
    bookings.push_back(booking);
    std::cout << "Booking added for room " << booking.getRoom().getNumber() << "\n";
}

bool Hotel::cancelBooking(int roomNumber) {
    for (auto i = bookings.begin(); i != bookings.end(); ++i) {
        if (i->getRoom().getNumber() == roomNumber) {
            bookings.erase(i);
            std::cout << "Booking removed for room " << roomNumber << ".\n";
            return true;
        }
    }
    std::cout << "No booking found for room " << roomNumber << ".\n";
    return false;
}

bool Hotel::isRoomAvailable(int roomNumber, const std::string& date) const {
    for (auto i = bookings.begin(); i != bookings.end(); ++i) {
        const Booking& booking = *i;
        if (booking.getRoom().getNumber() == roomNumber && booking.isActive(date))
            return false;
    }
    return true; // Available
}

void Hotel::displayAllBookings() const {
    if (bookings.empty()) {
        std::cout << "No bookings in the system.\n";
        return;
    }
    //std::cout << "--- All Bookings ---\n";
    for (const Booking& booking : bookings) {
        std::cout << booking << "\n---\n";
    }
}