#include "Station.h"

Station::Station()
{
	StationName = "";
	StationID = "";
	Connections = new vector<string>();
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
	Connections = new vector<string>();
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