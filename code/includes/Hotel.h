#ifndef HOTEL_H
#define HOTEL_H

#include "Booking.h"
#include<iostream>
#include <algorithm>
#include <vector>


class Hotel {
    std::vector<Booking> bookings;
    std::vector<Room> rooms;
public:
    // Constructors
    Hotel() = default;
    Hotel(const Hotel& other) = default;
    Hotel& operator=(const Hotel& other) = default;
    ~Hotel() = default;

    // Bookings
    void addBooking(const Booking& booking);
    bool cancelBooking(int roomNumber);

    [[nodiscard]] const std::vector<Booking>& getAllBookings() const;
    void displayBookingsForRoom(int roomNumber) const;
    void displayAllBookings() const;

	bool isRoomAvailable(int roomNumber, const std::string& date, int nights) const;
    [[nodiscard]] std::pair<std::string, std::string> findNextAvailablePeriod(int roomNumber, const std::string& checkIn, int nights) const;

    // Guests
    std::shared_ptr<Guest> findGuestById(const std::string& guestId) const;
    std::vector<Booking> getBookingsForGuest(const std::string& guestId) const;

    // Rooms
    const std::vector<Room>& getAllRooms() const;
    Room* findRoomByNumber(int roomNumber);
    Room* findAvailableRoomByType(const std::string& type, const std::string& checkIn, int nights);

    // CSV
    void saveBookingsToCSV(const std::string& filename) const;
    void loadBookingsFromCSV(const std::string& filename);
    void loadRoomsFromCSV(const std::string& filename);
};

#endif //HOTEL_H
