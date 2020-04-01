#include "File.h"

File::File()
{
	lines = NULL;
	this->path = "";
}

File::File(string path)
{
	lines = NULL;
	this->path = path;
	try {
		getLines();
	} catch (const char* msg) {
		cerr << msg << path << endl;
	}
}

File::~File()
{
	delete this;
}

bool File::isFileExist(fstream& file)
{
	if (!file.fail())
		return true;
	return false;
}


#pragma region General Functions
// Read each line of file and 
vector<string>* File::getLines()
{
	//delete(lines);
	lines = NULL;

	fstream file(path);
	if (isFileExist(file))
	{
		//cout << path << endl;
		lines = new vector<string>();

		for (string line; getline(file, line);)
			lines->push_back(line);

		file.close();
	}
	else
	{
		throw ("Failed to open file: ");
	}
	return lines;
}

// Write line to eof
bool File::writeFile(string line)
{
	fstream file(path, ios::app);
	if (isFileExist(file))
	{
		file << line << endl;
		file.close();

		return true;
	}
	return false;
}

// Write line to specific index in file
bool File::writeFile(string line, int index)
{
	fstream file(path);
	if (isFileExist(file))
	{
		vector<string> newData;
		newData = *getLines();

		newData.insert(newData.begin() + index, line);
		for (int i = 0; i < newData.size(); i++)
			file << newData.at(i) << endl;

		return true;
	}
	return false;
}

bool File::replaceLine(string line, int index)
{
	fstream file(path);
	if (isFileExist(file))
	{
		vector<string> newData = *getLines();
		newData.at(index) = line;

		for (int i = 0; i < newData.size(); i++)
			file << newData.at(i) << endl;

		return true;
	}
	return false;
}