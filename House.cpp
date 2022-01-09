// Anjal Parikh 1001660508
// House.cpp

#include<iostream>

#include "House.h"
		
House::House(std::string name_house, std::map<int, std::string> rankMap)
:houseName{name_house}, CandyRankingMap{rankMap}
{
	
};
	
std::string House::ringDoorbell(std::ostringstream &strstream)
{
	int candyNum = 0;
	
	door.lock();
	
	strstream<< "*";
	
	candyNum = rand() %CandyRankingMap.size() + 1;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	
	door.unlock();
	std::string value = CandyRankingMap[candyNum];
	
	return value;
}