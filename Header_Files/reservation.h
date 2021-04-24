#pragma once
#include <string>


struct Reservation
{
	Reservation(std::string ownerName, int id, std::string state, std::string hotelName, std::string dateStart, std::string dateEnd, int roomNumber, int stars);
	int stars;
	std::string dateStart;
	std::string dateEnd;
	std::string ownerName;
	std::string state;
	int roomNumber;
	std::string hotelName;
	int id;

};
