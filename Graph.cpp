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

Graph::Node* Graph::getNode(KeyType key)
{
	return NULL;
}

#pragma region General Functions
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
					if (!isInVec(LinePrefixes, CurrentPrefix))
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
		cout << endl;

		// If within rage of LinePrefixes vector
		if (!(option < 1 || option > LinePrefixes.size()))
		{
			if(displayStations(LinePrefixes.at(option - 1)))
				return true;
		}
	}
	cout << "=============================" << endl;
	cout << "Unknown option..." << endl;
	cout << "=============================" << endl;
	return false;
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
		cout << "=============================" << endl;
		cout << "ID" << "\t" << "Name" /*<< "\t\t" << "Dist to Next(m)"*/ << endl;
		for (int i = 0; i < StationIDs.size(); i++)
		{
			string StationName = findStationName(StationIDs.at(i));
			if (StationName != "")
			{
				//if (i == Distances.size())
				//{
				//	if (StationName.size() < 8)
				//	{
				//		cout << StationIDs.at(i) << "\t" << StationName << "\t\t" << endl;
				//		continue;
				//	}
				//	cout << StationIDs.at(i) << "\t" << StationName << "\t" << endl;
				//	continue;
				//}
				//if (StationName.size() < 8)
				//{
				//	cout << StationIDs.at(i) << "\t" << StationName << "\t\t" << Distances.at(i) << endl;
				//	continue;
				//}
				cout << StationIDs.at(i) << "\t" << StationName/* << "\t" << Distances.at(i)*/ << endl;
			}
		}
		cout << "=============================" << endl;
		return true;
	}
	return false;
}
#pragma endregion

#pragma region Feature 2: Display Station Info.
// note to self: display the distances to and from each connection. If it is before, display Connection's distance. 
// if it is after, display the station's distnace
bool Graph::displayStationInfo()
{
	string StationName;
	cout << "Enter a station name" << endl;
	cout << "=============================" << endl;
	cout << "Name: ";
	cin >> StationName;
	cout << "=============================" << endl;
	cout << endl;
	StationName = trim(StationName);
	int index = Hash(StationName, MAX_SIZE);

	Node* CurrentNode = List[index];
	if (isExist(StationName))
	{
		cout << StationName << " Station Info:" << endl;
		cout << "=============================" << endl;
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

				vector<string> Connections = *CurrentStation->getConnections();

				vector<string> StationIDs, Distances;
				if (findPrefixInRoutes(GetLine(CurrentStation->getStationID()), StationIDs, Distances))
				{
					for (int i = 0; i < Connections.size(); i++)
					{
						for (int j = 0; j < StationIDs.size(); j++)
						{
							// isBefore checks the position of CurrentStation's StationID. 
							// isBefore as in CurrentStation isBefore this one im checking now.
							// If CurrentStation's StationID comes after the StationID in <vec>StationIDs,
							//		isBefore will remain false, and will cout the distance of StationID in <vec>StationIDs.
							// Else
							//		will cout the distance of CurrentStation
							bool isBefore = false;
							if (StationIDs.at(j) == CurrentStation->getStationID())
								isBefore = true;
							if (StationIDs.at(j) == Connections.at(i))
							{
								// !isBefore - the station ID is lower than CurrentStationID, cout distance of StationID in <vec>StationIDs
								if (!isBefore)
								{
									if (j >= Distances.size() - 1)
									{
										cout << Connections.at(i) << "\t" << findStationName(Connections.at(i)) << "\t" << "-" << endl;
										break;
									}
									cout << Connections.at(i) << "\t" << findStationName(Connections.at(i)) << "\t" << Distances.at(j) << endl;
								}
								else
									cout << Connections.at(i) << "\t" << findStationName(Connections.at(i)) << "\t" << Distances.at(j - 1) << endl;
							}
						}
						if (i + 1 >= Connections.size())
							cout << endl;
						//if (i < Connections.size())
						//	cout << "____________________________\n";
					}
				}
			}
			CurrentNode = CurrentNode->Next;
		}
		cout << "=============================" << endl;
		return true;
	}
	cout << "=============================" << endl;
	cout << "No such station: " << StationName << endl;
	cout << "=============================" << endl;
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
				setupConnections(newStation);
			}
		}
		return true;
	}
	return false;
}

bool Graph::setupConnections(Station* station/*, string StationID, string StationName*/)
{
	if (isExist(station->getStationName()))
	{
		// If is interchange, 
		// For each Node* at List[index] that has key "StationName"
		// use findPrefixInRoutes() to get the StationIDs. From there, get the pos at which current StationID is at.
		// the connections would be pos +- 1.
		int index = Hash(station->getStationName(), MAX_SIZE);
		Node* CurrentNode = List[index];
		if (CurrentNode != NULL)
		{
			// Looping through each node in link list...
			while (CurrentNode != NULL)
			{
				// If the name of the node is what im looking for,
				if (CurrentNode->Key == station->getStationName())
				{
					// Get the list of StationIDs from routes.csv with the corresponding line prefix
					vector<string> StationIDs;
					if (findPrefixInRoutes(GetLine(station->getStationID()), StationIDs))
					{
						// For each StationID from the list of StationIDs,
						for (int i = 0; i < StationIDs.size(); i++)
						{
							// If the StationID is what im looking for,
							if (StationIDs.at(i) == station->getStationID())
							{
								// Check the position of the StationID to get the connections.

								vector<string> ConnectionIDs;
								// StationID is at front,
								// Connection = i + 1
								if (i == 0)
								{
									ConnectionIDs.push_back(StationIDs.at(i + 1));
								}
								// StationID is inbetween first and last,
								// Connection = i +- 1
								if (i > 0 && i < StationIDs.size() - 1)
								{
									ConnectionIDs.push_back(StationIDs.at(i + 1));
									ConnectionIDs.push_back(StationIDs.at(i - 1));

								}
								//StationID is last,
								// Connection = i - 1
								if (i == StationIDs.size() - 1)
								{
									ConnectionIDs.push_back(StationIDs.at(i - 1));
								}

								if (ConnectionIDs.size() > 0)
								{
									// ADD CONNECTIONS TO STATION OBJECT

									for (int j = 0; j < ConnectionIDs.size(); j++)
									{
										if (!isInVec(*station->getConnections(), ConnectionIDs.at(j))) // Pls change this. Find the root of why its looping more times the longer the chain
											station->getConnections()->push_back(ConnectionIDs.at(j));
									}
								}
								break;
							}
						}
					}
				}
				CurrentNode = CurrentNode->Next;
			}
			return true;
		}
	}
	return false;
}
#pragma endregion