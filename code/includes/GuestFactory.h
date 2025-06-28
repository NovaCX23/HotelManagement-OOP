#ifndef GUESTFACTORY_H
#define GUESTFACTORY_H

#include "Guest.h"
#include <memory>
#include <string>

class GuestFactory {
public:
	static std::shared_ptr<Guest> createFromInput(const std::string& name, const std::string& id);
	static std::shared_ptr<Guest> createFromCSV(const std::string& name, const std::string& fullId);

	static std::vector<std::string> split(const std::string& s, char delim);
};

#endif //GUESTFACTORY_H
