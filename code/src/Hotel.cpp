#include "../includes/Hotel.h"
#include<iostream>

void Hotel::addBooking(const Booking &booking) {
    bookings.push_back(booking);
    std::cout << "Booking added for room " << booking.getRoom().getNumber() << "\n";
}

bool Hotel::cancelBooking(int roomNumber) {
    for (auto i = bookings.begin(); i != bookings.end(); ++i) {
        if (i->getRoom().getNumber() == roomNumber) {
            bookings.erase(i);
            std::cout << "Booking removed for room " << roomNumber << ".\n";
            return true;
        }
    }
    std::cout << "No booking found for room " << roomNumber << ".\n";
    return false;
}

bool Hotel::isRoomAvailable(int roomNumber, const std::string& date) const {
    for (auto i = bookings.begin(); i != bookings.end(); ++i) {
        const Booking& booking = *i;
        if (booking.getRoom().getNumber() == roomNumber && booking.isActive(date))
            return false;
    }
    return true; // Available
}

void Hotel::displayAllBookings() const {
    if (bookings.empty()) {
        std::cout << "No bookings in the system.\n";
        return;
    }
    //std::cout << "--- All Bookings ---\n";
    for (const Booking& booking : bookings) {
        std::cout << booking << "\n---\n";
    }
}

bool compareByCheckIn(const Booking& first, const Booking& second) {
    return first.getCheckIn() < second.getCheckIn();
}

std::pair<std::string, std::string> Hotel::findNextAvailablePeriod(int roomNumber, const std::string& checkIn, int nights) const {
    // Cream un obiect Booking temporar
    Room room(roomNumber, "type", 0);
    Guest guest("Dummy", "DUM111");
    Booking newBooking(room, guest, checkIn, nights);

    std::string newCheckOut = newBooking.getCheckout();

    // Filtram doar rezervarile pentru camera respectiva
    std::vector<Booking> roomBookings;
    for (const Booking& b : bookings) {
        if (b.getRoom().getNumber() == roomNumber) {
            roomBookings.push_back(b);
        }
    }

    std::sort(roomBookings.begin(), roomBookings.end(), compareByCheckIn);

    // Cautam un interval disponibil intre rezervari
    int n = roomBookings.size();
    for (auto i = 0; i < n - 1; ++i) {
        const Booking& current = roomBookings[i];
        const Booking& next = roomBookings[i + 1];

        std::string currentCheckout = current.getCheckout();
        std::string nextCheckIn = next.getCheckIn();

        // Dacă e loc pentru perioada dorită între currentCheckout și nextCheckIn
        Room room1(roomNumber, "type", 0);
        Guest guest1("Dummy2", "DUM222");
        Booking temp(room1, guest1, currentCheckout, nights);
        std::string candidateCheckout = temp.getCheckout();

        if (candidateCheckout <= nextCheckIn) {
            return{currentCheckout, candidateCheckout};
        }
    }

    // Dacă nu s-a găsit interval între rezervări, returnăm perioada imediat după ultima rezervare
    if (!roomBookings.empty()) {
        const Booking& last = roomBookings.back();
        std::string lastCheckout = last.getCheckout();

        Room room1(roomNumber, "type", 0);
        Guest guest1("Dummy2", "DUM222");
        Booking temp(room1, guest1, lastCheckout, nights);

        return {lastCheckout, temp.getCheckout()};
    }

    // Daca nu exista nicio rezervare
    return {checkIn, newCheckOut};
}