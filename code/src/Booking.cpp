#include "../includes/Booking.h"

Booking::Booking(const Room &room, const Guest &guest, int nights)
    : room(room), guest(guest), nights(nights){}

double Booking::getTotalPrice() const {
    return room.getPrice() * nights;
}
