#include <fstream>
#include <iostream>
#include "../includes/TestRunner.h"
#include "../includes/Room.h"
#include "../includes/Guest.h"
#include "../includes/Booking.h"

bool isValidDateFormat(const std::string& date) {
    return date.size() == 10 && date[4] == '-' && date[7] == '-';
}

void TestRunner::RunInteractiveMenu(Hotel& hotel) {

    static bool start = false;
    if (!start) {
        Guest g1("Ana", "AAA111");
        Guest g2("Ion", "III222");

        Room r1(101, "single", 101.99);
        Room r2(201, "double", 171.99);

        Booking b1(r1, g1, "2025-01-01", 3);
        Booking b2(r2, g2, "2025-01-08", 4);

        hotel.addBooking(b1);
        hotel.addBooking(b2);

        start = true;
        std::cout << "[Initial bookings loaded]\n";
    }

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

                if (!isValidDateFormat(checkInDate)) {
                    std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                    break;
                }

                if (nights <= 0) {
                    std::cout << "Invalid number of nights. Must be greater than 0.\n";
                    break;
                }

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
