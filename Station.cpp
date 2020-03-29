#include "Station.h"

Station::Station()
{
	StationName = "";
	StationID = "";
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
	this->PreviousStation = NULL;
	this->NextStation = NULL;
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