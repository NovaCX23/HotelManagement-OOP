#include "../includes/TestRunner.h"

int main() {
    //TODO: Booking.cpp + TestRunner.cpp
    Hotel hotel;
    //TestRunner::RunTestsFromFile("tastatura.txt", hotel);
    TestRunner::RunInteractiveMenu(hotel);
    return 0;
}