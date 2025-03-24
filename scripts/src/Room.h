#ifndef ROOM_H
#define ROOM_H
#include <string>

class Room {
    int number;
    std::string type;
    double price;
public:
    Room(int number, std::string type, double price);

    // Getters
    int getNumber();
    std::string getType();
    double getPrice();
};



#endif //ROOM_H
