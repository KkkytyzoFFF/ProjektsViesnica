#pragma once
#include <string>


struct Hotel
{
	Hotel()
	{
		name = "";
		starsAmount = 0;
		roomAmount = 0;
		vacantRoomAmount = 0;
		roomDailyPrice = 0;
	}
	Hotel(std::string name, int starsAmount, int roomAmount, int vacantRoomAmount, int roomDailyPrice);
	int starsAmount;
	int roomAmount;
	int vacantRoomAmount;
	int roomDailyPrice;
	std::string name;
};