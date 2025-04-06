#include "../includes/Guest.h"
#include <cctype>

// Constructor
Guest::Guest(const std::string& name, const std::string& id)
    : name(name), id(id) {}

// Getters
const std::string& Guest::getName() const {
    return name;
}

const std::string& Guest::getId() const {
    return id;
}


// Validare ID
bool Guest::isValidId() const {
    if (id.length() != 6) return false;
    for (int i = 0; i < 3; ++i) {
        if (!isalpha(id[i])) return false;
    }
    for (int i = 3; i < 6; ++i) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

// Operators
std::ostream& operator<<(std::ostream& os, const Guest& guest) {
    os << guest.getName() << " (ID: " << guest.getId() << ")";
    return os;
}