#include "../includes/TestRunner.h"

int main() {
    Hotel hotel;
    TestRunner::RunTestsFromFile("tastatura.txt", hotel);
    return 0;
}