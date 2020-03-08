#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class File
{
private:
	string path;
	vector<string>* lines;

public:
	File();
	~File();

	File(string path);

	bool isFileExist(fstream& file);

	vector<string>* getLines();

	// Write line to eof
	bool writeFile(string line);

	// Write line to specific index in file
	bool writeFile(string line, int index);
};

