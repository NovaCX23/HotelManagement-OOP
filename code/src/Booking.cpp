#include "../includes/Booking.h"
#include "../includes/Exceptions.h"
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include<algorithm>


int Booking::totalBookings = 0;
// Constructors
Booking::Booking(const Room& room, std::shared_ptr<Guest> guest, const std::string& checkIn, int nights)
    : room(room), guest(std::move(guest)), checkIn(checkIn), nights(nights) {
    //std::cout << "Booking created for " << guest.getName() << " successfully " << "\n";
    totalBookings++;
}

Booking::Booking(const Booking& other)
    : room(other.room), guest(other.guest), checkIn(other.checkIn), nights(other.nights) {
    //std::cout << "Booking copied\n";
}

// Getters
std::shared_ptr<Guest> Booking::getGuest() const { return guest; }
const std::string& Booking::getCheckIn() const { return checkIn; }
const Room& Booking::getRoom() const { return room; }
int Booking::getNights() const { return nights; }



// Functions
double Booking::getTotalPrice() const {
    double basePrice = room.getPrice() * nights;
    double discount = guest->guestDiscount(nights);
    return basePrice * (1.0 - discount);
}

std::string Booking::calculateCheckout(const std::string& checkIn, int nights) {
    std::tm date = {};
    std::istringstream ss(checkIn);
    ss >> std::get_time(&date, "%Y-%m-%d");

    if (ss.fail())
        throw InvalidDateFormatException(checkIn);

    date.tm_mday += nights;
    std::mktime(&date);

    std::ostringstream out;
    out << std::put_time(&date, "%Y-%m-%d");
    return out.str();
}

std::string Booking::getCheckout() const {
    return calculateCheckout(this->checkIn, this->nights);
}

// CSV
std::string Booking::toCSV() const {
    std::ostringstream oss;
    oss << room.getNumber() << ","
        << room.getType() << ","
        << guest->getName() << ","
        << guest->getFullId() << ","
        << checkIn << ","
        << nights;
    return oss.str();
}


Booking Booking::fromCSV(const std::string& csvLine, const std::vector<Room>& rooms) {
    std::istringstream iss(csvLine);

    int roomNumber = 0;
    std::string roomType;
    std::string guestName = "Unknown";
    std::string guestId = "XXX000";
    std::string checkIn = "2025-01-01";
    int nights = 1;

    try {
        std::string token;
        std::getline(iss, token, ','); roomNumber = std::stoi(token);
        std::getline(iss, roomType, ',');
        std::getline(iss, guestName, ',');
        std::getline(iss, guestId, ',');
        std::getline(iss, checkIn, ',');
        std::getline(iss, token, ','); nights = std::stoi(token);
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing booking CSV: " << e.what() << "\n";
    }


    auto it = std::find_if(rooms.begin(), rooms.end(), [roomNumber](const Room& r) {
        return r.getNumber() == roomNumber;
    });

    if (it == rooms.end()) {
        throw std::runtime_error("Room not found for room number: " + std::to_string(roomNumber));
    }

    Room roomFinal = *it;
    auto guest = Guest::createFromCSV(guestName, guestId);

    ++totalBookings; // sincronizam corect numărul de bookinguri
    return Booking(roomFinal, guest, checkIn, nights);
}




// Operators
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
       << ", Guest: " << booking.guest->getName()
       << ", ID: " << booking.guest->getId()
       << ", Category: " << booking.room.getType()
       << ", Check-in: " << booking.checkIn
       << ", Checkout: " << booking.getCheckout()
       << ", Total Price: $" << booking.getTotalPrice()
       << "]";
    return os;
}

// Destructor
Booking::~Booking() = default;
