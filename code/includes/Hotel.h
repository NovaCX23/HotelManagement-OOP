#ifndef HOTEL_H
#define HOTEL_H

#include "Booking.h"
#include<iostream>
#include <algorithm>
#include <vector>


class Hotel {
    std::vector<Booking> bookings;
public:
    void addBooking(const Booking& booking);
    bool cancelBooking(int roomNumber);
    [[nodiscard]] bool isRoomAvailable(int roomNumber, const std::string& date, int nights) const;
    void displayBookingsForRoom(int roomNumber) const;
    void displayAllBookings() const;
    [[nodiscard]] const std::vector<Booking>& getAllBookings() const;
    [[nodiscard]] std::pair<std::string, std::string> findNextAvailablePeriod(int roomNumber, const std::string& checkIn, int nights) const;

    // CSV
    void saveBookingsToCSV(const std::string& filename) const;
    void loadBookingsFromCSV(const std::string& filename);
};

#endif //HOTEL_H
