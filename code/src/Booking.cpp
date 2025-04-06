#include "../includes/Booking.h"
#include <string>

// Constructor
Booking::Booking(const Room& room, const Guest& guest, const std::string& checkIn, int nights)
    : room(room), guest(guest), checkIn(checkIn), nights(nights) {
    std::cout << "Booking created for " << guest.getName() << " successfully " << "\n";
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

bool Booking::isActive(const std::string& currentDate) const {
    // format "YYYY-MM-DD"
    if (currentDate == checkIn) return true;

    // extragem datele din string
    int year = std::stoi(checkIn.substr(0,4));
    int month = std::stoi(checkIn.substr(5, 2));
    int day = std::stoi(checkIn.substr(8, 2));

    // calc nr de zile(check-in+nights)
    int totalDays = day + nights;

    while (true) {
        // Calculează numărul de zile din luna curentă
        int daysInMonth;
        if (month == 2) {
            // Verificare an bisect
            bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            daysInMonth = isLeapYear ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        } else {
            daysInMonth = 31;
        }
        // Dacă totalDays se încadrează în luna curentă, ieșim din buclă
        if (totalDays <= daysInMonth) {
            day = totalDays;
            break;
        }
        // Altfel, trecem la luna următoare
        totalDays -= daysInMonth;
        month++;

        // Dacă am depășit decembrie, trecem la anul următor
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    std::string checkOutDate =
    std::to_string(year) + "-" +
    (month < 10 ? "0" : "") + std::to_string(month) + "-" +
    (day < 10 ? "0" : "") + std::to_string(day);

    return (currentDate > checkIn) && (currentDate < checkOutDate);
}

// Operator
Booking& Booking::operator=(const Booking& other) {
    if (this != &other) {  // Verifică auto-atribuire
        // Folosind getter-ele
        room = other.getRoom();
        guest = other.getGuest();
        checkIn = other.getCheckIn();
        nights = other.getNights();
    }
    return *this;  // Returnează obiectul curent
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
Booking::~Booking() = default;


