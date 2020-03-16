#include "Station.h"

Station::Station()
{
	StationName = "";
	StationID = "";
	Connections = NULL;
	//InterchangeStations = NULL;
}

Station::~Station()
{
	delete this;
}

Station::Station(string name, string id, int dist)
{
	this->StationName = name;
	this->StationID = id;
	this->DistToNext = dist;
	Connections = NULL;
	//InterchangeStations = NULL;
}

void Station::setupConnections()
{
	int id = stoi(GetNum(this->StationID));
	if (id <= 0)
	{
		string s = GetLine(StationID) + to_string(id + 1);
		Connections->push_back(s);
	}
	else
	{
		string s = GetLine(StationID) + to_string(id + 1);
		Connections->push_back(s);
		s = GetLine(StationID) + to_string(id - 1);
		Connections->push_back(s);
	}
	//Connections->push_back()
}

string Station::getStationName()
{
	return StationName;
}

string Station::getStationID()
{
	return StationID;
}

int Station::getDistToNext()
{
	return DistToNext;
}

vector<string>* Station::getConnections()
{
	return Connections;
}

//vector<Station*>* Station::getInterchangeStations()
//{
//	return InterchangeStations;
//}
