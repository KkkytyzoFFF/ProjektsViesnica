#include "hotel.h"


Hotel::Hotel(std::string name, int starsAmount, int roomAmount, int vacantRoomAmount, int roomDailyPrice)
{
	this->starsAmount = starsAmount;
	this->roomAmount = roomAmount;
	this->vacantRoomAmount = vacantRoomAmount;
	this->roomDailyPrice = roomDailyPrice;
	this->name = name;
}
