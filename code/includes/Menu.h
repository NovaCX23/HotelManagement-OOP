#ifndef MENU_H
#define MENU_H

#include "Hotel.h"
class Menu {

public:

    static void RunInteractiveMenu(Hotel& hotel);
    static void displayBookingsMenu(Hotel& hotel);
    static void displayGuestsMenu(const Hotel& hotel);
};

#endif //MENU_H
