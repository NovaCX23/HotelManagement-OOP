#include "../includes/Menu.h"
#include "../includes/Exceptions.h"


int main() {
    try {
        Hotel hotel;
        hotel.loadRoomsFromCSV("data/rooms.csv");
        Menu::RunInteractiveMenu(hotel);
    }
    catch (const Exceptions& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected system error: " << e.what() << std::endl;
    }
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
//    exit ul din program nu e un exit real

// TODO: Posibile probleme cu csv-ul, gen rezervari pe aceeasi data
//   O problema pe care nu cred ca o sa apuc sa o implementez este ca daca dau load dupa ce am adaugat deja
//  niste booking uri o sa le dea clear ,
//   Alta chestie e sa modific ceva ca sa se reflecte real modificarile facute pe bookings.csv
//   Implementare reala pentru posibilitatea de a cumpara servicii extra


// TODO: momentan adaug costul de vip de fiecare data , chiar daca se repeta clientul