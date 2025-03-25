#include "../includes/Room.h"

#include <iostream>
#include <string>

Room::Room(int number, const std::string& type, double price)
    : number(number), type(type), price(price) {}

// Overload <<
std::ostream &operator<<(std::ostream &os, const Room &room) {
    os << "Room " << room.number << " (" << room.type << "): $" << room.price << "/night";
    return os;
}



