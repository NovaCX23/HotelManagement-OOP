#include "../includes/Booking.h"

// Constructor
Booking::Booking(const Room& room, const Guest& guest, const std::string& checkIn, int nights)
    : room(room), guest(guest), checkIn(checkIn), nights(nights) {
    std::cout << "Booking created for " << guest.getName() << "\n";
}

Booking::Booking(const Booking& other)
    : room(other.room), guest(other.guest), checkIn(other.checkIn), nights(other.nights) {
    std::cout << "Booking copied\n";
}

// Public functions
double Booking::getTotalPrice() const {
    return room.getPrice() * nights;
}

bool Booking::isActive(const std::string& currentDate) const {
    // format "YYYY-MM-DD"
    return currentDate >= checkIn;
}

// Operator
Booking& Booking::operator=(const Booking& other) {
    if (this != &other) {  // Verifică auto-atribuire
        room = other.room;
        guest = other.guest;
        checkIn = other.checkIn;
        nights = other.nights;
    }
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Booking& booking) {
    os << "Booking:\n"
       << "  Guest: " << booking.guest << "\n"
       << "  Room: " << booking.room << "\n"
       << "  Check-in: " << booking.checkIn << " for " << booking.nights << " nights\n"
       << "  Total: $" << booking.getTotalPrice();
    return os;
}

// Destructor
Booking::~Booking() {
    std::cout << "Booking for " << guest.getName() << " cancelled\n";
}


