#include "Reservation.h"


Reservation::Reservation(std::string ownerName, int id, std::string state, std::string hotelName, std::string dateStart, std::string dateEnd, int roomNumber, int stars)
{
	this->id = id;
	this->ownerName = ownerName;
	this->state = state;
	this->hotelName = hotelName;
	this->dateStart = dateStart;
	this->dateEnd = dateEnd;
	this->roomNumber = roomNumber;
	this->stars = stars;
}
