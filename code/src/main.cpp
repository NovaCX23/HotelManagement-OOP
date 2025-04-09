#include "../includes/TestRunner.h"

int main() {
    //TODO: !!! Atunci cand cauta disponibilitatea unei camere dupa stergere nu apare
    //  Verificare date disponibilitate incepand cu data pe care o dau eu
    //  Stergerea trebuie sa fie mai precisa decat doar numarul camerei, momentan doar le sterge
    // la rand, o idee ar fi sa mi listeze toate datele la camera respectiva si doar sa aleg data - done
    //  Cand dau display la bookings ar fi o idee sa fie sortate dupa data , indiferent de tipul de camera

    //  Oare era mai bine sa fac in booking disponibilitatea ??

    //TODO: trecere la tema 2 -> implementare de derivate


    //TODO: eventual modificat descrierea proiectului lmao
    Hotel hotel;
    TestRunner::RunInteractiveMenu(hotel);
    return 0;
}