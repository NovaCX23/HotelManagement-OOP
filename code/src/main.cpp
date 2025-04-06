#include "../includes/TestRunner.h"

int main() {
    Hotel hotel;
    //TestRunner::RunTestsFromFile("tastatura.txt", hotel);
    TestRunner::RunInteractiveMenu(hotel);
    return 0;
}