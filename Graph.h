#pragma once

#include "Globals.h"
#include "File.h"
#include "Station.h"
#include <string>
#include <iostream>
using namespace std;

// This graph will make use of Hash table
// The hash function makes use of Horner's rule
typedef string KeyType;
typedef Station ItemType;

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
		KeyType key;
		ItemType* station;
		Node* next;
	};

	Node* List[MAX_SIZE];
	int Size;
	File* Fares, * Interchanges, * Routes, * Stations;

public:
	Graph();
	~Graph();

	int hash(KeyType key);

	bool initFiles();

	Node* getNode(KeyType key);

	bool add(KeyType key, ItemType item);
	
	bool remove(KeyType key);

	bool search(KeyType key);

	bool displayLines();
};

