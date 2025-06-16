#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class Exceptions : public std::exception {
protected:
	std::string message;
public:
	explicit Exceptions(const std::string& msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class InvalidGuestIdException : public Exceptions {
public:
	explicit InvalidGuestIdException(const std::string& id)
		: Exceptions("Invalid Guest ID: " + id) {}
};

class RoomNotFoundException : public Exceptions {
public:
	explicit RoomNotFoundException(int roomNumber)
		: Exceptions("Room not found: " + std::to_string(roomNumber)) {}
};

class BookingConflictException : public Exceptions {
public:
	BookingConflictException()
		: Exceptions("Booking conflict: overlapping reservation exists.") {}
};

class InvalidDateFormatException : public Exceptions {
public:
	explicit InvalidDateFormatException(const std::string& date)
		: Exceptions("Invalid date format: " + date + ". Use YYYY-MM-DD.") {}
};

class InvalidNightsException : public Exceptions {
public:
	explicit InvalidNightsException(int nights)
		: Exceptions("Invalid number of nights: " + std::to_string(nights)) {}
};


#endif
