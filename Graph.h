#pragma once

#include "File.h"
#include "Station.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//typedef string KeyType;
typedef Station ItemType;

// This graph will make use of Hash table
// The hash function makes use of Horner's rule

const int MAX_SIZE = 200;

// Paths
static const string PATH_BASE = "Demo\\"; /// Full or Demo
static const string PATH_FARES = PATH_BASE + "Fares.csv";
static const string PATH_INTERCHANGES = PATH_BASE + "Interchanges.csv";
static const string PATH_ROUTES = PATH_BASE + "Routes.csv";
static const string PATH_STATIONS = PATH_BASE + "Stations.csv";

class Graph
{
private:
	struct Node
	{
		KeyType Key;
		ItemType* Station;
		Node* Next;
	};

	Node* List[MAX_SIZE];
	int Size;
	File* Fares, * Interchanges, * Routes, * Stations;

public:
	Graph();
	~Graph();

	// General Functions
	Node* getNode(KeyType key);
	// The Add function is used ONLY for setup. Use the AddNewStation() function for NEW stations. It updates files as well.
	bool add(KeyType key, ItemType* item);
	bool remove(KeyType key);
	bool search(KeyType key);
	bool isEmpty();
	bool isExist(KeyType key);
	bool isInterchange(string StationID);
	//string findStationID(string StationName);
	string findStationName(string StationID);
	bool findPrefixInRoutes(string prefix, vector<string>& retStationIDs);
	bool findPrefixInRoutes(string prefix, vector<string>& Stations, vector<string>& Distances);

	// Feature 1: Display Lines.
	void feature1();
	vector<string>* displayLines();
	bool displayStations(string prefix);

	// Feature 2: Display Station Info.
	void feature2();
	bool displayStationInfo(string StationName);

	// Feature 3: Add New Station
	void feature3();
	bool addNewStation_Choose(ItemType* station);
	bool addNewStation_Last(ItemType* station);

	// Feature 4: Add New Line

	// Feature 5: Find Shortest Route
	
	// Setup Functions
	void initFiles();
	bool setupStations();
	bool setupConnections(Station* station/*, string StationID, string StationName*/);

	int RoutesBinary(vector<string> vec, int first, int last, int target);

};

