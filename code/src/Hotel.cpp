#include "../includes/Hotel.h"

bool compareByCheckIn(const Booking& first, const Booking& second) {
    return first.getCheckIn() < second.getCheckIn();
}

void Hotel::addBooking(const Booking& booking) {
    bookings.push_back(booking);
    std::cout << "Booking added for room " << booking.getRoom().getNumber() << "\n";
}

bool Hotel::cancelBooking(int roomNumber) {
    std::cout << "Do you want to see all bookings for room " << roomNumber << "? (y/n): ";
    char seeDetails;
    std::cin >> seeDetails;
    if (seeDetails == 'y' || seeDetails == 'Y') {
        displayBookingsForRoom(roomNumber);
    }
    std::string targetDate;
    std::cout << "Enter the check-in date of the booking to cancel (YYYY-MM-DD): ";
    std::cin >> targetDate;

    for (auto i = bookings.begin(); i != bookings.end(); ++i) {
        if (i->getRoom().getNumber() == roomNumber && i->getCheckIn() == targetDate) {
            std::cout << "Booking found:\n";
            std::cout << "Are you sure you want to cancel it? (y/n)";

            char confirm;
            std::cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                bookings.erase(i);
                std::cout << "Booking successfully cancelled.\n";
                return true;
            }
            else {
                std::cout << "Cancellation aborted.\n";
                return false;
            }
        }
    }

    std::cout << "No bookings with that check-in date found for room " << roomNumber << ".\n";
    return false;
}

bool Hotel::isRoomAvailable(int roomNumber, const std::string& date) const {
    for (const auto & booking : bookings) {
        if (booking.getRoom().getNumber() == roomNumber && booking.isActive(date))
            return false;
    }
    return true; // Available
}

void Hotel::displayBookingsForRoom(int roomNumber) const {
    bool found = false;
    int index = 1;
    std::cout << "--- Bookings for room: " << roomNumber << " ---\n";
    for (const Booking& b : bookings)
        if (b.getRoom().getNumber() == roomNumber) {
            std::cout << "#" << index++ << ": "
                      << "Check-in: "   << b.getCheckIn()
                      << ", Checkout: " << b.getCheckout()
                      << ", Guest: "    << b.getGuest().getName()
                      << ", Category: " << b.getRoom().getType()
                      << ", Price: "    << b.getTotalPrice() << "\n";
            found = true;
        }
    if (!found) {
        std::cout << "No bookings found for room " << roomNumber << ".\n";
    }
}


void Hotel::displayAllBookings() const {
    if (bookings.empty()) {
        std::cout << "No bookings in the system.\n";
        return;
    }

    char choice;
    std::cout << "Do you want to display bookings by room (r) or all bookings together (a)? ";
    std::cin >> choice;

    std::vector<Booking> sortedBookings = bookings;
    std::sort(sortedBookings.begin(), sortedBookings.end(), compareByCheckIn);

    if (choice == 'r' || choice == 'R') {
        std::cout << "------- Bookings by Room -------\n";
        std::set<int> uniqueRooms;
        for (const Booking& b : sortedBookings) {
            uniqueRooms.insert(b.getRoom().getNumber());
        }

        for (auto roomNumber : uniqueRooms) {
            displayBookingsForRoom(roomNumber);
            std::cout << "-----------------------------\n";
        }
    }
    else if (choice == 'a' || choice == 'A') {
        std::cout << "------- All Bookings  -------\n";
        int index = 1;
        for (const Booking& b : sortedBookings) {
            std::cout << "#" << index++ << ": "
                      << "Check-in: "   << b.getCheckIn()
                      << ", Checkout: " << b.getCheckout()
                      << ", Room: "     << b.getRoom().getNumber()
                      << ", Guest: "    << b.getGuest().getName()
                      << ", Category: " << b.getRoom().getType()
                      << ", Price: "    << b.getTotalPrice() << "\n";
        }
    }
    else {
        std::cout << "Invalid choice, please try again.\n";
    }

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

    // Verif daca perioada ceruta este disponibila inainte de prima rez
    if (!roomBookings.empty()) {
        const Booking& first = roomBookings.front();
        Booking temp(room, guest, checkIn, nights);
        if (temp.getCheckout() <= first.getCheckIn()) {
            return {checkIn, temp.getCheckout()};
        }
    }

    // Cautam un interval disponibil intre rezervari
    size_t n = roomBookings.size();
    for (size_t i = 0; i < n - 1; ++i) {
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