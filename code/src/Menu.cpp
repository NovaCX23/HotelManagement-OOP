#include <fstream>
#include <iostream>
#include <set>

#include "../includes/Menu.h"
#include "../includes/Room.h"
#include "../includes/Booking.h"
#include "../includes/Guest.h"

bool isValidDateFormat(const std::string& date) {
    return date.size() == 10 && date[4] == '-' && date[7] == '-';
}

void Menu::RunInteractiveMenu(Hotel& hotel) {
    while (true) {
        std::cout << "\n--- Hotel Management ---\n";
        std::cout << "1. Manage Bookings\n";
        std::cout << "2. Manage Guests\n";
        std::cout << "0. Exit\n";
        std::cout << "Select an option: ";

        int option;
        if (!(std::cin >> option)) {
            std::cout << "Invalid input or end of input. Exiting...\n";
            return;
        }
        switch (option) {
            case 1:
                displayBookingsMenu(hotel);
            break;
            case 2:
                displayGuestsMenu(hotel);
            break;
            case 0:
                std::cout << "Exiting...\n";
            break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void Menu::displayBookingsMenu(Hotel& hotel) {
    while (true){
        std::cout << "\n--- Manage Bookings ---\n";
        std::cout << "1. Add Booking\n";
        std::cout << "2. Cancel Booking\n";
        std::cout << "3. Check Room Availability\n";
        std::cout << "4. Display All Bookings\n";
        std::cout << "5. Save Bookings to CSV\n";
        std::cout << "6. Load Bookings from CSV\n";
        std::cout << "0. Back\n";
        std::cout << "Choose option: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input or end of input. Exiting...\n";
            return;
        }

        switch (choice) {
            case 1: { // Add booking
                std::string guestName, guestId, checkInDate, roomType;
                int nights;

                // Guest
                std::cout << "Enter guest name: ";
                std::getline(std::cin >> std::ws, guestName);
                std::cout << "Enter guest id: ";
                std::cin >> guestId;

                auto guest = Guest::createFromInput(guestName, guestId);
                if (!guest->isValidId()) {
                    std::cout << "Invalid ID format! Must be 3 letters + 3 digits (ABC123).\n";
                    break;
                }

                // Room type
                std::cout << "Enter desired room type (Standard/Deluxe/Suite): ";
                std::cin >> roomType;

                std::cout << "Enter check-in date (YYYY-MM-DD) and number of nights: ";
                std::cin >> checkInDate >> nights;
                std::cin.get();

                if (!isValidDateFormat(checkInDate)) {
                    std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                    break;
                }
                if (nights <= 0) {
                    std::cout << "Invalid number of nights.\n";
                    break;
                }

                // Try to find available room directly
                Room* roomPtr = hotel.findAvailableRoomByType(roomType, checkInDate, nights);
                if (roomPtr) {
                    Room room = *roomPtr;
                    hotel.addBooking(Booking(room, guest, checkInDate, nights));
                    std::cout << "Booking confirmed for Room " << room.getNumber()
                              << " from " << checkInDate << " to "
                              << Booking::calculateCheckout(checkInDate, nights) << "\n";
                    break;
                }

                // No room available – show the 3 closest availability options
                std::cout << "No available " << roomType << " room for that period.\n";
                std::vector<std::pair<std::string, const Room*>> suggestions;

                for (const auto& room : hotel.getAllRooms()) {
                    if (room.getType() == roomType) {
                        auto [startDate, endDate] = hotel.findNextAvailablePeriod(room.getNumber(), checkInDate, nights);
                        suggestions.emplace_back(startDate, &room);
                    }
                }

                std::sort(suggestions.begin(), suggestions.end());

                std::vector<int> shownRooms;
                int count = 0;

                std::cout << "The 3 closest available options:\n";
                for (const auto& [startDate, roomPtr] : suggestions) {
                    std::string endDate = Booking::calculateCheckout(startDate, nights);
                    std::cout << "- Room " << roomPtr->getNumber()
                              << " | From: " << startDate << " to " << endDate << "\n";
                    shownRooms.push_back(roomPtr->getNumber());
                    ++count;
                    if (count == 3) break;
                }

                // Option to book one of them
                char confirm;
                std::cout << "Would you like to book one of these? (y/n): ";
                std::cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    int chosenRoom;
                    std::cout << "Enter the room number you want to book: ";
                    std::cin >> chosenRoom;

                    bool valid = false;
                    std::string chosenStartDate;

                    for (const auto& [startDate, roomPtr] : suggestions) {
                        if (roomPtr->getNumber() == chosenRoom) {
                            chosenStartDate = startDate;
                            valid = true;
                            Room room = *roomPtr;
                            hotel.addBooking(Booking(room, guest, chosenStartDate, nights));
                            std::cout << "Booking confirmed for Room " << room.getNumber()
                                      << " from " << chosenStartDate << " to "
                                      << Booking::calculateCheckout(chosenStartDate, nights) << "\n";
                            break;
                        }
                    }
                    if (!valid) {
                        std::cout << "Invalid room number.\n";
                    }
                }

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
            case 0: { // Exit
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

void Menu::displayGuestsMenu(const Hotel& hotel) {
    while (true) {
        std::cout << "\n--- Manage Guests ---\n";
        std::cout << "1. List all guests\n";
        std::cout << "2. Show benefits for guest (by ID)\n";
        std::cout << "3. Show discount for guest (by ID)\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Choose option: ";

        int option;
        if (!(std::cin >> option)) {
            std::cout << "Invalid input or end of input. Exiting...\n";
            return;
        }

        switch (option) {
            case 1: { // List all guests
                std::set<std::string> seen;
                for (const auto& b : hotel.getAllBookings()) {
                    auto guest = b.getGuest();
                    if (seen.insert(guest->getId()).second) {
                        std::cout << "- " << guest->getName()
                                  << " | " << guest->getId()
                                  << " | " << guest->getType() << "\n";
                    }
                }
                break;
            }
            case 2: { // Show benefits
                std::string id;
                std::cout << "Enter guest ID: ";
                std::cin >> id;
                if (auto guest = hotel.findGuestById(id)) {
                    guest->displayBenefits();
                } else {
                    std::cout << "Guest not found.\n";
                }
                break;
            }
            case 3: { // Show discount
                std::string id;
                std::cout << "Enter guest ID: ";
                std::cin >> id;
                auto guest = hotel.findGuestById(id);
                if (guest) {
                    auto bookings = hotel.getBookingsForGuest(id);
                    if (bookings.empty()) {
                        std::cout << "This guest has no bookings.\n";
                    }
                    else {
                        std::cout << "Discounts for guest:\n";
                        for (const auto& booking : bookings) {
                            std::cout << "- Booking from " << booking.getCheckIn()
                                      << " for " << booking.getNights() << " nights: "
                                      << guest->guestDiscount(booking.getNights()) * 100 << "%\n";
                        }
                    }
                }
                else {
                    std::cout << "Guest not found.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    }
}