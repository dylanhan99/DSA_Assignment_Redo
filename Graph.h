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
static const string PATH_BASE = "Full\\";
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

	//int hash(KeyType key);

	void initFiles();

	Node* getNode(KeyType key);

	bool add(KeyType key, ItemType* item);
	
	bool remove(KeyType key);

	bool search(KeyType key);

	bool displayLines();

	bool displayStations(string prefix);

	bool findPrefixInRoutes(string prefix, vector<string>& Stations, vector<string>& Distances);

	bool isEmpty();

	bool setupStations();

	bool setupConnections(string StationName);

	bool isInterchange(string StationID);
};

