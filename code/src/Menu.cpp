#include <fstream>
#include <iostream>
#include "../includes/Menu.h"
#include "../includes/Room.h"
#include "../includes/Guest.h"
#include "../includes/Booking.h"

bool isValidDateFormat(const std::string& date) {
    return date.size() == 10 && date[4] == '-' && date[7] == '-';
}

void Menu::RunInteractiveMenu(Hotel& hotel) {

    std::cout << "\n--- Hotel Management System ---\n";
    while (true) {
        std::cout << "\n1. Add Booking\n";
        std::cout << "2. Cancel Booking\n";
        std::cout << "3. Check Room Availability\n";
        std::cout << "4. Display All Bookings\n";
        std::cout << "5. Save Bookings to CSV\n";
        std::cout << "6. Load Bookings from CSV\n";
        std::cout << "7. Exit\n";
        std::cout << "Select an option(number): ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input or end of input. Exiting...\n";
            return;
        }

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
                    std::cout << "Invalid ID format! Must be 3 letters + 3 digits (ABC123).\n";
                    break;
                }

                // Room information
                std::cout << "Enter room number, category and price: ";
                std::cin >> roomNumber >> roomType >> price;
                if (roomNumber <= 0) {
                    std::cout << "Invalid room number. Must be a positive integer.\n";
                    break;
                }
                if (price <= 0) {
                    std::cout << "Invalid price. Must be greater than 0.\n";
                    break;
                }

                // Check-in details
                std::cout << "Enter check-in date (YYYY-MM-DD) and number of nights: ";
                std::cin >> checkInDate >> nights;
                std::cin.get();
                if (!isValidDateFormat(checkInDate)) {
                    std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                    break;
                }
                if (nights <= 0) {
                    std::cout << "Invalid number of nights. Must be greater than 0.\n";
                    break;
                }

                // Check availability
                if (!hotel.isRoomAvailable(roomNumber, checkInDate, nights)) {
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
                int roomNumber, nights;
                std::string date;
                std::cout << "Enter room number, date (YYYY-MM-DD) and nights to check availability: ";
                std::cin >> roomNumber >> date >> nights;

                bool hasBooking = false;
                for (const auto& b : hotel.getAllBookings()) {
                    if (b.getRoom().getNumber() == roomNumber) {
                        hasBooking = true;
                        break;
                    }
                }
                if (!isValidDateFormat(date)) {
                    std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                    break;
                }
                if (nights <= 0) {
                    std::cout << "Invalid number of nights. Must be greater than 0.\n";
                    break;
                }
                if (!hasBooking) {
                    std::cout << "No bookings found for room number: " << roomNumber << ".\n";
                    break;
                }

                auto nextPeriod = hotel.findNextAvailablePeriod(roomNumber, date, nights);
                std::cout << "Room " << roomNumber << " is available from: "
                          << nextPeriod.first << " to " << nextPeriod.second << "\n";
                break;
            }
            case 4: { // Display All Bookings
                hotel.displayAllBookings();
                break;
            }
            case 5: { // Save Bookings to CSV
                std::string filename;
                std::cout << "Enter filename to save: (bookings.csv) ";
                std::cin >> filename;
                hotel.saveBookingsToCSV("../data/" + filename);
                std::cout << "Bookings saved successfully to " << filename << "\n";
                break;
            }
            case 6: { // Load Bookings from CSV
                std::string filename;
                std::cout << "Enter filename to load: (bookings.csv) ";
                std::cin >> filename;
                hotel.loadBookingsFromCSV("../data/" + filename);
                std::cout << "Bookings loaded successfully from " << filename << "\n";
                break;
            }
            case 7: { // Exit
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
