#include <iostream>
#include <vector>
#include "hotel.h"
#include <unordered_map>
#include "reservation.h"
#include <random>
#include "helperVariables.h"
#include <iomanip>
#include <fstream>
#include <strstream>
#include <sstream>

// Students - Kirils Kutuzovs
// Grupa - D4-2
// Uzdevums - Prakses uzdevums "Projekts 'Viesnica'"
// PIKC RVT
// 24/04/2021


// Rez nr generation
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, 400);
//

//files creation
std::ofstream fileStatesWrite;
std::ofstream fileHotelsWrite;
std::ofstream fileStatesHotelsWrite;
std::ifstream fileStatesRead;
std::ifstream fileHotelsRead;
std::ifstream fileStatesHotelsRead;
std::ofstream fileReservationsWrite;
std::ifstream fileReservationsRead;

//

std::unordered_multimap<std::string, Hotel> stateHotels;
std::vector<Reservation> reservations;
std::vector < std::string> statesFromFile;
std::vector< Hotel> hotelsFromFile;
int getReservationId();
void writeStateHotels(std::string state, std::string hotel, int stars, int rooms, int vacantRooms, int price);
void printStats();
void editState(std::string stateName, std::string newName, std::string newAcronym);

void printReport(int id);
void editReservation(int id, std::string newStartDate, std::string newEndDate);
void removeReservation(int id);
void searchReservation();
void reserveHotel(std::string, std::string, std::string);
void editHotel(std::string hotelName, std::string newHotelName, int starsAmount, int roomAmount, int vacantRoomAmount, int roomDailyPrice);
std::string findState(std::string);
Hotel findHotel(std::string name);
void searchHotelByHotelName(std::string hotelName);
void searchHotelsByState(std::string, std::string);
void searchHotelsByStars(int stars);
void printStateAndHotels();
void printStates();
void printHotels();
void removeState(std::string stateName);
void addState(std::string name, std::string acronym);
void addHotel(std::string hotelName, int starsAmount, int roomAmount, int vacantRoomAmount, int roomDailyPrice);
void removeHotel(std::string hotelName);
void enterAsAdmin();
void enterAsUser();
void writeToFile(std::ofstream& file, std::string string);
bool empty(std::ifstream& file);
void getDataFromFiles();
int main()
{
	/*fileStatesWrite.open("states.txt", std::ifstream::app);
	fileHotelsWrite.open("hotels.txt", std::ifstream::app);
	fileStatesHotelsWrite.open("stateHotels.txt", std::ifstream::app);*/
	getDataFromFiles();
	//главный цикл
	while (true)
	{
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "Login" << std::endl;
		std::cout << "1. Enter as admin" << std::endl;
		std::cout << "2. Enter as user" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cin >> login;
		switch (login)
		{
		case(1):
		{
			enterAsAdmin();
			break;
		}
		case(2):
		{
			enterAsUser();
			break;
		}
		case(3):
		{
			return 0;
		}
		default:
			break;
		}
	}
	//
	/*fileStatesWrite.close();

	fileHotelsWrite.close();


	fileStatesHotelsWrite.close();*/

	return 0;
}


void editHotel(std::string hotelName, std::string newHotelName, int starsAmount, int roomAmount, int vacantRoomAmount, int roomDailyPrice)
{
	bool check = false;
	for (auto itr = hotelsFromFile.begin(); itr != hotelsFromFile.end(); ++itr)
	{
		if (itr->name == hotelName)
		{
			/*std::stringstream stream;
			fileHotelsRead.open("hotels.txt");
			stream << fileHotelsRead.rdbuf();
			std::string textFromFile = stream.str();
			std::string oldHotelName = itr->name;
			std::string oldStars = std::to_string(itr->starsAmount);
			std::string oldRooms = std::to_string(itr->roomAmount);
			std::string oldVacantRooms = std::to_string(itr->vacantRoomAmount);
			std::string oldPrice = std::to_string(itr->roomDailyPrice);
			auto pos = textFromFile.find(oldHotelName);
			auto pos2 = textFromFile.find(oldStars);
			auto pos3 = textFromFile.find(oldRooms);
			auto pos4 = textFromFile.find(oldVacantRooms);
			auto pos5 = textFromFile.find(oldPrice);
			textFromFile.replace(pos, std::string(oldHotelName).length(), newHotelName);
			textFromFile.replace(pos2, std::string(oldStars).length(), std::to_string(starsAmount));
			textFromFile.replace(pos3, std::string(oldRooms).length(), std::to_string(roomAmount));
			textFromFile.replace(pos4, std::string(oldVacantRooms).length(), std::to_string(vacantRoomAmount));
			textFromFile.replace(pos5, std::string(oldPrice).length(), std::to_string(roomDailyPrice));
			fileHotelsRead.close();
			fileHotelsWrite.open("hotels.txt");
			fileHotelsWrite << textFromFile;
			fileHotelsWrite.close();*/

			std::stringstream stream;
			fileHotelsRead.open("hotels.txt");
			stream << fileHotelsRead.rdbuf();
			std::string textFromFile = stream.str();
			std::string oldHotelName = itr->name;
			auto pos = textFromFile.find(oldHotelName);
			auto pos2 = textFromFile.find("\n", pos);
			textFromFile.erase(pos, pos2);
			textFromFile += newHotelName + "|" + std::to_string(starsAmount) + "|" + std::to_string(roomAmount) + "|" + std::to_string(vacantRoomAmount) + "|" + std::to_string(roomDailyPrice) + "\n";
			fileHotelsRead.close();
			fileHotelsWrite.open("hotels.txt");
			fileHotelsWrite << textFromFile;
			fileHotelsWrite.close();

			itr->name = newHotelName;
			itr->starsAmount = starsAmount;
			itr->roomAmount = roomAmount;
			itr->vacantRoomAmount = vacantRoomAmount;
			itr->roomDailyPrice = roomDailyPrice;
			check = true;

			std::cout << "Success!" << std::endl;
		}
	}
	if (!check)
	{
		std::cout << "Hotel dont exist" << std::endl;
	}


}
std::string findState(std::string name)
{
	for (auto itr = statesFromFile.begin(); itr != statesFromFile.end(); ++itr)
	{
		if (itr->rfind(name, 0) == 0)
		{
			return *itr;
		}
	}
	std::string emptyString = "";
	return emptyString;
}
Hotel findHotel(std::string name)
{
	for (auto itr = hotelsFromFile.begin(); itr != hotelsFromFile.end(); ++itr)
	{
		if (itr->name == name)
		{
			return *itr;
		}
	}
	Hotel hotel = Hotel();
	return hotel;
}
void searchHotelByHotelName(std::string hotelName)
{
	bool check = false;
	std::cout << "-----------------------------------------------" << std::endl;
	for (auto itr = stateHotels.begin(); itr != stateHotels.end(); ++itr)
	{
		if (itr->second.name == hotelName)
		{
			check = true;
			std::cout << "State: " << itr->first << std::endl;
			std::cout << "Hotel: " << itr->second.name << std::endl;
			std::cout << "Stars: " << itr->second.starsAmount << std::endl;
			std::cout << "Rooms: " << itr->second.roomAmount << std::endl;
			std::cout << "Available rooms: " << itr->second.vacantRoomAmount << std::endl;
			std::cout << "Price for day: " << itr->second.roomDailyPrice << std::endl;
		}
	}
	if (check == false)
	{
		std::cout << "Hotel dont exist" << std::endl;
	}

}
void searchHotelsByState(std::string stateName)
{
	std::string state = findState(stateName);
	bool check = false;
	std::pair<std::unordered_multimap<std::string, Hotel>::iterator, std::unordered_multimap<std::string, Hotel>::iterator> pairItr = stateHotels.equal_range(state);
	for (; pairItr.first != pairItr.second; ++pairItr.first)
	{
		check = true;
		std::cout << "Hotel: " << pairItr.first->second.name << std::endl;
		//std::cout << "State: " << pairItr.first->first << std::endl;
		std::cout << "Stars: " << pairItr.first->second.starsAmount << std::endl;
		std::cout << "Rooms: " << pairItr.first->second.roomAmount << std::endl;
		std::cout << "Available rooms: " << pairItr.first->second.vacantRoomAmount << std::endl;
		std::cout << "Price for day: " << pairItr.first->second.roomDailyPrice << std::endl;

	}
	if (check == false)
	{
		std::cout << "No hotels in this state" << std::endl;
	}
}
void searchHotelsByStars(int stars)
{
	bool check = false;
	for (auto itr = stateHotels.begin(); itr != stateHotels.end(); ++itr)
	{
		if (itr->second.starsAmount == starsAmountValue)
		{
			check = true;
			std::cout << "Hotel: " << itr->second.name << std::endl;
			std::cout << "State: " << itr->first << std::endl;
			std::cout << "Stars: " << itr->second.starsAmount << std::endl;
			std::cout << "Rooms: " << itr->second.roomAmount << std::endl;
			std::cout << "Available rooms: " << itr->second.vacantRoomAmount << std::endl;
			std::cout << "Price for day: " << itr->second.roomDailyPrice << std::endl;

		}
	}
	if (check == false)
	{
		std::cout << "Hotel dont exist" << std::endl;
	}
}
void printStateAndHotels()
{
	bool check = false;
	bool check2 = false;
	if (statesFromFile.empty())
	{
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "State list is empty" << std::endl;

	}
	else
	{
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "States:" << std::endl;
	}

	for (auto itr : statesFromFile)
	{
		if (itr.empty())continue;
		std::cout << itr << std::endl;
		check = true;
	}
	std::cout << std::endl;
	if (hotelsFromFile.empty())
	{
		std::cout << "Hotel list is empty" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

	}
	else
	{
		std::cout << "Hotels:" << std::endl;
	}
	for (auto itr : hotelsFromFile)
	{
		if (itr.name.empty())
			continue;
		std::cout << itr.name << std::endl;
		check2 = true;
	}
	std::cout << "-----------------------------------------------" << std::endl;

	if (check == false && statesFromFile.empty() == false)
	{
		std::cout << "State list is empty" << std::endl;
	}
	if (check2 == false && hotelsFromFile.empty() == false)
	{
		std::cout << "Hotel list is empty" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

	}
}
void printStates()
{
	bool check = false;
	if (statesFromFile.empty())
	{

		std::cout << "State list is empty" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
	}
	else
	{
		std::cout << "States:" << std::endl;
	}

	for (auto itr : statesFromFile)
	{
		if (itr.empty())
		{
			continue;
		}
		std::cout << itr << std::endl;
		check = true;
	}
	std::cout << "-----------------------------------------------" << std::endl;

	if (check == false && statesFromFile.empty() == false)
	{
		std::cout << "State list is empty" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

	}

}
void printHotels()
{
	bool check = false;
	if (hotelsFromFile.empty())
	{
		std::cout << "Hotel list is empty" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

	}
	else
	{
		std::cout << "Hotels:" << std::endl;
	}
	for (auto itr : hotelsFromFile)
	{
		if (itr.name.empty())
			continue;
		std::cout << itr.name << std::endl;
		check = true;
	}
	std::cout << "-----------------------------------------------" << std::endl;

	if (check == false && hotelsFromFile.empty() == false)
	{
		std::cout << "Hotel list is empty" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

	}
}
void removeState(std::string stateName)
{
	bool check = false;
	for (auto itr = statesFromFile.begin(); itr != statesFromFile.end(); )
	{
		if (itr->rfind(stateName, 0) == 0)
		{
			check = true;

			fileStatesRead.open("states.txt");
			std::stringstream stream;
			std::string delimitr = "\n";
			stream << fileStatesRead.rdbuf();
			std::string fileText = stream.str();
			auto pos = fileText.find(stateName);
			auto pos2 = fileText.find(delimitr, pos);
			auto pos3 = pos2 - pos;
			fileText.erase(pos, pos3);
			fileStatesRead.close();
			fileStatesWrite.open("states.txt");
			fileStatesWrite << fileText;
			fileStatesWrite.close();

			std::cout << "Success!" << std::endl;
			itr = statesFromFile.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	if (check == false)
	{
		std::cout << "State dont exist" << std::endl;
	}
}
int getReservationId()
{
	if (reservations.empty())
		return 0;
	int number = 0;
	for (auto itr : reservations)
	{
		number = itr.id;
	}
	number += 1;
	return number;
}
void writeStateHotels(std::string state, std::string hotel, int stars, int rooms, int vacantRooms, int price)
{
	fileStatesHotelsWrite.open("statesHotels.txt", std::ios::app);
	fileStatesHotelsWrite << state << "|" << hotel << "|" << stars << "|" << rooms << "|" << vacantRooms << "|" << price << "\n";
	fileStatesHotelsWrite.close();
}

void printStats()
{
	bool check = false;
	std::cout << "Enter the hotel name" << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, hotelName, '\n');
	int report = 0;
	double report2 = 0.0;
	int report3 = 0;
	std::string finalReport2 = "";
	for (auto itr = reservations.begin(); itr != reservations.end(); ++itr)
	{
		if (itr->hotelName == hotelName)
		{
			check = true;
			report++;

		}
	}
	if (check == false)
	{
		std::cout << "No data to collect stats" << std::endl;
		return;
	}
	std::ofstream file;
	file.open("Statistics\\" + hotelName + "stats.json");

	for (auto itr = stateHotels.begin(); itr != stateHotels.end(); ++itr)
	{
		if (itr->second.name == hotelName)
		{
			int sum = itr->second.roomDailyPrice;
			report3 = sum * report;
			double oneProcent = itr->second.roomAmount / 100.0;
			report2 = report / oneProcent;
			finalReport2 = std::to_string(report2);
			finalReport2 += "%";
		}
	}
	file << "{" << std::endl;
	file << "\"Reservations\":" << report << "," << std::endl;
	file << "\"HotelCapacity\":" << finalReport2 << "," << std::endl;
	file << "\"Incomes\":" << report3 << std::endl;
	file << "}" << std::endl;
	file.close();
	file.open("Statistics\\" + hotelName + "stats.csv");

	file << "Reservations;" + std::to_string(report) << std::endl;
	file << "HotelCapacity;" + finalReport2 << std::endl;
	file << "Incomes;" + std::to_string(report3) << std::endl;
	file.close();
	std::cout << "Success!" << std::endl;
}

void printReport(int id)
{
	bool check = false;

	for (auto itr = reservations.begin(); itr != reservations.end(); ++itr)
	{
		if (itr->ownerName == userName && itr->id == id)
		{
			check = true;
			std::ofstream myfile;
			std::string idText = std::to_string(itr->id);
			std::string fileName = "Reservations\\" + userName + "_" + idText + "_" + "Report.html";
			myfile.open(fileName);
			myfile << "<!DOCTYPE html><html><head></head><body>";
			myfile << "<p><span style='font-weight: bold'>" << itr->ownerName << " ID: " << itr->id << "</span><span><br>" "State: " << itr->state << "</span><span><br>" "Hotel: " << itr->hotelName << "</span><span><br>" "Date start: " << itr->dateStart << "</span><span><br>""Date end: " << itr->dateEnd << "</span><span><br>" "Room: " << itr->roomNumber << "</span><span><br>" "Stars: " << itr->stars << "</span></p>";
			std::cout << "Success!" << std::endl;
			myfile << "</body></html>";
			myfile.close();
		}
	}


	if (check == false)
	{
		std::cout << "Reservation dont exist" << std::endl;
	}
}

void editReservation(int id, std::string newStartDate, std::string newEndDate)
{
	bool check = false;
	for (auto itr = reservations.begin(); itr != reservations.end(); ++itr)
	{
		if (itr->id == id)
		{
			check = true;

			std::stringstream stream;
			fileReservationsRead.open("reservations.txt");
			stream << fileReservationsRead.rdbuf();
			std::string textFromFile = stream.str();
			auto pos = textFromFile.find(itr->dateStart);
			auto pos2 = textFromFile.find(itr->dateEnd);
			textFromFile.replace(pos, newStartDate.length(), newStartDate);
			textFromFile.replace(pos2, newEndDate.length(), newEndDate);
			fileReservationsRead.close();
			fileReservationsWrite.open("reservations.txt");
			fileReservationsWrite << textFromFile;
			fileReservationsWrite.close();

			itr->dateStart = newStartDate;
			itr->dateEnd = newEndDate;
			std::cout << "Success!" << std::endl;
		}
	}
	if (check == false)
	{
		std::cout << "Reservation dont exist" << std::endl;
	}

}
void removeReservation(int id)
{
	bool check = false;
	for (auto itr = reservations.begin(); itr != reservations.end();)
	{
		if (itr->id == id)
		{
			fileReservationsRead.open("reservations.txt");
			std::stringstream stream;
			std::string delimitr = "\n";
			stream << fileReservationsRead.rdbuf();
			std::string fileText = stream.str();
			auto pos = fileText.find(itr->ownerName);
			auto pos2 = fileText.find(delimitr, pos);
			auto pos3 = pos2 - pos;
			fileText.erase(pos, pos3);
			fileReservationsRead.close();
			fileReservationsWrite.open("reservations.txt");
			fileReservationsWrite << fileText;
			fileReservationsWrite.close();

			check = true;
			itr = reservations.erase(itr);
			std::cout << "Success!" << std::endl;
		}
		else
		{
			++itr;
		}
	}
	if (check == false)
	{
		std::cout << "Reservations dont exist" << std::endl;
	}

}
void searchReservation()
{
	bool check = false;
	for (auto itr = reservations.begin(); itr != reservations.end(); ++itr)
	{
		if (itr->ownerName == userName)
		{
			check = true;
			std::cout << "Owner: " << itr->ownerName << std::endl;
			std::cout << "ID: " << itr->id << std::endl;
			std::cout << "State: " << itr->state << std::endl;
			std::cout << "Hotel: " << itr->hotelName << std::endl;
			std::cout << "Start date: " << itr->dateStart << std::endl;
			std::cout << "End date: " << itr->dateEnd << std::endl;
			std::cout << "Room: " << itr->roomNumber << std::endl;
			std::cout << "Stars: " << itr->stars << std::endl;
		}
	}

	if (check == false)
		std::cout << "Reservations list is empty" << std::endl;

}
void reserveHotel(std::string hotelName, std::string dateStart, std::string dateEnd)
{
	bool check = false;
	int randomNumber = dist(gen);
	for (auto itr = stateHotels.begin(); itr != stateHotels.end(); ++itr)
	{
		if (itr->second.name == hotelName)
		{
			check = true;

			if (itr->second.vacantRoomAmount > 0)
			{


				std::stringstream stream;
				fileStatesHotelsRead.open("statesHotels.txt");
				stream << fileStatesHotelsRead.rdbuf();
				std::string textFromFile = stream.str();
				std::string roomAmountText = std::to_string(itr->second.roomAmount);
				std::string vacantRoomAmountText = std::to_string(itr->second.vacantRoomAmount);
				auto pos = textFromFile.find(roomAmountText);
				auto pos2 = textFromFile.find(vacantRoomAmountText, pos + 1);
				int vacantRoomAmount = itr->second.vacantRoomAmount - 1;

				textFromFile.replace(pos2, vacantRoomAmountText.length(), std::to_string(vacantRoomAmount));
				fileStatesHotelsRead.close();
				fileStatesHotelsWrite.open("statesHotels.txt");
				fileStatesHotelsWrite << textFromFile << std::endl;
				fileStatesHotelsWrite.close();

				itr->second.vacantRoomAmount--;
				int number = getReservationId();
				Reservation reservation = Reservation(userName, number, itr->first, itr->second.name, startDate, endDate, randomNumber, itr->second.starsAmount);

				fileReservationsWrite.open("reservations.txt", std::ios::app);
				fileReservationsWrite << reservation.ownerName << "|" << reservation.id << "|" << reservation.state << "|" << reservation.hotelName << "|" << reservation.dateStart << "|" << reservation.dateEnd << "|" << reservation.roomNumber << "|" << reservation.stars << "\n";
				fileReservationsWrite.close();
				reservations.push_back(reservation);
				std::cout << "Success!" << std::endl;
			}
			else
			{
				std::cout << "Not enough room to reserve" << std::endl;
			}
		}
	}
	if (check == false)
	{
		std::cout << "Hotel dont exist" << std::endl;
	}
}
void editState(std::string stateName, std::string newName, std::string newAcronym)
{
	bool check = false;
	for (auto itr = statesFromFile.begin(); itr != statesFromFile.end(); ++itr)
	{
		if (itr->rfind(stateName, 0) == 0)
		{
			check = true;
			std::stringstream stream;
			fileStatesRead.open("states.txt");
			stream << fileStatesRead.rdbuf();
			std::string textFromFile = stream.str();
			std::string oldStateName = findState(stateName);
			auto pos = textFromFile.find(oldStateName);
			textFromFile.replace(pos, std::string(oldStateName).length(), newName + " (" + newAcronym + ")");
			fileStatesRead.close();
			fileStatesWrite.open("states.txt");
			fileStatesWrite << textFromFile;
			fileStatesWrite.close();

			*itr = newName + " (" + newAcronym + ")";
			std::cout << "Success!" << std::endl;
		}
	}
	if (check == false)
	{
		std::cout << "State dont exist" << std::endl;
	}
}
void addState(std::string name, std::string acronym)
{
	for (auto itr = statesFromFile.begin(); itr != statesFromFile.end(); ++itr)
	{
		if (itr->rfind(name, 0) == 0)
		{
			std::cout << "State already exist" << std::endl;
			return;
		}
	}
	statesFromFile.push_back(name + " (" + acronym + ")");
	fileStatesWrite.open("states.txt", std::ios::app);
	fileStatesWrite << name + " (" + acronym + ")\n";
	fileStatesWrite.close();
	std::cout << "Success!" << std::endl;

}
void addHotel(std::string hotelName, int starsAmount, int roomAmount, int vacantRoomAmount, int roomDailyPrice)
{
	for (auto itr = hotelsFromFile.begin(); itr != hotelsFromFile.end(); ++itr)
	{
		if (itr->name == hotelName)
		{
			std::cout << "Hotel already exist" << std::endl;
			return;
		}
	}
	Hotel hotel = Hotel(hotelName, starsAmount, roomAmount, vacantRoomAmount, roomDailyPrice);
	hotelsFromFile.push_back(hotel);
	fileHotelsWrite.open("hotels.txt", std::ios::app);
	fileHotelsWrite << hotel.name << "|" << hotel.starsAmount << "|" << hotel.roomAmount << "|" << hotel.vacantRoomAmount << "|" << hotel.roomDailyPrice << "\n";
	fileHotelsWrite.close();
	std::cout << "Success!" << std::endl;
}
void removeHotel(std::string hotelName)
{
	bool check = false;
	for (auto itr = hotelsFromFile.begin(); itr != hotelsFromFile.end(); )
	{
		if (itr->name == hotelName)
		{
			check = true;
			itr = hotelsFromFile.erase(itr);
			//
			fileHotelsRead.open("hotels.txt");
			std::stringstream stream;
			std::string delimitr = "\n";
			stream << fileHotelsRead.rdbuf();
			std::string fileText = stream.str();
			auto pos = fileText.find(hotelName);
			auto pos2 = fileText.find(delimitr, pos);
			auto pos3 = pos2 - pos;
			fileText.erase(pos, pos3);
			fileHotelsRead.close();
			fileHotelsWrite.open("hotels.txt");
			fileHotelsWrite << fileText;
			fileHotelsWrite.close();

			std::cout << "Success!" << std::endl;
		}
		else
		{
			++itr;
		}
	}
	if (check == false)
	{
		std::cout << "Hotel dont exist" << std::endl;
	}

}

void enterAsAdmin()
{
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "Enter your name" << std::endl;
	std::cout << "Enter your password" << std::endl;
	std::cout << "Name: admin  Password: 0123" << std::endl;
	std::cout << "--------------- --------------------------------" << std::endl;
	std::cin >> adminName;
	std::cin >> password;
	while (adminName != "admin" && password != "0123")
	{
		std::cout << "Either your name or password are wrong. Try again." << std::endl;
		std::cin >> adminName;
		std::cin >> password;
	}
	while (true)
	{
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "Choose operation: " << std::endl;
		std::cout << "1. Add state" << std::endl;
		std::cout << "2. Remove state" << std::endl;
		std::cout << "3. Edit state" << std::endl;
		std::cout << "4. Add hotel" << std::endl;
		std::cout << "5. Remove hotel" << std::endl;
		std::cout << "6. Edit hotel" << std::endl;
		std::cout << "7. Link hotel to state" << std::endl;
		std::cout << "8. Print hotels and states to link" << std::endl;
		std::cout << "9. Print hotels and states" << std::endl;
		std::cout << "10. Print stats" << std::endl;
		std::cout << "11. Log out" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cin >> operation;
		switch (operation)
		{
		case(1):
		{
			printStates();
			std::cout << std::endl;
			std::cout << "Enter the state name " << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, stateName, '\n');
			if (stateName == "q")
				break;
			std::cout << "Enter the acronym" << std::endl;
			std::getline(std::cin, acronym, '\n');
			addState(stateName, acronym);
			break;
		}
		case(2):
		{
			printStates();
			std::cout << std::endl;
			std::cout << "Enter the state name" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, stateName, '\n');
			if (stateName == "q")
				break;
			removeState(stateName);
			break;
		}
		case(3):
		{
			printStates();
			std::cout << std::endl;

			std::cout << "Enter the state name to edit" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, stateName, '\n');
			if (stateName == "q")
				break;
			while (findState(stateName).empty())
			{
				std::cout << "State dont exist. Try again" << std::endl;
				std::getline(std::cin, stateName, '\n');
			}
			std::cout << "Enter the new state name" << std::endl;
			std::getline(std::cin, newStateName, '\n');
			std::cout << "Enter the new acronym" << std::endl;
			std::cin >> newAcronym;
			editState(stateName, newStateName, newAcronym);
			break;
		}
		case(4):
		{
			printHotels();
			std::cout << std::endl;

			std::cout << "Enter the hotel name" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, hotelName, '\n');
			if (hotelName == "q")
				break;
			std::cout << "Enter the stars:" << std::endl;
			std::cin >> starsAmountValue;
			while (starsAmountValue > 8)
			{
				std::cout << "Stars value can not exceed 8. Try again" << std::endl;
				std::cin >> starsAmountValue;
			}
			std::cout << "Enter the amount of rooms" << std::endl;
			std::cin >> roomAmountValue;
			std::cout << "Enter the amount of available rooms" << std::endl;
			std::cin >> vacantRoomAmountValue;
			while (vacantRoomAmountValue > roomAmountValue)
			{
				std::cout << "Vacant rooms can not exceed total rooms. Try again" << std::endl;
				std::cin >> vacantRoomAmountValue;
			}
			std::cout << "Enter the daily price for the room" << std::endl;
			std::cin >> roomDailyPriceValue;
			addHotel(hotelName, starsAmountValue, roomAmountValue, vacantRoomAmountValue, roomDailyPriceValue);
			break;
		}
		case(5):
		{
			printHotels();
			std::cout << std::endl;

			std::cout << "Enter the hotel name" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, hotelName, '\n');
			if (hotelName == "q")
				break;
			removeHotel(hotelName);
			break;
		}
		case(6):
		{
			printHotels();
			std::cout << std::endl;
			std::cout << "Enter the hotel name to edit" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, hotelName, '\n');
			if (hotelName == "q")
				break;
			while (findHotel(hotelName).name.empty())
			{
				std::cout << "Hotel dont exist. Try again" << std::endl;
				std::getline(std::cin, hotelName, '\n');
			}
			std::cout << "Enter the new hotel name" << std::endl;
			std::getline(std::cin, newHotelName, '\n');
			std::cout << "Enter the stars" << std::endl;
			std::cin >> starsAmountValue;
			while (starsAmountValue > 8)
			{
				std::cout << "Stars value can not exceed 8. Try again" << std::endl;
				std::cin >> starsAmountValue;
			}
			std::cout << "Enter the amount of rooms" << std::endl;
			std::cin >> roomAmountValue;

			std::cout << "Enter the amount of available rooms" << std::endl;
			std::cin >> vacantRoomAmountValue;
			while (vacantRoomAmountValue > roomAmountValue)
			{
				std::cout << "Vacant rooms can not exceed total rooms. Try again" << std::endl;
				std::cin >> vacantRoomAmountValue;
			}
			std::cout << "Enter the daily price for the room" << std::endl;
			std::cin >> roomDailyPriceValue;
			editHotel(hotelName, newHotelName, starsAmountValue, roomAmountValue, vacantRoomAmountValue, roomDailyPriceValue);
			break;
		}
		case(7):
		{
			printStateAndHotels();
			
			//
			if (stateHotels.size() != 0)
			{
				std::cout << "States and hotels:" << std::endl;
				for (auto itr : stateHotels)
				{
					std::cout << itr.first << "->" << itr.second.name << std::endl;
				}
			}
			//

			std::cout << "-----------------------------------------------" << std::endl;
			std::cout << "Enter the hotel" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, hotelName, '\n');
			if (hotelName == "q")
				break;
			Hotel hotel = findHotel(hotelName);
			if (hotel.name == "")
			{
				std::cout << "Hotel dont exist. Try again." << std::endl;
				break;
			}
			std::cout << "Enter the state name" << std::endl;
			std::getline(std::cin, stateName, '\n');
			std::string state = findState(stateName);

			if (state == "")
			{
				std::cout << "State dont exist. Try again." << std::endl;
				break;
			}
			writeStateHotels(state, hotel.name, hotel.starsAmount, hotel.roomAmount, hotel.vacantRoomAmount, hotel.roomDailyPrice);
			stateHotels.insert(std::unordered_multimap<std::string, Hotel>::value_type(state, hotel));
			std::cout << "Success!" << std::endl;
			break;
		}
		case(8):
		{
			printStateAndHotels();
			break;
		}
		case(9):
		{
			if (stateHotels.size() == 0)
			{
				std::cout << "List is empty" << std::endl;
				break;
			}
			std::cout << "States and hotels:" << std::endl;
			for (auto itr : stateHotels)
			{
				std::cout << itr.first << "->" << itr.second.name << std::endl;
			}
			break;
		}
		case(10):
		{
			printStats();
		}
		case(11):
			return;
		default:
			break;
		}

	}
}
void enterAsUser()
{
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "Enter your name" << std::endl;
	std::cin >> userName;
	while (true)
	{
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "1. Search hotels by name" << std::endl;
		std::cout << "2. Search hotels by state" << std::endl;
		std::cout << "3. Search hotels by stars" << std::endl;
		std::cout << "4. Reserve a room" << std::endl;
		std::cout << "5. Search reservations" << std::endl;
		std::cout << "6. Remove reservation" << std::endl;
		std::cout << "7. Edit reservation" << std::endl;
		std::cout << "8. Print out reservation" << std::endl;
		std::cout << "9. Log out" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cin >> operation2;
		switch (operation2)
		{
		case(1):
		{
			std::cout << "Enter the hotel name" << std::endl;
			std::cout << "Press q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, hotelName, '\n');
			if (hotelName == "q")
				break;
			searchHotelByHotelName(hotelName);
			break;
		}
		case(2):
		{
			std::cout << "Enter the state" << std::endl;
			std::cout << "Press q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, stateName, '\n');
			if (stateName == "q")
				break;
			searchHotelsByState(stateName);
			break;
		}
		case(3):
		{
			std::cout << "Enter the stars" << std::endl;
			std::cout << "Press q to cancel operation" << std::endl;
			std::string starAmountValueText;
			std::cin >> starAmountValueText;
			if (starAmountValueText == "q")
			{
				break;
			}
			starsAmountValue = std::stoi(starAmountValueText);
			searchHotelsByStars(starsAmountValue);
			break;
		}
		case(4):
		{
			long parsedStartDate = 0;
			long parsedStartDate2 = 0;
			long parsedStartDate3 = 0;
			long parsedEndDate = 0;
			long parsedEndDate2 = 0;
			long parsedEndDate3 = 0;
			std::cout << "Enter the hotel name" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, hotelName, '\n');
			if (hotelName == "q")
			{
				break;
			}
			while (findHotel(hotelName).name.empty())
			{
				std::cout << "Hotel dont exist. Try again" << std::endl;
				std::getline(std::cin, hotelName, '\n');
			}
			std::cout << "Enter the start date. Format 01/02/2021" << std::endl;
			std::cin >> startDate;
			std::string startDateCopy = startDate;
			auto pos = startDateCopy.find("/");
			std::string startDateSubstring;
			std::string startDateSubstring2;
			std::string startDateSubstring3;
			startDateSubstring = startDateCopy.substr(0, pos);
			startDateCopy.erase(0, pos + 1);
			pos = startDateCopy.find("/");
			startDateSubstring2 = startDateCopy.substr(0, pos);
			startDateCopy.erase(0, pos + 1);
			pos = startDateCopy.find("/");
			startDateSubstring3 = startDateCopy.substr(0, pos);

			if (startDateSubstring[0] == '0')
			{
				startDateSubstring = startDateSubstring.substr(1);
			}
			if (startDateSubstring2[0] == '0')
			{
				startDateSubstring2 = startDateSubstring2.substr(1);
			}
			parsedStartDate = std::stoi(startDateSubstring);
			parsedStartDate2 = std::stoi(startDateSubstring2);
			parsedStartDate3 = std::stoi(startDateSubstring3);
			while (parsedStartDate > 31 || parsedStartDate2 > 12)
			{
				std::cout << "Either day or month are incorrect.Try again." << std::endl;
				std::cin >> startDate;
				startDateCopy = startDate;
				pos = startDateCopy.find("/");
				startDateSubstring = startDateCopy.substr(0, pos);
				startDateCopy.erase(0, pos + 1);
				pos = startDateCopy.find("/");
				startDateSubstring2 = startDateCopy.substr(0, pos);
				startDateCopy.erase(0, pos + 1);
				pos = startDateCopy.find("/");
				startDateSubstring3 = startDateCopy.substr(0, pos);

				if (startDateSubstring[0] == '0')
				{
					startDateSubstring = startDateSubstring.substr(1);
				}
				if (startDateSubstring2[0] == '0')
				{
					startDateSubstring2 = startDateSubstring2.substr(1);
				}
				parsedStartDate = std::stoi(startDateSubstring);
				parsedStartDate2 = std::stoi(startDateSubstring2);
				parsedStartDate3 = std::stoi(startDateSubstring3);

			}
			std::cout << "Enter the end date. Format 01/02/2021" << std::endl;
			std::cin >> endDate;
			std::string endDateCopy = endDate;
			auto pos2 = endDateCopy.find("/");
			std::string endDateSubstring;
			std::string endDateSubstring2;
			std::string endDateSubstring3;
			endDateSubstring = endDateCopy.substr(0, pos2);
			endDateCopy.erase(0, pos2 + 1);
			pos2 = endDateCopy.find("/");
			endDateSubstring2 = endDateCopy.substr(0, pos2);
			endDateCopy.erase(0, pos2 + 1);
			pos2 = endDateCopy.find("/");
			endDateSubstring3 = endDateCopy.substr(0, pos2);
			if (endDateSubstring[0] == '0')
			{
				endDateSubstring = endDateSubstring.substr(1);
			}
			if (endDateSubstring2[0] == '0')
			{
				endDateSubstring2 = endDateSubstring2.substr(1);
			}
			parsedEndDate = std::stoi(endDateSubstring);
			parsedEndDate2 = std::stoi(endDateSubstring2);
			parsedEndDate3 = std::stoi(endDateSubstring3);
			while (parsedEndDate > 31 || parsedEndDate2 > 12)
			{
				std::cout << "Either day or month are incorrect.Try again." << std::endl;
				std::cin >> endDate;
				endDateCopy = endDate;
				pos2 = endDateCopy.find("/");
				endDateSubstring = endDateCopy.substr(0, pos2);
				endDateCopy.erase(0, pos2 + 1);
				pos2 = endDateCopy.find("/");
				endDateSubstring2 = endDateCopy.substr(0, pos2);
				endDateCopy.erase(0, pos2 + 1);
				pos2 = endDateCopy.find("/");
				endDateSubstring3 = endDateCopy.substr(0, pos2);
				if (endDateSubstring[0] == '0')
				{
					endDateSubstring = endDateSubstring.substr(1);
				}
				if (endDateSubstring2[0] == '0')
				{
					endDateSubstring2 = endDateSubstring2.substr(1);
				}
				parsedEndDate = std::stoi(endDateSubstring);
				parsedEndDate2 = std::stoi(endDateSubstring2);
				parsedEndDate3 = std::stoi(endDateSubstring3);
			}
			while ((parsedStartDate3 * 10000 + parsedStartDate2 * 100 + parsedStartDate) > (parsedEndDate3 * 10000 + parsedEndDate2 * 100 + parsedEndDate))
			{
				std::cout << "End date set earlier than start date" << std::endl;
				std::cin >> endDate;
				endDateCopy = endDate;
				pos2 = endDateCopy.find("/");
				endDateSubstring = endDateCopy.substr(0, pos2);
				endDateCopy.erase(0, pos2 + 1);
				pos2 = endDateCopy.find("/");
				endDateSubstring2 = endDateCopy.substr(0, pos2);
				endDateCopy.erase(0, pos2 + 1);
				pos2 = endDateCopy.find("/");
				endDateSubstring3 = endDateCopy.substr(0, pos2);
				if (endDateSubstring[0] == '0')
				{
					endDateSubstring = endDateSubstring.substr(1);
				}
				if (endDateSubstring2[0] == '0')
				{
					endDateSubstring2 = endDateSubstring2.substr(1);
				}
				parsedEndDate = std::stoi(endDateSubstring);
				parsedEndDate2 = std::stoi(endDateSubstring2);
				parsedEndDate3 = std::stoi(endDateSubstring3);
			}
			reserveHotel(hotelName, startDate, endDate);
			break;
		}
		case(5):
		{
			searchReservation();
			break;
		}
		case(6):
		{
			std::cout << "Enter reservation ID" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::string idText;
			std::cin >> idText;
			if (idText == "q")
				break;
			id = std::stoi(idText);
			removeReservation(id);
			break;
		}
		case(7):
		{
			long parsedStartDate = 0;
			long parsedStartDate2 = 0;
			long parsedStartDate3 = 0;
			long parsedEndDate = 0;
			long parsedEndDate2 = 0;
			long parsedEndDate3 = 0;
			std::cout << "Enter reservation ID" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::string idText;
			std::cin >> idText;
			if (idText == "q")
				break;
			id = std::stoi(idText);
			std::cout << "Enter the new start date" << std::endl;
			std::cin >> newStartDate;
			std::string startDateCopy = newStartDate;
			auto pos = startDateCopy.find("/");
			std::string startDateSubstring;
			std::string startDateSubstring2;
			std::string startDateSubstring3;
			startDateSubstring = startDateCopy.substr(0, pos);
			startDateCopy.erase(0, pos + 1);
			pos = startDateCopy.find("/");
			startDateSubstring2 = startDateCopy.substr(0, pos);
			startDateCopy.erase(0, pos + 1);
			pos = startDateCopy.find("/");
			startDateSubstring3 = startDateCopy.substr(0, pos);

			if (startDateSubstring[0] == '0')
			{
				startDateSubstring = startDateSubstring.substr(1);
			}
			if (startDateSubstring2[0] == '0')
			{
				startDateSubstring2 = startDateSubstring2.substr(1);
			}
			parsedStartDate = std::stoi(startDateSubstring);
			parsedStartDate2 = std::stoi(startDateSubstring2);
			parsedStartDate3 = std::stoi(startDateSubstring3);
			while (parsedStartDate > 31 || parsedStartDate2 > 12)
			{
				std::cout << "Either day or month are incorrect.Try again." << std::endl;
				std::cin >> newStartDate;
				startDateCopy = newStartDate;
				pos = startDateCopy.find("/");
				startDateSubstring = startDateCopy.substr(0, pos);
				startDateCopy.erase(0, pos + 1);
				pos = startDateCopy.find("/");
				startDateSubstring2 = startDateCopy.substr(0, pos);
				startDateCopy.erase(0, pos + 1);
				pos = startDateCopy.find("/");
				startDateSubstring3 = startDateCopy.substr(0, pos);

				if (startDateSubstring[0] == '0')
				{
					startDateSubstring = startDateSubstring.substr(1);
				}
				if (startDateSubstring2[0] == '0')
				{
					startDateSubstring2 = startDateSubstring2.substr(1);
				}
				parsedStartDate = std::stoi(startDateSubstring);
				parsedStartDate2 = std::stoi(startDateSubstring2);
				parsedStartDate3 = std::stoi(startDateSubstring3);

			}
			std::cout << "Enter the new end date" << std::endl;
			std::cin >> newEndDate;

			std::string endDateCopy = newEndDate;
			auto pos2 = endDateCopy.find("/");
			std::string endDateSubstring;
			std::string endDateSubstring2;
			std::string endDateSubstring3;
			endDateSubstring = endDateCopy.substr(0, pos2);
			endDateCopy.erase(0, pos2 + 1);
			pos2 = endDateCopy.find("/");
			endDateSubstring2 = endDateCopy.substr(0, pos2);
			endDateCopy.erase(0, pos2 + 1);
			pos2 = endDateCopy.find("/");
			endDateSubstring3 = endDateCopy.substr(0, pos2);
			if (endDateSubstring[0] == '0')
			{
				endDateSubstring = endDateSubstring.substr(1);
			}
			if (endDateSubstring2[0] == '0')
			{
				endDateSubstring2 = endDateSubstring2.substr(1);
			}
			parsedEndDate = std::stoi(endDateSubstring);
			parsedEndDate2 = std::stoi(endDateSubstring2);
			parsedEndDate3 = std::stoi(endDateSubstring3);
			while (parsedEndDate > 31 || parsedEndDate2 > 12)
			{
				std::cout << "Either day or month are incorrect.Try again." << std::endl;
				std::cin >> newEndDate;
				endDateCopy = newEndDate;
				pos2 = endDateCopy.find("/");
				endDateSubstring = endDateCopy.substr(0, pos2);
				endDateCopy.erase(0, pos2 + 1);
				pos2 = endDateCopy.find("/");
				endDateSubstring2 = endDateCopy.substr(0, pos2);
				endDateCopy.erase(0, pos2 + 1);
				pos2 = endDateCopy.find("/");
				endDateSubstring3 = endDateCopy.substr(0, pos2);
				if (endDateSubstring[0] == '0')
				{
					endDateSubstring = endDateSubstring.substr(1);
				}
				if (endDateSubstring2[0] == '0')
				{
					endDateSubstring2 = endDateSubstring2.substr(1);
				}
				parsedEndDate = std::stoi(endDateSubstring);
				parsedEndDate2 = std::stoi(endDateSubstring2);
				parsedEndDate3 = std::stoi(endDateSubstring3);
			}
			while ((parsedStartDate3 * 10000 + parsedStartDate2 * 100 + parsedStartDate) > (parsedEndDate3 * 10000 + parsedEndDate2 * 100 + parsedEndDate))
			{
				std::cout << "End date set earlier than start date" << std::endl;
				std::cin >> newEndDate;
				endDateCopy = newEndDate;
				pos2 = endDateCopy.find("/");
				endDateSubstring = endDateCopy.substr(0, pos2);
				endDateCopy.erase(0, pos2 + 1);
				pos2 = endDateCopy.find("/");
				endDateSubstring2 = endDateCopy.substr(0, pos2);
				endDateCopy.erase(0, pos2 + 1);
				pos2 = endDateCopy.find("/");
				endDateSubstring3 = endDateCopy.substr(0, pos2);
				if (endDateSubstring[0] == '0')
				{
					endDateSubstring = endDateSubstring.substr(1);
				}
				if (endDateSubstring2[0] == '0')
				{
					endDateSubstring2 = endDateSubstring2.substr(1);
				}
				parsedEndDate = std::stoi(endDateSubstring);
				parsedEndDate2 = std::stoi(endDateSubstring2);
				parsedEndDate3 = std::stoi(endDateSubstring3);
			}

			editReservation(id, newStartDate, newEndDate);
			break;
		}
		case(8):
		{
			std::string idText;
			std::cout << "Enter reservation ID" << std::endl;
			std::cout << "Type q to cancel operation" << std::endl;
			std::cin >> idText;
			if (idText == "q")
				break;
			id = std::stoi(idText);

			printReport(id);
			break;
		}
		case(9):
		{
			return;
		}
		default:
			break;
		}
	}
}


void writeToFile(std::ofstream& file, std::string string)
{
	file << string;
}

bool empty(std::ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

void getDataFromFiles()
{
	fileReservationsRead.open("reservations.txt");
	if (fileReservationsRead.is_open())
	{
		std::string line;
		while (std::getline(fileReservationsRead, line))
		{
			std::string delimitr = "|";
			auto pos = line.find(delimitr);
			std::string lineSubstring = line.substr(0, pos);
			line.erase(0, pos + delimitr.length());
			if (lineSubstring.empty())
				continue;
			pos = line.find(delimitr);
			int lineSubstring2 = std::stoi(line.substr(0, pos));
			line.erase(0, pos + delimitr.length());
			pos = line.find(delimitr);
			std::string lineSubstring3 = line.substr(0, pos);
			line.erase(0, pos + delimitr.length());
			pos = line.find(delimitr);
			std::string lineSubstring4 = line.substr(0, pos);
			line.erase(0, pos + delimitr.length());
			pos = line.find(delimitr);
			std::string lineSubstring5 = line.substr(0, pos);
			line.erase(0, pos + delimitr.length());
			std::string lineSubstring6 = line.substr(0, pos);
			line.erase(0, pos + delimitr.length());
			pos = line.find(delimitr);
			int lineSubstring7 = std::stoi(line.substr(0, pos));
			line.erase(0, pos + delimitr.length());
			pos = line.find(delimitr);
			int lineSubstring8 = std::stoi(line.substr(0, pos));

			Reservation reservationInstance = Reservation(lineSubstring, lineSubstring2, lineSubstring3, lineSubstring4, lineSubstring5, lineSubstring6, lineSubstring7, lineSubstring8);

			reservations.push_back(reservationInstance);
		}

	}
	fileReservationsRead.close();
	fileStatesRead.open("states.txt");
	if (fileStatesRead.is_open())
	{
		std::string line;
		while (std::getline(fileStatesRead, line))
		{
			statesFromFile.push_back(line);
		}

	}
	fileStatesRead.close();
	fileHotelsRead.open("hotels.txt");
	if (fileHotelsRead.is_open())
	{
		std::string line;
		while (std::getline(fileHotelsRead, line))
		{
			std::string delimitr = "|";
			auto pos = line.find(delimitr);
			std::string lineSubstring = line.substr(0, pos);
			line.erase(0, pos + delimitr.length());
			if (lineSubstring.empty())
				continue;
			pos = line.find(delimitr);
			int lineSubstring2 = std::stoi(line.substr(0, pos));
			line.erase(0, pos + delimitr.length());
			pos = line.find(delimitr);
			int lineSubstring3 = std::stoi(line.substr(0, pos));
			line.erase(0, pos + delimitr.length());
			pos = line.find(delimitr);
			int lineSubstring4 = std::stoi(line.substr(0, pos));
			line.erase(0, pos + delimitr.length());
			pos = line.find(delimitr);
			int lineSubstring5 = std::stoi(line.substr(0, pos));
			Hotel hotelInstance = Hotel(lineSubstring, lineSubstring2, lineSubstring3, lineSubstring4, lineSubstring5);

			hotelsFromFile.push_back(hotelInstance);
		}

	}
	fileHotelsRead.close();
	fileStatesHotelsRead.open("statesHotels.txt");
	if (fileStatesHotelsRead.is_open())
	{
		if (!empty(fileStatesHotelsRead))
		{
			std::string line;
			while (std::getline(fileStatesHotelsRead, line))
			{
				auto pos = 0;
				std::string word;
				std::string delimitr = "|";
				pos = line.find(delimitr);
				std::string lineSubstring = line.substr(0, pos);
				if (lineSubstring.empty())
					continue;
				line.erase(0, pos + delimitr.length());
				pos = line.find(delimitr);
				std::string lineSubstring2 = line.substr(0, pos);
				line.erase(0, pos + delimitr.length());
				pos = line.find(delimitr);
				int lineSubstring3 = std::stoi(line.substr(0, pos));
				line.erase(0, pos + delimitr.length());
				pos = line.find(delimitr);
				int lineSubstring4 = std::stoi(line.substr(0, pos));
				line.erase(0, pos + delimitr.length());
				pos = line.find(delimitr);
				int lineSubstring5 = std::stoi(line.substr(0, pos));
				line.erase(0, pos + delimitr.length());
				pos = line.find(delimitr);
				int lineSubstring6 = std::stoi(line.substr(0, pos));
				Hotel hotel = Hotel(lineSubstring2, lineSubstring3, lineSubstring4, lineSubstring5, lineSubstring6);
				stateHotels.insert(std::unordered_multimap<std::string, Hotel>::value_type(lineSubstring, hotel));
			}
		}
	}
	fileStatesHotelsRead.close();
}
