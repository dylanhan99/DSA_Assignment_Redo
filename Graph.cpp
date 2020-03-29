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


#pragma region General Functions
Graph::Node* Graph::getNode(KeyType key)
{
	return List[Hash(key, MAX_SIZE)];
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

bool Graph::isEmpty()
{
	if (Size <= 0)
		return true;
	return false;
}

bool Graph::isExist(KeyType key)
{
	int index = Hash(key, MAX_SIZE);
	Node* CurrentNode = List[index];
	while (CurrentNode != NULL)
	{
		if (CurrentNode->Key == key)
			return true;
		CurrentNode = CurrentNode->Next;
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

// Use station name to get station id
// Makes use of Stations.csv
//string findStationID(string StationName)
//{
//	vector<string>* StationsLines = Stations->getLines();
//	if (StationsLines != NULL)
//	{
//		for (int i = 0; i < StationsLines->size(); i++)
//		{
//			string CurrentStr = StationsLines->at(i);
//			vector<string> splt = *Split(CurrentStr, ',');
//			if (splt.back() == StationName)
//			{
//				return splt.return();
//			}
//		}
//	}
//	return "";
//}

// Use station ID to get station name 
// Makes use of Stations.csv
string Graph::findStationName(string StationID)
{
	vector<string>* StationsLines = Stations->getLines();
	if (StationsLines != NULL)
	{
		for (int i = 0; i < StationsLines->size(); i++)
		{
			string CurrentStr = StationsLines->at(i);
			vector<string> splt = *Split(CurrentStr, ',');
			if (splt.front() == StationID)
			{
				return splt.back();
			}
		}
	}
	return "";
}

bool Graph::findPrefixInRoutes(string prefix, vector<string>& retStationIDs)
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
					retStationIDs.push_back(StationIDs.at(j));
			}
		}
	}
	if (retStationIDs.size() <= 0)
		return false;
	return true;
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
					if (j < Distances.size())
						retDistances.push_back(Distances.at(j));
				}
			}
		}
	}
	if (retStationIDs.size() <= 0)
		return false;
	return true;
}
#pragma endregion

#pragma region Feature 1: Display Lines.
void Graph::feature1()
{
	cout << "Select a line to display" << endl;
	coutEqual();
	vector<string>* LinePrefixes = displayLines();
	coutEqual();

	if (LinePrefixes != NULL)
	{
		int option;
		cout << "Line: ";
		cin >> option;
		cout << endl;

		chooseLine(option, LinePrefixes);
		return;
	}
	coutEqual();
	cout << "Error displaying lines..." << endl;
	coutEqual();
}

vector<string>* Graph::displayLines()
{
	vector<string>* FileLines = Stations->getLines();
	vector<string>* LinePrefixes = new vector<string>();
	if (FileLines != NULL)
	{
		for (int i = 0; i < FileLines->size(); i++)
		{
			string CurrentStr = FileLines->at(i);
			string CurrentPrefix = GetLine(Split(CurrentStr, DELIMITER)->at(0));

			if (LinePrefixes->empty())
				LinePrefixes->push_back(CurrentPrefix);
			else
			{
				for (int i = 0; i < LinePrefixes->size(); i++)
				{
					if (!isInVec(*LinePrefixes, CurrentPrefix))
						LinePrefixes->push_back(CurrentPrefix);
				}
			}
		}
		
		for (int i = 0; i < LinePrefixes->size(); i++)
		{
			cout << i + 1 << " " << LinePrefixes->at(i) << endl;
		}
	}
	return LinePrefixes;
}

void Graph::chooseLine(int option, vector<string>* LinePrefixes)
{
	// If within rage of LinePrefixes vector
	if (!(option < 1 || option > LinePrefixes->size()))
	{
		if (displayStations(LinePrefixes->at(option - 1)))
			return;
	}
	coutEqual();
	cout << "Unknown option..." << endl;
	coutEqual();
}

bool Graph::displayStations(string prefix)
{
	/*
	For each StationID in routes, get the station name.
		Use the station name to get the Index in list.
		For each item at the index,
			if the Station ID is current,
				Display information of that Station.
	*/

	vector<string> StationIDs/*, Distances*/;
	if (findPrefixInRoutes(prefix, StationIDs/*, Distances*/))
	{
		cout << "Stations under " << prefix << " line:" << endl;
		coutEqual();
		cout << "ID" << "\t" << "Name" << endl;
		for (int i = 0; i < StationIDs.size(); i++)
		{
			string StationName = findStationName(StationIDs.at(i));
			if (StationName != "")
			{
				cout << StationIDs.at(i) << "\t" << StationName << endl;
			}
		}
		coutEqual();
		return true;
	}
	return false;
}
#pragma endregion

#pragma region Feature 2: Display Station Info.
void Graph::feature2()
{
	string StationName;
	cout << "Enter a station name" << endl;
	coutEqual();
	cout << "Name: ";
	cin >> StationName;
	coutEqual();
	cout << endl;
	StationName = trim(StationName);

	if (!displayStationInfo(StationName))
	{
		coutEqual();
		cout << "No such station: " << StationName << endl;
		coutEqual();
	}
}
// note to self: display the distances to and from each connection. If it is before, display Connection's distance. 
// if it is after, display the station's distnace
bool Graph::displayStationInfo(string StationName)
{
	int index = Hash(StationName, MAX_SIZE);

	Node* CurrentNode = List[index];
	if (isExist(StationName))
	{
		cout << StationName << " Station Info:" << endl;
		coutEqual();
		if (isInterchange(StationName))
			cout << StationName << " is an interchange." << endl;
		while (CurrentNode != NULL)
		{
			if (CurrentNode->Key == StationName)
			{
				Station* CurrentStation = CurrentNode->Station;
				cout << GetLine(CurrentStation->getStationID()) << " Line" << endl;
				cout << CurrentStation->getStationID() << "\t" << CurrentStation->getStationName() << endl;
				cout << "Connections: " << endl;

				if (CurrentStation->PreviousStation != NULL)
					cout << CurrentStation->PreviousStation->getStationID() << "\t"
						 << CurrentStation->PreviousStation->getStationName() << "\t"
						 << CurrentStation->PreviousStation->getDistToNext() << endl;

				if (CurrentStation->NextStation != NULL)
					cout << CurrentStation->NextStation->getStationID() << "\t"
						 << CurrentStation->NextStation->getStationName() << "\t"
						 << CurrentStation->getDistToNext() << endl;
			}
			CurrentNode = CurrentNode->Next;
		}
		cout << "=============================" << endl;
		return true;
	}
	return false;
}
#pragma endregion

#pragma region Feature 3: Add New Station
bool Graph::addNewStation()
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
					if (!isInVec(LinePrefixes, CurrentPrefix))
						LinePrefixes.push_back(CurrentPrefix);
				}
			}
		}

		cout << "Select a line to add to" << endl;
		cout << "=============================" << endl;
		for (int i = 0; i < LinePrefixes.size(); i++)
		{
			cout << i + 1 << " " << LinePrefixes.at(i) << endl;
		}
		cout << "=============================" << endl;

		int option;
		cout << "Line: ";
		cin >> option;
		cout << endl;

		// If within rage of LinePrefixes vector
		if (!(option < 1 || option > LinePrefixes.size()))
		{
			if (displayStations(LinePrefixes.at(option - 1)))
			{

				return true;
			}
		}
		cout << "=============================" << endl;
		cout << "Unknown option" << endl;
		cout << "=============================" << endl;
	}
	return false;
}
#pragma endregion

#pragma region Feature 4: Add New Line

#pragma endregion

#pragma region Feature 5: Find Shortest Route

#pragma endregion

#pragma region Setup Functions
void Graph::initFiles()
{
	Fares = new File(PATH_FARES);
	Interchanges = new File(PATH_INTERCHANGES);
	Routes = new File(PATH_ROUTES);
	Stations = new File(PATH_STATIONS);
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

				// Once interchanges is done, setup connections.
				//setupConnections("test");
				//function should be claled after ALL station objects have been created
			}
		}
		for (int i = 0; i < MAX_SIZE; i++)
		{
			Node* CurrentNode = List[i];
			while (CurrentNode != NULL)
			{
				setupConnections(CurrentNode->Station);
				CurrentNode = CurrentNode->Next;
			}
		}
		return true;
	}
	return false;
}

// Search for target station ID using recursive binary search
int Graph::RoutesBinary(vector<string> vec, int first, int last, int target)
{
	if (first <= last)
	{
		int mid = (first + last) / 2;
		int midVal = stoi(GetNum(vec.at(mid)));
		if (target == midVal)
			return mid;
		else if (target < midVal)
			return RoutesBinary(vec, first, mid - 1, target);
		else if (target > midVal)
			return RoutesBinary(vec, mid + 1, last, target);
	}
	return -1;
}

// Setup the connecting stations for a stated Station object.
bool Graph::setupConnections(Station* station)
{
	if (station != NULL)
	{
		// If is interchange, 
		// For each Node* at List[index] that has key "StationName"
		// use findPrefixInRoutes() to get the StationIDs. From there, get the pos at which current StationID is at.
		// the connections would be pos +- 1.

		// Get the list of StationIDs from routes.csv with the corresponding line prefix
		vector<string> StationIDs;
		if (findPrefixInRoutes(GetLine(station->getStationID()), StationIDs))
		{
			// Using binary search to search for the StationID index in the vector.
			int index = RoutesBinary(StationIDs, 0, StationIDs.size() - 1, 
									 stoi(GetNum(station->getStationID())));
			// If index is within range
			// and the StationID is what im looking for,
			if ((index >= 0 && index < StationIDs.size()) &&
				StationIDs.at(index) == station->getStationID())
			{
				// Check the position of the StationID to get the connections.

				vector<string> ConnectionIDs;
				// StationID is at front,
				// Connection = i + 1
				if (index == 0)
				{
					ConnectionIDs.push_back(StationIDs.at(index + 1));
				}
				// StationID is inbetween first and last,
				// Connection = i +- 1
				if (index > 0 && index < StationIDs.size() - 1)
				{
					ConnectionIDs.push_back(StationIDs.at(index + 1));
					ConnectionIDs.push_back(StationIDs.at(index - 1));

				}
				// StationID is last,
				// Connection = i - 1
				if (index == StationIDs.size() - 1)
				{
					ConnectionIDs.push_back(StationIDs.at(index - 1));
				}

				// If there are connections...
				if (ConnectionIDs.size() > 0)
				{
					// ADD CONNECTIONS TO STATION OBJECT

					for (int i = 0; i < ConnectionIDs.size(); i++)
					{
						//if (!isInVec(*station->getConnections(), ConnectionIDs.at(j))) // Pls change this. Find the root of why its looping more times the longer the chain
						//	station->getConnections()->push_back(ConnectionIDs.at(j));

						Node* node = getNode(findStationName(ConnectionIDs.at(i)));
						while (node != NULL)
						{
							if (node->Station->getStationID() == ConnectionIDs.at(i))
							{
								int IDnum = stoi(GetNum(ConnectionIDs.at(i)));
								// Is previous 
								if (IDnum < stoi(GetNum(station->getStationID())))
									station->PreviousStation = node->Station;
								// Is next
								else if (IDnum > stoi(GetNum(station->getStationID())))
									station->NextStation = node->Station;
								break;
							}
							node = node->Next;
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}
#pragma endregion