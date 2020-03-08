#include "Graph.h"

Graph::Graph()
{
	Size = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		List[i] = NULL;
}

Graph::~Graph()
{
	delete this;
}

// Horner's hash function
int Graph::hash(KeyType key)
{
	int pos = 0;
	for (int i = 0; i < key.length(); i++)
	{
		int currentChar = charvalue(key[i]);
		// isAlphaNumeric
		if (currentChar >= 0)
			pos += currentChar * NUMOF_CHARS + charvalue(key[i + 1]);
	}
	return pos %= MAX_SIZE;
}

Graph::Node* Graph::getNode(KeyType key)
{
	return NULL;
}

// Add new Station into hash table
bool Graph::add(KeyType key, ItemType item)
{
	return false;
}

bool Graph::remove(KeyType key)
{
	return false;
}

bool Graph::search(KeyType key)
{
	return false;
}

bool Graph::displayLines()
{
	return false;
}