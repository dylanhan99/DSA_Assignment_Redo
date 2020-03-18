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