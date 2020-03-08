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


#pragma region Read Files
// Read each line of file and 
vector<string>* File::getLines()
{
	delete(lines);
	lines = NULL;

	fstream file(path);
	if (isFileExist(file))
	{
		lines = new vector<string>();

		for (string line; getline(file, line);)
			lines->push_back(line);

		file.close();
	}
	return lines;
}
#pragma endregion

#pragma region Write Files
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
#pragma endregion