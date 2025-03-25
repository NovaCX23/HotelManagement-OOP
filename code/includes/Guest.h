#ifndef GUEST_H
#define GUEST_H
#include<string>
#include<iostream>

class Guest {
    std::string name;
    std::string id;
public:
    // Constructors
    Guest(const std::string& name, const std::string& id);

    //Getters
    std::string getName() const { return name;}
    std::string getId() const { return id;}


    bool isValidId() const;

    // Operators
    friend std::ostream& operator<<(std::ostream& os, const Guest& guest);
};


#endif //GUEST_H
