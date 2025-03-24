#include "../includes/Guest.h"
#include<cctype>

Guest::Guest(const std::string &name, const std::string &id)
    :name(name), id(id){}

std::string Guest::getName() const { return name;}
std::string Guest::getId() const { return id;}

bool Guest::isValidId() const {
    // Exemplu: ID-ul trebuie să fie format din 3 litere + 3 cifre (ex: "ABC123")
    if (id.length() != 6) return false;
    for (int i = 0; i < 3; ++i) {
        if (!isalpha(id[i])) return false;
    }
    for (int i = 3; i < 6; ++i) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}