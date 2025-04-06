#include <fstream>
#include <iostream>
#include "../includes/TestRunner.h"
#include "../includes/Room.h"
#include "../includes/Guest.h"
#include "../includes/Booking.h"

void TestRunner::RunTestsFromFile(const std::string& filename, Hotel& hotel) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }
    int option;
    while (fin >> option) {
        switch (option) {
            case 1: { // Adauga rezervare
                int roomNumber, nights;
                std::string guestName, guestId, checkInDate;
                fin >> roomNumber >> guestName >> guestId >> checkInDate >> nights;

                Room room(roomNumber, "single", 99.99);
                Guest guest(guestName, guestId);

                if (guest.isValidId()) {
                    hotel.addBooking(Booking(room, guest, checkInDate, nights));
                }
                else { std::cout << "Invalid ID for guest: " << guestId << "\n"; }
                break;
            }
            case 2: { // Anulare rezervare
                int roomNumber;
                fin >> roomNumber;
                hotel.cancelBooking(roomNumber);
                break;
            }
            case 3: { // Verificare disponibilitate
                int roomNumber;
                std::string date;
                fin >> roomNumber >> date;
                std::cout << "Room " << roomNumber << " availability on " << date << ": "
                          << (hotel.isRoomAvailable(roomNumber, date) ? "Yes" : "No") << "\n";
                break;
            }
            case 4: { // Afisare rezervari
                hotel.displayAllBookings();
                break;
            }
            case 5: {
                std::cout << "Exit..\n";
                return;
            }
            default: {
                std::cerr << "Error: Invalid option: " << option << "\n";
            }
        }
    }
}