#include "../includes/GuestFactory.h"
#include "../includes/VIPGuest.h"
#include "../includes/CorporateGuest.h"
#include "../includes/EventGuest.h"
#include "../includes/InfluencerGuest.h"
#include "../includes/Exceptions.h"


std::vector<std::string> GuestFactory::split(const std::string& s, char delim) {
	std::vector<std::string> out;
	std::string temp;
	for (char c : s) {
		if (c == delim) { out.push_back(temp); temp.clear(); }
		else temp += c;
	}
	out.push_back(temp);
	return out;
}

std::shared_ptr<Guest> GuestFactory::createFromInput(const std::string& name, const std::string& id) {
	if (id.starts_with("VIP"))
		return VIPGuest::createFromInput(name, id);
	else if (id.starts_with("COR"))
		return CorporateGuest::createFromInput(name, id);
	else if (id.starts_with("EVT"))
		return EventGuest::createFromInput(name, id);
	else if (id.starts_with("INF"))
		return InfluencerGuest::createFromInput(name, id);
	else {
		auto guest = std::make_shared<Guest>(name, id);
		if (!guest->isValidId())
			throw InvalidGuestIdException(id);
		return guest;
	}
}

std::shared_ptr<Guest> GuestFactory::createFromCSV(const std::string& name, const std::string& fullId) {
	auto parts = split(fullId, '|');
	std::string raw_id = parts[0];

	if (raw_id.rfind("VIP", 0) == 0)
		return VIPGuest::createFromCSV(name, fullId);
	else if (raw_id.rfind("COR", 0) == 0)
		return CorporateGuest::createFromCSV(name, fullId);
	else if (raw_id.rfind("EVT", 0) == 0)
		return EventGuest::createFromCSV(name, fullId);
	else if (raw_id.rfind("INF", 0) == 0)
		return InfluencerGuest::createFromCSV(name, fullId);
	else {
		auto guest = std::make_shared<Guest>(name, raw_id);
		if (!guest->isValidId())
			throw InvalidGuestIdException(raw_id);
		return guest;
	}
}

