#include "Graph.h"

Graph::Graph()
{
	Size = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		List[i] = NULL;
	initFiles();
}

Graph::~Graph()
{
	delete this;
}

// Horner's hash function
//int Graph::hash(KeyType key)
//{
//	int pos = 0;
//	for (int i = 0; i < key.length(); i++)
//	{
//		int currentChar = charvalue(key[i]);
//		// isAlphaNumeric
//		if (currentChar >= 0)
//			pos += currentChar * NUMOF_CHARS + charvalue(key[i + 1]);
//	}
//	return pos %= MAX_SIZE;
//}

void Graph::initFiles()
{
	Fares = new File(PATH_FARES);
	Interchanges = new File(PATH_INTERCHANGES);
	Routes = new File(PATH_ROUTES);
	Stations = new File(PATH_STATIONS);
}


Graph::Node* Graph::getNode(KeyType key)
{
	return NULL;
}

// Add new Station into hash table
bool Graph::add(KeyType key, ItemType* item)
{
	int index = Hash(key, MAX_SIZE);
	Node* NewNode = new Node();
	NewNode->Key = key;
	NewNode->Station = item;
	NewNode->Next = NULL;
	if (isEmpty())
	{
		List[index] = NewNode;
		Size++;
		return true;
	}
	else
	{
		if (List[index] == NULL)
			List[index] = NewNode;
		else
		{
			Node* CurrentNode = List[index];
			while (CurrentNode->Next != NULL)
				CurrentNode = CurrentNode->Next;
			CurrentNode->Next = NewNode;
		}
		Size++;
		return true;
	}
	return false;
}

bool Graph::remove(KeyType key)
{
	int index = Hash(key, MAX_SIZE);
	if (!isEmpty() && List[index] != NULL)
	{
		Node* CurrentNode = List[index];
		Node* PreviousNode = CurrentNode;
		while (CurrentNode->Next != NULL)
		{
			//  if(PreviousNode->Key)
		}
		return true;
	}
	return false;
}

bool Graph::search(KeyType key)
{
	return false;
}

bool Graph::displayLines()
{
	vector<string>* FileLines = Stations->getLines();
	if (FileLines != NULL)
	{
		vector<string> LinePrefixes;
		for (int i = 0; i < FileLines->size(); i++)
		{
			string CurrentStr = FileLines->at(i);
			string CurrentPrefix = GetLine(Split(CurrentStr, DELIMITER)->at(0));

			if (LinePrefixes.empty())
				LinePrefixes.push_back(CurrentPrefix);
			else
			{
				for (int i = 0; i < LinePrefixes.size(); i++)
				{
					if(!isInVec(LinePrefixes, CurrentPrefix))
						LinePrefixes.push_back(CurrentPrefix);
				}
			}
		}

		cout << "Select a line to display" << endl;
		cout << "=============================" << endl;
		for (int i = 0; i < LinePrefixes.size(); i++)
		{
			cout << i + 1 << " " << LinePrefixes.at(i) << endl;
		}
		cout << "=============================" << endl;

		int option;
		cout << "Line: ";
		cin >> option;

		// If within rage of LinePrefixes vector
		if (!(option < 1 || option > LinePrefixes.size()))
		{
			displayStations(LinePrefixes.at(option - 1));

			return true;
		}
	}
	return false;
}

bool Graph::displayStations(string prefix)
{
	vector<string> StationIDs, Distances;
	if (findPrefixInRoutes(prefix, StationIDs, Distances))
	{
		cout << "Stations under " << prefix << " line:" << endl;
		cout << "=============================" << endl;
		for (int i = 0; i < StationIDs.size(); i++)
		{
			if (i == Distances.size()) 
			{
				cout << StationIDs.at(i) << " " << endl;
				continue;
			}
			cout << StationIDs.at(i) << " " << Distances.at(i) << endl;
		}
		return true;
	}
	return false;
}

bool Graph::findPrefixInRoutes(string prefix, vector<string>& retStationIDs, vector<string>& retDistances)
{
	vector<string> RoutesLines = *Routes->getLines();
	for (int i = 0; i < RoutesLines.size(); i++)
	{
		// If the line contains the StationIDs
		if (i % 2 == 0)
		{
			vector<string> StationIDs = *Split(RoutesLines.at(i), ',');
			vector<string> Distances = *Split(RoutesLines.at(i + 1), ',');

			for (int j = 0; j < StationIDs.size(); j++)
			{
				if (GetLine(StationIDs.at(j)) == prefix)
				{
					retStationIDs.push_back(StationIDs.at(j));
					if(j < Distances.size())
						retDistances.push_back(Distances.at(j));
				}
			}
		}
	}
	if (retStationIDs.size() <= 0)
		return false;
	return true;
}

bool Graph::isEmpty()
{
	if (Size <= 0)
		return true;
	return false;
}

bool Graph::setupStations()
{
	// Loop through each station in Stations.csv 
	vector<string>* StationsLines = Stations->getLines();
	if (StationsLines != NULL)
	{
		for (int i = 0; i < StationsLines->size(); i++)
		{
			vector<string> CurrentStr = *Split(StationsLines->at(i), ',');
			vector<string> StationIDs, Distances;
			Station* newStation = NULL;
			if (findPrefixInRoutes(GetLine(CurrentStr.front()), StationIDs, Distances))
			{
				// Loop through the Station IDs to find the Distance
				for (int j = 0; j < StationIDs.size(); j++)
				{
					//if (j == Distances.size())
					//{
					int Dist = 0;
					if (j < Distances.size())
						Dist = stoi(Distances.at(j));

					newStation = new Station(CurrentStr.back(), CurrentStr.front(), Dist);
					this->add(CurrentStr.back(), newStation);
						
					break;
					//}
				}
			}
		}
			
		// Once interchanges is done, setup connections.
		setupConnections("test");
		return true;
	}
	
	return false;
}

bool Graph::setupConnections(string StationName)
{
	cout << List[0]->Station->getStationID();
	if (isInterchange(StationName))
	{

	}
	else
	{

	}
	return false;
}

bool Graph::isInterchange(string StationName)
{
	int index = Hash(StationName, MAX_SIZE);
	Node* CurrentNode = List[index];
	if (CurrentNode != NULL)
	{
		int Count = 0;
		while (CurrentNode->Next != NULL)
		{
			if (CurrentNode->Station->getStationName() == StationName)
			{
				Count++;
				if (Count > 1)
					return true;
			}
		}
	}
	return false;
}