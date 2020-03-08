#pragma once

#include "Globals.h"
#include "Station.h"
#include <string>
#include <iostream>
using namespace std;

// This graph will make use of Hash table
// The hash function makes use of Horner's rule
typedef string KeyType;
typedef Station ItemType;

const int MAX_SIZE = 200;
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


public:
	Graph();
	~Graph();

	int hash(KeyType key);

	Node* getNode(KeyType key);

	bool add(KeyType key, ItemType item);
	
	bool remove(KeyType key);

	bool search(KeyType key);

	bool displayLines();
};

