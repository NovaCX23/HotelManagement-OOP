#ifndef BOOKING_H
#define BOOKING_H

#include "Room.h"
#include "Guest.h"
#include <string>

class Booking {
    Room room;
    Guest guest;
    int nights;
public:
    Booking(const Room& room, const Guest& guest, int nights);

    double getTotalPrice() const;
};



#endif //BOOKING_H
