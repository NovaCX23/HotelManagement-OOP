#include<iostream>

#include "../includes/Room.h"
#include "../includes/Guest.h"
#include "../includes/Booking.h"
#include "../includes/Hotel.h"

int main() {
    // Test room
    Room room1(101, "single", 99.99);
    Room room2(102, "double", 199.99);
    std::cout << room1 << std::endl;

    std::cout << "Room number:" << room1.getNumber() << std::endl;
    std::cout << "Room type:" << room1.getType() << std::endl;
    std::cout << "Room price:" << room1.getPrice() << std::endl;

    // Test Guest
    Guest guest1("Ana", "APP123");
    std::cout << "Ana'id is: " << guest1.getId() << std::endl;
    Guest guest2("Alex", "IV456"); // ID invalid
    Guest guest3("Ion", "ION012");
    Guest guest4("Matei", "MAT101");


    std::cout << guest1 << "\n";
    std::cout << "ID valid? " << (guest1.isValidId() ? "Yes" : "No") << "\n"; // true

    std::cout << guest2 << "\n";
    std::cout << "ID valid? " << (guest2.isValidId() ? "Yes" : "No")<< "\n"; // false

    // Test Booking
    /*
    Booking booking1(room1, guest1, "2023-10-01", 3);
    std::cout << booking1 << "\n";

    Booking booking2 = booking1;
    booking2 = booking1;

    std::cout << "Total price:  " << booking1.getTotalPrice() << "\n";
    std::cout << "Is active?  " << booking1.isActive("2023-10-02") << "\n";
    */

    // Test Hotel
    Hotel hotel;
    hotel.addBooking(Booking(room1, guest1, "2024-10-02", 3));
    hotel.addBooking(Booking(room2, guest2, "2024-10-06", 2));
    std::cout << (hotel.isRoomAvailable(101, "2024-10-05") ? "Yes" : "No") << std::endl;
    hotel.addBooking(Booking(room1, guest4, "2024-10-05", 3));

    hotel.displayAllBookings();

    std::cout << "=== Availability ===\n";
    std::cout << "Room 102 available on 2024-10-02? "
              << (hotel.isRoomAvailable(101, "2024-10-02") ? "Yes" : "No") << "\n";
    std::cout << "Room 102 available on 2024-10-10? "
              << (hotel.isRoomAvailable(102, "2024-10-10") ? "Yes" : "No") << "\n";


    std::cout << "=== Cancel reservation ===\n";
    hotel.cancelBooking(101);

    std::cout << "=== Remaining reservations ===\n";
    hotel.displayAllBookings();


    return 0;
}