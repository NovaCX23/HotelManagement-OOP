#ifndef MENU_H
#define MENU_H

#include "Hotel.h"
#include "Exceptions.h"
#include "Room.h"
#include "Booking.h"
#include "Guest.h"
#include "VIPGuest.h"
#include "CorporateGuest.h"
#include "EventGuest.h"
#include "InfluencerGuest.h"
#include "GuestFactory.h"
#include "Report.h"

class Menu {

public:

    static void RunInteractiveMenu(Hotel& hotel);
    static void displayBookingsMenu(Hotel& hotel);
    static void displayGuestsMenu(const Hotel& hotel);
    static void displayAnalyticsMenu(const Hotel& hotel);
};

#endif //MENU_H
