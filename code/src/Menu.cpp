#include <fstream>
#include <iostream>
#include <set>
#include <map>

#include "../includes/Menu.h"


bool isValidDateFormat(const std::string& date) {
    return date.size() == 10 && date[4] == '-' && date[7] == '-';
}

void Menu::RunInteractiveMenu(Hotel& hotel) {
    while (true) {
        std::cout << "\n--- Hotel Management ---\n";
        std::cout << "1. Manage Bookings\n";
        std::cout << "2. Manage Guests\n";
        std::cout << "3. Manage Analytics\n";
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
            case 3:
                displayAnalyticsMenu(hotel);
            break;
            case 0: {
                std::cout << "Exiting...\n";
                return;
            }
            default: {
                std::cout << "Invalid choice. Try again.\n";
                break;
            }
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
                std::string guestName, guestId;
                std::cout << "Enter guest name: ";
                std::getline(std::cin >> std::ws, guestName);
                std::cout << "Enter guest id: ";
                std::cin >> guestId;

                try{
                    auto guest = GuestFactory::createFromInput(guestName, guestId);

                    // Room type
                    std::cout << "Enter desired room type (Standard/Deluxe/Suite): ";
                    std::string roomType;
                    std::cin >> roomType;

                    std::cout << "Enter check-in date (YYYY-MM-DD) and number of nights: ";
                    std::string checkInDate;
                    int nights;
                    std::cin >> checkInDate >> nights;
                    std::cin.get();

                    if (!isValidDateFormat(checkInDate)) {
                        throw InvalidDateFormatException(checkInDate);
                    }
                    if (nights <= 0) {
                        throw InvalidNightsException(nights);
                    }

                    // Try to find available room directly
                    const Room* availableRoom = hotel.findRoomByType(roomType);
                    if (availableRoom) {
                        Room room = *availableRoom;
                        hotel.addBooking(Booking(room, guest->clone(), checkInDate, nights));
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
                    for (const auto& [startDate, suggestedRoom] : suggestions) {
                        std::string endDate = Booking::calculateCheckout(startDate, nights);
                        std::cout << "- Room " << suggestedRoom->getNumber()
                                  << " | From: " << startDate << " to " << endDate << "\n";
                        shownRooms.push_back(suggestedRoom->getNumber());
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

                        for (const auto& [startDate, suggestedRoom] : suggestions) {
                            if (suggestedRoom->getNumber() == chosenRoom) {
                                chosenStartDate = startDate;
                                valid = true;
                                Room room = *suggestedRoom;
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
                }
                catch (const InvalidGuestIdException& e) {
                    std::cout << e.what() << std::endl;
                    break;
                }
                catch (const Exceptions& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                    break;
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
            case 3: { // General availability checker

                try{
                    std::string checkInDate;
                    int nights;
                    std::cout << "Enter check-in date (YYYY-MM-DD): ";
                    std::cin >> checkInDate;
                    std::cout << "Enter number of nights: ";
                    std::cin >> nights;
                    std::cin.get();

                    if (!isValidDateFormat(checkInDate)) {
                        throw InvalidDateFormatException(checkInDate);
                    }
                    if (nights <= 0) {
                        throw InvalidNightsException(nights);
                    }

                    std::map<std::string, std::vector<const Room*>> available;
                    for (const auto& room : hotel.getAllRooms()) {
                        if (hotel.isRoomAvailable(room.getNumber(), checkInDate, nights)) {
                            available[room.getType()].push_back(&room);
                        }
                    }

                    if (available.empty()) {
                        std::cout << "No rooms available for the selected period.\n";
                    }
                    else {
                        std::cout << "--- Available rooms ---\n";
                        for (const auto& [type, rooms] : available) {
                            std::cout << type << ":\n";
                            for (const auto* r : rooms) {
                                std::cout << "  - Room " << r->getNumber()
                                          << " ($" << r->getPrice() << " per night)\n";
                            }
                        }
                    }
                }
                catch (const Exceptions& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                    break;
                }

                break;
            }
            case 4: { // Display All Bookings
                hotel.displayAllBookings();
                std::cout << "\n";
                std::cout << "Total number of bookings in the system: " << Booking::getTotalBookings() << "\n";
                break;
            }
            case 5: { // Save Bookings to CSV
                std::string filename;
                std::cout << "Enter filename to save: (bookings.csv) ";
                std::cin >> filename;
                hotel.saveBookingsToCSV("data/" + filename);
                std::cout << "Bookings saved successfully to " << filename << "\n";
                break;
            }
            case 6: { // Load Bookings from CSV
                std::string filename;
                std::cout << "Enter filename to load: (bookings.csv) ";
                std::cin >> filename;
                hotel.loadBookingsFromCSV("data/" + filename);
                std::cout << "Bookings loaded successfully from " << filename << "\n";
                break;
            }
            case 0:
                return;
            default: {
                std::cout << "Invalid option. Please try again.\n";
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
        std::cout << "4. Show detailed guest summary (by ID)\n";
        std::cout << "0. Back\n";
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
            case 4: {
                std::string id;
                std::cout << "Enter guest ID: ";
                std::cin >> id;

                auto guest = hotel.findGuestById(id);
                if (!guest) {
                    std::cout << "Guest not found.\n";
                    break;
                }

                std::cout << "\n--- Guest Details ---\n";
                std::cout << "Name: " << guest->getName() << "\n";
                std::cout << "ID: " << guest->getId() << "\n";

                std::cout << guest->getSummary() << "\n";


                std::cout << "\nFree Benefits:\n";
                auto freeBenefits = guest->getFreeBenefits();
                if (freeBenefits.empty()) {
                    std::cout << "  - None\n";
                } else {
                    for (const auto& b : freeBenefits) {
                        std::cout << "  - " << b << "\n";
                    }
                }

                auto bookings = hotel.getBookingsForGuest(id);
                if (bookings.empty()) {
                    std::cout << "\nNo bookings found.\n";
                } else {
                    double totalPaid = 0.0;
                    std::cout << "\n--- Bookings ---\n";
                    for (const auto& booking : bookings) {
                        double discount = guest->guestDiscount(booking.getNights());
                        double price = booking.getBookingPrice();
                        totalPaid += price;

                        std::cout << "Booking: Room " << booking.getRoom().getNumber()
                                  << " | " << booking.getCheckIn()
                                  << " for " << booking.getNights() << " nights\n";
                        std::cout << "  - Discount applied: " << discount * 100 << "%\n";
                        std::cout << "  - Paid: $" << price << "\n";
                    }
                    std::cout << "Total amount paid by this guest: $" << totalPaid << "\n";
                }

                break;
            }


            case 0:
                return;
            default: {
                std::cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    }
}


void Menu::displayAnalyticsMenu(Hotel& hotel) {
    while (true) {
        std::cout << "\n--- Hotel Analytics ---\n";
        std::cout << "1. Show Total Profit Report\n";
        std::cout << "2. Show Guest Report (by type)\n";
        std::cout << "0. Back\n";
        std::cout << "Choose option: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input or end of input. Exiting...\n";
            return;
        }

        switch (choice) {
            case 1: {
                std::cout << "\n--- TOTAL PROFIT REPORT ---\n";

                double gross = hotel.getGrossBookingProfit();
                double booking = hotel.getBookingProfit();
                double losses = gross - booking;
                double net = hotel.getTotalProfit();

                std::cout << "Gross Booking Profit (without losses): $" << gross << "\n";
                std::cout << "Total Losses from Free Benefits:       -$" << losses << "\n";
                std::cout << "---------------------------------------------\n";
                std::cout << "Net Booking Profit (after losses):     $" << booking << "\n";
                std::cout << "VIP Upgrade Profit:                    +$" << hotel.getVIPProfit() << "\n";
                std::cout << "Cancellation Profit:                   +$" << hotel.getCancellationProfit() << "\n";
                std::cout << "---------------------------------------------\n";
                std::cout << "->  TOTAL NET PROFIT:                     $" << net << "\n";
                break;
            }

            case 2: {
                std::string type;
                std::cout << "Enter guest type (Standard/ VIP / Corporate / Event / Influencer): ";
                std::cin >> type;

                if (type == "VIP") {
                    Report<VIPGuest> report;
                    report.generate(hotel.getAllBookings());
                    if (auto strat = hotel.getProfitStrategy()) {
                        double profit = calculateProfitForType<VIPGuest>(hotel.getAllBookings(), *strat);
                        std::cout << "Total profit from VIP guests: $" << profit << "\n";
                    }
                } else if (type == "Corporate") {
                    Report<CorporateGuest> report;
                    report.generate(hotel.getAllBookings());
                    if (auto strat = hotel.getProfitStrategy()) {
                        double profit = calculateProfitForType<CorporateGuest>(hotel.getAllBookings(), *strat);
                        std::cout << "Total profit from Corporate guests: $" << profit << "\n";
                    }
                } else if (type == "Event") {
                    Report<EventGuest> report;
                    report.generate(hotel.getAllBookings());if (auto strat = hotel.getProfitStrategy()) {
                        double profit = calculateProfitForType<EventGuest>(hotel.getAllBookings(), *strat);
                        std::cout << "Total profit from Event guests: $" << profit << "\n";
                    }
                } else if (type == "Influencer") {
                    Report<InfluencerGuest> report;
                    report.generate(hotel.getAllBookings());
                    if (auto strat = hotel.getProfitStrategy()) {
                        double profit = calculateProfitForType<InfluencerGuest>(hotel.getAllBookings(), *strat);
                        std::cout << "Total profit from Influencer guests: $" << profit << "\n";
                    }
                } else if (type == "Standard") {
                    int count = 0;
                    double total = 0.0;

                    if (auto strat = hotel.getProfitStrategy()) {
                        for (const auto& b : hotel.getAllBookings()) {
                            auto g = b.getGuest();
                            if (!std::dynamic_pointer_cast<VIPGuest>(g) &&
                                !std::dynamic_pointer_cast<CorporateGuest>(g) &&
                                !std::dynamic_pointer_cast<EventGuest>(g) &&
                                !std::dynamic_pointer_cast<InfluencerGuest>(g)) {
                                ++count;
                                total += strat->computeProfit(b);
                                }
                        }
                        std::cout << "\n--- Report for Standard guests ---\n";
                        std::cout << "Total guests of selected type: " << count << "\n";
                        std::cout << "Total profit from Standard guests: $" << total << "\n";
                    }
                } else {
                    std::cout << "Unknown type.\n";
                }
                break;
            }
            case 0:
                return;
            default:
                std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }
}
