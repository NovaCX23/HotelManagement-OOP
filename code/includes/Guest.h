#ifndef GUEST_H
#define GUEST_H
#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<memory>
#include "../includes/Exceptions.h"

class Guest {

protected:
    std::string name;
    std::string id;
public:
    // Constructors
    Guest(const std::string& name, const std::string& id);

    //Getters
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getId() const;
    std::vector<std::string> getFreeBenefits() const;


    // virtuals
    virtual ~Guest() = default;
    virtual bool isValidId() const;
    virtual std::string getFullId() const;
    virtual std::string getType() const;
    virtual std::string getSummary() const;
    virtual double guestDiscount(int nights) const;
    virtual std::map<std::string, double> getAvailableBenefits() const;
    virtual std::vector<std::string> excludedBenefits() const;
    virtual bool isEligibleForBenefit(const std::string& benefitName) const;

    virtual std::shared_ptr<Guest> clone() const;

    // functions
    void displayBenefits() const;
    static std::map<std::string, double> getStandardBenefitPrices();


    // Operators
    friend std::ostream& operator<<(std::ostream& os, const Guest& guest);
};


#endif //GUEST_H
