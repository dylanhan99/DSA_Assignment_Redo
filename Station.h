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
	//vector<Station*>* InterchangeStations;

public:

	Station();
	~Station();

	Station(string name, string id, int dist);

	string getStationName();
	string getStationID();
	int getDistToNext();

	Station* PreviousStation, * NextStation;

	vector<string>* getConnections();

};

