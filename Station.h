#pragma once

#include "Globals.h"
#include <string>
#include <vector>

using namespace std;

class Station
{
private:
	string StationName;
	string StationID;
	int DistToNext;
	vector<string>* Connections;
	vector<Station*>* InterchangeStations;

public:

	Station();
	~Station();

	Station(string name, string id);

	// Can assume that connections are +-1 of current station 
	// e.g.EW24 connections would be EW23 and EW25
	void setupConnections();

};

