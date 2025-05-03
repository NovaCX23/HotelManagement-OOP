#include "../includes/Booking.h"
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>


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
    return price;
}
std::string Booking::calculateCheckout(const std::string& checkIn, int nights) {
    std::tm date = {};
    std::istringstream ss(checkIn);
    ss >> std::get_time(&date, "%Y-%m-%d");

    if (ss.fail()) {
        throw std::runtime_error("Invalid date format in calculateCheckout");
    }
    date.tm_mday += nights;
    std::mktime(&date);

    std::ostringstream out;
    out << std::put_time(&date, "%Y-%m-%d");
    return out.str();
}

std::string Booking::getCheckout() const {
    return Booking::calculateCheckout(this->checkIn, this->nights);
}

// CSV
std::string Booking::toCSV() const {
    std::ostringstream oss;
    oss << room.getNumber() << ","
        << room.getType() << ","
        << room.getPrice() << ","
        << guest.getName() << ","
        << guest.getId() << ","
        << checkIn << ","
        << nights;
    return oss.str();
}

Booking Booking::fromCSV(const std::string& csvLine) {
    std::istringstream iss(csvLine);
    std::string token;

    int roomNumber = 0;
    std::string roomType = "standard";
    double roomPrice = 100.0;
    std::string guestName = "Unknown";
    std::string guestId = "XXX000";
    std::string checkIn = "2025-01-01";
    int nights = 1;

    try {
        if (std::getline(iss, token, ',')) roomNumber = std::stoi(token);
        if (std::getline(iss, token, ',')) roomType = token;
        if (std::getline(iss, token, ',')) roomPrice = std::stod(token);
        if (std::getline(iss, token, ',')) guestName = token;
        if (std::getline(iss, token, ',')) guestId = token;
        if (std::getline(iss, token, ',')) checkIn = token;
        if (std::getline(iss, token, ',')) nights = std::stoi(token);
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing booking CSV: " << e.what() << "\n";
    }

    Room room(roomNumber, roomType, roomPrice);
    Guest guest(guestName, guestId);
    return Booking(room, guest, checkIn, nights);
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


