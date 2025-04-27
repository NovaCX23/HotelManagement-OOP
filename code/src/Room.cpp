#include "../includes/Room.h"

Room::Room(int number, const std::string& type, double price)
    : number(number), type(type), price(price) {}

// Getters
int Room::getNumber() const {
    return number;
}
const std::string& Room::getType() const {
    return type;
}
double Room::getPrice() const {
    return price;
}

// Overload <<
std::ostream &operator<<(std::ostream &os, const Room &room) {
    os << "Room " << room.number << " (" << room.type << "): $" << room.price << "/night";
    return os;
}



