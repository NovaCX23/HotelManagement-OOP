#include "../includes/Hotel.h"
#include "../includes/Exceptions.h"
#include <fstream>
#include <set>
#include <sstream>

bool compareByCheckIn(const Booking& first, const Booking& second) {
    return first.getCheckIn() < second.getCheckIn();
}

// Bookings

void Hotel::addBooking(const Booking& booking) {
    bookings.push_back(booking);
    std::cout << "Booking added for room " << booking.getRoom().getNumber() << "\n";
}

bool Hotel::cancelBooking(int roomNumber) {
    try {
        findRoomByNumber(roomNumber);
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
                std::cout << *i << "\n";
                std::cout << "Are you sure you want to cancel it? (y/n): ";

                char confirm;
                std::cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    bookings.erase(i);
                    std::cout << "Booking successfully cancelled.\n";
                    return true;
                } else {
                    std::cout << "Operation aborted.\n";
                    return false;
                }
            }
        }

        std::cout << "No bookings with that check-in date found for room " << roomNumber << ".\n";
        return false;
    }
    catch (const RoomNotFoundException& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}



const std::vector<Booking>& Hotel::getAllBookings() const {
    return bookings;
}

void Hotel::displayBookingsForRoom(int roomNumber) const {
    bool found = false;
    int index = 1;
    std::cout << "--- Bookings for room: " << roomNumber << " ---\n";
    for (const Booking& b : bookings)
        if (b.getRoom().getNumber() == roomNumber) {
            std::cout << "#" << index++ << ": " << b << "\n";
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
            std::cout << "#" << index++ << ": " << b << "\n";
        }
    }
    else {
        std::cout << "Invalid choice, please try again.\n";
    }

}

bool Hotel::isRoomAvailable(int roomNumber, const std::string& newCheckIn, int nights) const {
    std::string newCheckOut = Booking::calculateCheckout(newCheckIn, nights);

    for (const auto& booking : bookings) {
        if (booking.getRoom().getNumber() == roomNumber) {
            const std::string& existingCheckIn = booking.getCheckIn();
            std::string existingCheckOut = booking.getCheckout();

            if (!(newCheckOut <= existingCheckIn || newCheckIn >= existingCheckOut)) {
                throw BookingConflictException();
            }
        }
    }
    return true;
}

std::pair<std::string, std::string> Hotel::findNextAvailablePeriod(int roomNumber, const std::string& checkIn, int nights) const {
    std::string newCheckOut = Booking::calculateCheckout(checkIn, nights);


    std::vector<Booking> roomBookings;
    for (const Booking& b : bookings) {
        if (b.getRoom().getNumber() == roomNumber) {
            roomBookings.push_back(b);
        }
    }

    std::sort(roomBookings.begin(), roomBookings.end(), compareByCheckIn);

    if (roomBookings.empty()) {
        return {checkIn, newCheckOut};  // Nicio rezervare
    }

    // dacă checkIn este dupa ultima rezervare
    const Booking& lastBooking = roomBookings.back();
    if (checkIn >= lastBooking.getCheckout()) {
        return {checkIn, newCheckOut};
    }

    //  verificăm între rezervări
    const Booking& first = roomBookings.front();
    if (newCheckOut <= first.getCheckIn()) {
        return {checkIn, newCheckOut};
    }

    size_t n = roomBookings.size();
    for (size_t i = 0; i < n - 1; ++i) {
        const Booking& current = roomBookings[i];
        const Booking& next = roomBookings[i + 1];

        std::string currentCheckout = current.getCheckout();
        std::string nextCheckIn = next.getCheckIn();

        std::string possibleCheckout = Booking::calculateCheckout(currentCheckout, nights);
        if (possibleCheckout <= nextCheckIn) {
            return {currentCheckout, possibleCheckout};
        }
    }

    // Default fallback
    const Booking& last = roomBookings.back();
    std::string lastCheckout = last.getCheckout();

    std::string newCheckout = Booking::calculateCheckout(lastCheckout, nights);

    return {lastCheckout, newCheckout};
}

// Guest
std::shared_ptr<Guest> Hotel::findGuestById(const std::string& guestId) const {
    for (const auto& booking : bookings) {
        if (booking.getGuest()->getId() == guestId)
            return booking.getGuest();
    }
    return nullptr;
}

std::vector<Booking> Hotel::getBookingsForGuest(const std::string& guestId) const {
    std::vector<Booking> result;
    for (const auto& booking : bookings) {
        if (booking.getGuest()->getId() == guestId) {
            result.push_back(booking);
        }
    }
    return result;
}


// Rooms
const std::vector<Room>& Hotel::getAllRooms() const {
    return rooms;
}

Room* Hotel::findRoomByNumber(int roomNumber) {
    for (auto& room : rooms) {
        if (room.getNumber() == roomNumber) {
            return &room;
        }
    }
    throw RoomNotFoundException(roomNumber);
}

Room* Hotel::findAvailableRoomByType(const std::string& type, const std::string& checkIn, int nights) {
    for (auto& room : rooms) {
        if (room.getType() == type) {
            return &room;
        }
    }
    return nullptr;
}

// CSV
void Hotel::loadRoomsFromCSV(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening room CSV file: " << filename << "\n";
        return;
    }

    rooms.clear();
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string numberStr, type, priceStr;

        if (std::getline(iss, numberStr, ',') &&
            std::getline(iss, type, ',') &&
            std::getline(iss, priceStr)) {
            try {
                int number = std::stoi(numberStr);
                double price = std::stod(priceStr);
                rooms.emplace_back(number, type, price);
            } catch (const std::exception& e) {
                std::cerr << "Invalid room data: " << line << " – " << e.what() << "\n";
            }
            }
    }

    std::cout << "Loaded " << rooms.size() << " rooms from " << filename << ".\n";
}


void Hotel::saveBookingsToCSV(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << "\n";
        return;
    }
    for (const auto& booking : bookings) {
        fout << booking.toCSV() << "\n";
    }
}
void Hotel::loadBookingsFromCSV(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << "\n";
        return;
    }
    bookings.clear();
    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        try {
            Booking b = Booking::fromCSV(line, rooms);
            bookings.push_back(b);
        }
        catch (const std::exception& e) {
            std::cerr << "Error reading booking, skipping line. Reason: " << e.what() << "\n";
        }
    }
}