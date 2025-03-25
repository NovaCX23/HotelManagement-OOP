#include<iostream>

#include "../includes/Room.h"
#include "../includes/Guest.h"
#include "../includes/Booking.h"

int main() {
    // Test room
    Room room(10, "single", 99.99);

    std::cout << room << std::endl;

    std::cout << "Room number:" << room.getNumber() << std::endl;
    std::cout << "Room type:" << room.getType() << std::endl;
    std::cout << "Room price:" << room.getPrice() << std::endl;

    // Test Guest
    Guest guest1("Ana", "APP123");
    Guest guest2("Ion", "IV456"); // ID invalid

    std::cout << guest1 << "\n";
    std::cout << "ID valid? " << guest1.isValidId() << "\n"; // true

    std::cout << guest2 << "\n";
    std::cout << "ID valid? " << guest2.isValidId() << "\n"; // false

    // Test Booking
    Booking booking1(room, guest1, "2023-10-01", 3);
    std::cout << booking1 << "\n";

    Booking booking2 = booking1;
    booking2 = booking1;

    std::cout << "Total price:  " << booking1.getTotalPrice() << "\n";
    std::cout << "Is active?  " << booking1.isActive("2023-10-02") << "\n";
    return 0;
}
