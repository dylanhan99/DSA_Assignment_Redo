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

	Node* getNode(KeyType key);

	// General Functions
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
	bool displayLines();
	bool displayStations(string prefix);
	
	// Setup Functions
	void initFiles();
	bool setupStations();
	bool setupConnections(Station* station/*, string StationID, string StationName*/);
};

