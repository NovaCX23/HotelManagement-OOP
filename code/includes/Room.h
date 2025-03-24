#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>

class Room {
    int number;
    std::string type;
    double price;
public:
    Room(int number, const std::string& type, double price);

    // Getters
    int getNumber() const;
    std::string getType() const;
    double getPrice() const;

    // Overload << to print room details
    friend std::ostream& operator<<(std::ostream& os, const Room& room);
};

#endif  //ROOM_H
