#include "../includes/Menu.h"

int main() {

    Hotel hotel;
    hotel.loadRoomsFromCSV("../data/rooms.csv");
    Menu::RunInteractiveMenu(hotel);
    return 0;

}

//TODO: la menu ul principal 4 devine manage bookings(display, save, load)(meniu sep)
//    cancellation cost
//    calcul profit propriu-zis hotel tinand cont de pierderi
//    cost de a deveni vip undeva adunat la profit
//    separare beneficii vip mai mult, impartite pe tier
//    eventual rethink (roomUpgrade cel mai probabil vine mai bine altundeva decat in guest)
//    erori la bife ca nu folosesc inca functiile , o sa dispara curand
//    adaugare un numar concret de camere si o procesare mai buna a booking urilor in functie de tipul de guest
//    la event daca nu respecta FullHotelBooking trebuie implementata o alternativa
//    functionalitate in hotel pt FullHotelBooking
//    update guest dependent stuff obv :))
//    discount for guest trebuie sa stie deja cate nopti sta guest ul
// probleme:
//    erori bife



// TODO: Posibile probleme cu csv-ul, gen rezervari pe aceeasi data