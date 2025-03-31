#ifndef BOOKING_H
#define BOOKING_H

#include "Room.h"
#include "Guest.h"
#include <string>

class Booking {
    Room room;
    Guest guest;
    std::string checkIn;
    int nights;
public:
    // Constructors
    Booking(const Room& room, const Guest& guest, const std::string& checkIn, int nights);
    Booking(const Booking& other); // copy constructor

    // Getters
    [[nodiscard]] const Room& getRoom() const { return room; }
    [[nodiscard]] const Guest& getGuest() const { return guest; }
    [[nodiscard]] const std::string& getCheckIn() const { return checkIn; }
    [[nodiscard]] int getNights() const { return nights; }

    // Public Functions
    [[nodiscard]] double getTotalPrice() const;
    [[nodiscard]] bool isActive(const std::string& currentDate) const;

    // Operators
    Booking& operator=(const Booking& other);
    friend std::ostream& operator<<(std::ostream& os, const Booking& booking);

    // Destructors
    ~Booking();
};



#endif //BOOKING_H
