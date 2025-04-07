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
    [[nodiscard]] const Room& getRoom() const;
    [[nodiscard]] const Guest& getGuest() const;
    [[nodiscard]] const std::string& getCheckIn() const;
    [[nodiscard]] int getNights() const;

    // Public Functions
    [[nodiscard]] double getTotalPrice() const;
    [[nodiscard]] std::string getCheckout() const;
    [[nodiscard]] bool isActive(const std::string& currentDate) const;

    // Operators
    Booking& operator=(const Booking& other);
    friend std::ostream& operator<<(std::ostream& os, const Booking& booking);

    // Destructors
    ~Booking();
};



#endif //BOOKING_H
