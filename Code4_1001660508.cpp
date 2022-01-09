//Coding Assignment 4
//Anjal Parikh 1001660508

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<iomanip>
#include<stdexcept>
#include<fstream>                 
#include<cstring>


#include "House.h"
#include "TrickOrTreater.h"

#define SIZE 1000

using namespace std;

void get_command_line_params(int argc, char *argv[], string &TOTFile, string &HouseFile, string &CandyFile)
{
	if(argc!=4)
	{
		throw invalid_argument("Missing command line parameters – - Usage : input^filename output^filename");
	}
	else
	{
		TOTFile = argv[1];
		HouseFile = argv[2];
		CandyFile = argv[3];
	}
}	

int main(int argc, char* argv[])
{
	srand(time(NULL));
	string TOTFile, HouseFile, CandyFile;

	int i =0,total =0;
	string fileLine, houseLine, TOTLine;
	string candyNames, candyValues;
	int keyValues = 0;
	map <int, string> myMap;
	vector<House*> housePtr; 
	House *temp;
	vector<TrickOrTreater> TOTs;
	
	//Loop for catching command line param error;
	try
	{
		get_command_line_params(argc,argv,TOTFile,HouseFile,CandyFile);
	}
	catch(invalid_argument &ex)
	{
		cout<<"An exception occured: "<<ex.what()<<endl;
	}
	
	//Reading in the Candy, House Names;

	ifstream CandyInputFile(CandyFile);
	ifstream HouseInputFile(HouseFile);
	ifstream TOTInputFile(TOTFile);
	
	if(CandyInputFile.is_open())
	{
		while(getline(CandyInputFile,fileLine))
		{
			char *cstr = new char[fileLine.length()+1];
			strcpy(cstr,fileLine.c_str());
			
			char *ptr = strtok(cstr,"|");
			candyNames = ptr;
			
			ptr = strtok(NULL," ");
			candyValues = ptr;
			
			keyValues = stoi(candyValues);
	
			myMap.insert(make_pair(keyValues, candyNames));
			
			delete [] cstr;
			
		}
		for(auto it: myMap)
			cout<<	it.first<< "	"<< it.second<<endl;
		
		
	}
	else
	{
		cout<<"The Candy file couldn't open. Sorry!"<<endl;
	}
	
	ostringstream bout;
	int leng;
	int size;

	
	if(HouseInputFile.is_open())
	{
		while(getline(HouseInputFile, houseLine))
		{
			bout << houseLine;
			size = houseLine.size();
			
			for(leng=0;leng<=(11-size);leng++)
			{
				bout << " ";
			}
			
			temp = new House(houseLine, myMap);
			housePtr.push_back(temp);
		}
		size=0;
		
		
	}
	else
	{
		cout<<"Couldn't open the house file. Sorry!"<<endl;
	}
	
	string houselist = bout.str();
	
	if(TOTInputFile.is_open())
	{
		while(getline(TOTInputFile, TOTLine))
		{
			TOTs.push_back(TrickOrTreater{TOTLine , housePtr});
		}
		
	}
	else
	{
		cout<<"Couldn't open the house file. Sorry!"<<endl;
	}
	
	for(auto &it : TOTs)
	{
		it.startThread();
	}
	
	
	while(TrickOrTreater::ImDone != TOTs.size())
	{
		for(int j = 1; j<36; j++)
			cout<<"\n";
		
		cout<< "           ";
		cout << houselist << endl;
		
		for(auto &it : TOTs)
		{
			cout<<it.getPath() <<it.getName() <<endl;
			
		}
		this_thread::sleep_for(chrono::milliseconds(5));
	}
	
	//bucket list
	
	for(auto &var : TOTs)
	{
		cout << var;
	}
	
	for(auto &var : TOTs)
	{
		var.joinThread();
	}
	
	//delete object
	//for(auto &x : House(houseLine, myMap))
	//{
		delete temp;
	//}
	
	CandyInputFile.close();
	HouseInputFile.close();
	TOTInputFile.close();

	return 0;
}