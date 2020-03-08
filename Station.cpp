#include "Station.h"

Station::Station()
{
	StationName = "";
	StationID = "";
	Connections = NULL;
	InterchangeStations = NULL;
}

Station::~Station()
{
	delete this;
}

Station::Station(string name, string id)
{
	this->StationName = name;
	this->StationID = id;
	Connections = NULL;
	InterchangeStations = NULL;
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