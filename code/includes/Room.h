#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>

class Room {
    int number;
    std::string type;
    double price;
public:
    //Constructors
    Room(int number, const std::string& type, double price);

    // Getters
    int getNumber() const { return number; }
    std::string getType() const { return type; }
    double getPrice() const { return price; }

    // Operators
    friend std::ostream& operator<<(std::ostream& os, const Room& room);
};

#endif  //ROOM_H
