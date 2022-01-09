//Anjal Parikh 1001660508

#include<iostream>

#include "TrickOrTreater.h"

int TrickOrTreater::ImDone = 0;

TrickOrTreater::TrickOrTreater(std::string namesOfPeople, std::vector<House*> houses)
:ListOfHouses{houses}, name{namesOfPeople}
{

};

std::string TrickOrTreater::getName()
{
	return name;
}

void TrickOrTreater::startThread()
{
	TOTThreadPtr = new std::thread(&TrickOrTreater::GoTrickOrTreating, this);
}

void TrickOrTreater::joinThread()
{
	this->TOTThreadPtr->join();
	// delete this->TOTThreadPtr;
}

void TrickOrTreater::GoTrickOrTreating()
{
	int speed;
	for(auto &it: ListOfHouses)
	{
		speed = rand()%500;
		Walk(speed);
		
		std::string names = it->ringDoorbell(path);
		
		Bucket[names]++;
	}
	TrickOrTreater::ImDone++;
}

void TrickOrTreater::Walk(int speed)
{
	for(int i = 0; i < 11; i++)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		path << ".";
	}
}

std::string TrickOrTreater::getPath()
{
	return path.str();
}

std::ostream& operator<<(std::ostream& out, TrickOrTreater& dummy)
{
	out<<dummy.getName();
	for(auto x : dummy.Bucket)
	{
		out << x.second <<" "<<x.first<<",";
	}
	out<<std::endl;
	
	return out;
}
