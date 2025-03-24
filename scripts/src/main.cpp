#include<iostream>


int main() {
    // Create a room
    ROOM room(10, "single", 99.99);

    std::cout << room << std::endl;

    // via getters
    std::cout << "Room number:" << room.getNumber() << std::endl;
    std::cout << "Room type:" << room.getType() << std::endl;
    std::cout << "Room price:" << room.getPrice() << std::endl;
    return 0;
}