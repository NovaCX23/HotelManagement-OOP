#ifndef HOTEL_H
#define HOTEL_H

#include "Booking.h"
#include <vector>

class Hotel {
    std::vector<Booking> bookings;
public:
    void addBooking(const Booking& booking);
    bool cancelBooking(int roomNumber);
    [[nodiscard]] bool isRoomAvailable(int roomNumber, const std::string& date) const;
    void displayAllBookings() const;
    [[nodiscard]] std::pair<std::string, std::string> findNextAvailablePeriod(int roomNumber, const std::string& checkIn, int nights) const;

};

#endif //HOTEL_H
