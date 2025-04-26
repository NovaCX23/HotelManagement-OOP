#include "../includes/Booking.h"
#include <string>

// Constructor
Booking::Booking(const Room& room, const Guest& guest, const std::string& checkIn, int nights)
    : room(room), guest(guest), checkIn(checkIn), nights(nights) {
    //std::cout << "Booking created for " << guest.getName() << " successfully " << "\n";
}

Booking::Booking(const Booking& other)
    : room(other.room), guest(other.guest), checkIn(other.checkIn), nights(other.nights) {
    //std::cout << "Booking copied\n";
}

// Getters
const Guest& Booking::getGuest() const {
    return guest;
}

const std::string& Booking::getCheckIn() const {
    return checkIn;
}

int Booking::getNights() const {
    return nights;
}
const Room& Booking::getRoom() const {
    return room;
}

// Public functions
double Booking::getTotalPrice() const {
    double price =  room.getPrice() * nights;
    if (room.getType() == "VIP") {
        price *= 0.9; // Aplică reducere de 10% pentru camere VIP
    }
    return price;
}
// Static
std::string Booking::calculateCheckout(const std::string& checkIn, int nights) {
    int year = std::stoi(checkIn.substr(0,4));
    int month = std::stoi(checkIn.substr(5, 2));
    int day = std::stoi(checkIn.substr(8, 2));

    int totalDays = day + nights;
    while (true) {
        int daysInMonth;
        if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            daysInMonth = isLeapYear ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        } else {
            daysInMonth = 31;
        }
        if (totalDays <= daysInMonth) {
            day = totalDays;
            break;
        }
        totalDays -= daysInMonth;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    std::string checkOutDate =
        std::to_string(year) + "-" +
        (month < 10 ? "0" : "") + std::to_string(month) + "-" +
        (day < 10 ? "0" : "") + std::to_string(day);

    return checkOutDate;
}

std::string Booking::getCheckout() const {
    return Booking::calculateCheckout(this->checkIn, this->nights);
}

// Operator
Booking& Booking::operator=(const Booking& other) {
    if (this != &other) {
        room = other.getRoom();
        guest = other.getGuest();
        checkIn = other.getCheckIn();
        nights = other.getNights();
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Booking& booking) {
    os << "[Room " << booking.room.getNumber()
       << ", Guest: " << booking.guest.getName()
       << ", Category: " << booking.room.getType()
       << ", Check-in: " << booking.checkIn
       << ", Checkout: " << booking.getCheckout()
       << ", Total Price: $" << booking.getTotalPrice()
       << "]";
    return os;
}

// Destructor
Booking::~Booking() = default;


