#include "../includes/Menu.h"

int main() {
    Hotel hotel;
    Menu::RunInteractiveMenu(hotel);
    return 0;
}

//TODO: la menu ul principal 4 devine manage bookings(display, save, load)(meniu sep)
//    5 devine eventual manage guest(beneficii, ...)
//    cancellation cost
//    eventual rethink (roomUpgrade cel mai probabil vine mai bine altundeva decat in guest)