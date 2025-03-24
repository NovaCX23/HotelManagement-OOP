#ifndef GUEST_H
#define GUEST_H
#include<string>

class Guest {
    std::string name;
    std::string id;
public:
    Guest(const std::string& name, const std::string& id);
    std::string getName() const;
    std::string getId() const;

    bool isValidId() const;
};


#endif //GUEST_H
