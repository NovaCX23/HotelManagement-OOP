#ifndef BOOKING_H
#define BOOKING_H

#include "Room.h"
#include "Guest.h"
#include <string>
#include <memory>

class Booking {
    static int totalBookings;
    Room room;
    std::shared_ptr<Guest> guest;
    std::string checkIn;
    int nights;
public:
    // Constructors
    Booking(const Room& room, std::shared_ptr<Guest> guest, const std::string& checkIn, int nights);
    Booking(const Booking& other); // copy constructor

    // Getters
    [[nodiscard]] const Room& getRoom() const;
    [[nodiscard]] std::shared_ptr<Guest> getGuest() const;
    [[nodiscard]] const std::string& getCheckIn() const;
    [[nodiscard]] int getNights() const;
    static int getTotalBookings() { return totalBookings; }

    // Public Functions
    [[nodiscard]] double getTotalPrice() const;
    [[nodiscard]] std::string getCheckout() const;
    static std::string calculateCheckout(const std::string& checkIn, int nights);

    // CSV
    std::string toCSV() const;
    static Booking fromCSV(const std::string& csvLine, const std::vector<Room>& rooms);

    // Operators
    Booking& operator=(const Booking& other);
    friend std::ostream& operator<<(std::ostream& os, const Booking& booking);

    // Destructor
    ~Booking();
};


#endif //BOOKING_H
