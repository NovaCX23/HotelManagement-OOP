#include "../includes/Room.h"

#include <iterator>
#include <string>

Room::Room(int number, const std::string& type,double price)
    : number(number), type(type), price(price){}

// Getters
int Room::getNumber() const {return number;}
std::string Room::getType() const {return type;}
double Room::getPrice() const {return price;}

// Overload <<
std::ostream &operator<<(std::ostream &out, const Room &room) {
    out << "Room " << room.number << " (" << room.type << "): $" << room.price << "/night";
    return out;
}



