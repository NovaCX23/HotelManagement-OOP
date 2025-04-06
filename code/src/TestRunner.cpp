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
    std::cout << "File " << filename << " opened successfully.\n";
    int option;
    while (fin >> option) {
        switch (option) {
            case 1: { // Add booking
                int roomNumber, nights;
                double price;
                std::string guestName, roomType, guestId, checkInDate;
                fin >> roomNumber >> roomType >> price >> guestName >> guestId >> checkInDate >> nights;

                Room room(roomNumber, roomType, price);
                Guest guest(guestName, guestId);

                if (guest.isValidId()) {
                    hotel.addBooking(Booking(room, guest, checkInDate, nights));
                }
                else { std::cout << "Invalid ID for guest: " << guestId << "\n"; }
                break;
            }
            case 2: { // Cancel booking
                int roomNumber;
                fin >> roomNumber;
                hotel.cancelBooking(roomNumber);
                break;
            }
            case 3: { // Check Room Availability
                int roomNumber;
                std::string date;
                fin >> roomNumber >> date;
                std::cout << "Room " << roomNumber << " availability on " << date << ": "
                          << (hotel.isRoomAvailable(roomNumber, date) ? "Yes" : "No") << "\n";
                break;
            }
            case 4: { // Display All Bookings
                hotel.displayAllBookings();
                break;
            }
            case 5: { // Exit
                std::cout << "Exiting...\n";
                return;
            }
            default: {
                std::cerr << "Error: Invalid option: " << option << "\n";
            }
        }
    }
}

void TestRunner::RunInteractiveMenu(Hotel& hotel) {
    std::cout << "\n--- Hotel Management System ---\n";
    while (true) {
        std::cout << "\n1. Add Booking\n";
        std::cout << "2. Cancel Booking\n";
        std::cout << "3. Check Room Availability\n";
        std::cout << "4. Display All Bookings\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an option(number): ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input or end of input. Exiting...\n";
            return;
        }
        std::cin >> choice;

        switch (choice) {
            case 1: { // Add booking
                std::string guestName, guestId, checkInDate;
                int nights;
                double price;
                std::string roomType;
                int roomNumber;

                // Guest information
                std::cout << "Enter guest name and ID: ";
                std::cin >> guestName >> guestId;

                Guest guest(guestName, guestId);

                if (!guest.isValidId()) {
                    std::cout << "Invalid ID: " << guestId << " for guest: " << guestName << "\n";
                    break;
                }

                // Room information
                std::cout << "Enter room number, category and price: ";
                std::cin >> roomNumber >> roomType >> price;

                // Check-in details
                std::cout << "Enter check-in date (YYYY-MM-DD) and number of nights: ";
                std::cin >> checkInDate >> nights;

                // Check availability
                if (!hotel.isRoomAvailable(roomNumber, checkInDate)) {
                    std::cout << "Room unavailable. Check availability\n";
                    break;
                }

                Room room(roomNumber, roomType, price);
                hotel.addBooking(Booking(room, guest, checkInDate, nights));
                break;
            }
            case 2: { // Cancel Booking
                int roomNumber;
                std::cout << "Enter room number to cancel booking: ";
                std::cin >> roomNumber;
                hotel.cancelBooking(roomNumber);
                break;
            }
            case 3: { // Check Room Availability
                //TODO: Instead of saying if room is available it would be better if this
                // was checking when the room was available after a certain date
                int roomNumber;
                std::string date;
                std::cout << "Enter room number and date (YYYY-MM-DD) to check availability: ";
                std::cin >> roomNumber >> date;

                std::cout << "Room " << roomNumber << " availability on " << date << ":\n";
                std::cout << (hotel.isRoomAvailable(roomNumber, date) ? "Yes" : "No") << "\n";
                break;
            }
            case 4: { // Display All Bookings
                hotel.displayAllBookings();
                break;
            }
            case 5: { // Exit
                std::cout << "Exiting...\n";
                return;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
}
