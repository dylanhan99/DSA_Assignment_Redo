#pragma once
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//namespace Globals
//{
	typedef string KeyType;

	// Total number of chars involved: 26 * 2 Alphabet, 10 Numbers
	static int NUMOF_CHARS = 62;
	static char DELIMITER = ',';

	// Convert char to int
	// 0 - 9   Numbers
	// 10 - 35 Uppercase
	// 36 - 61 Lowercase
	// -1 None of the above
	static int charvalue(char c)
	{
		//isAlpha
		if (isalpha(c))
		{
			if (isupper(c))
				return (int)c - (int)'A' + 10;
			else
				return (int)c - (int)'a' + 26 + 10;
		}
		// isNumeric
		else if (48 <= c && c <= 57)
		{
			return (int)c - (int)'0';
		}
		else
			return -1;
	}

	// Get the Line prefix from string.
	// Does this by getting all the alphabets from the string until
	// reaching a non-alphabet.
	// eg. GetLine("EW24") = "EW"
	// eg. GetLine("MyLinePrefix8899") = "MyLinePrefix"
	static string GetLine(string str)
	{
		string s = "";
		for (int i = 0; i < str.length(); i++)
		{
			if (isalpha(str[i]))
				s += str[i];
			// If not char, break
			else
				break;
		}
		return s;
	}

	// Get the station ID from the entered string
	// eg. GetNum("EW24") = 24
	// eg. GetNum("qwErT9009") = 9009
	static string GetNum(string str)
	{
		string line = GetLine(str);
		return str.substr(line.length(), str.length() - 1);
	}

	// trim whitespace from start of string
	static inline string& ltrim(string& s) {
		s.erase(s.begin(), find_if(s.begin(), s.end(),
			not1(ptr_fun<int, int>(isspace))));
		return s;
	}

	// trim whitespace from end of string
	static inline string& rtrim(string& s) {
		s.erase(find_if(s.rbegin(), s.rend(),
			not1(ptr_fun<int, int>(isspace))).base(), s.end());
		return s;
	}

	// Trim function. Used to trim off white space at 
	// the beginning and end of string.
	static string trim(string str)
	{
		return ltrim(rtrim(str));
	}

	// Split the string entered at the delimiter and return a vector of each element in the newly split string
	static vector<string>* Split(string str, char delimiter)
	{
		// count number of delimiter in string to determine List size
		int size = 0;
		for (int i = 0; i < str.size(); i++)
			if (str[i] == delimiter)
				size++;

		vector<string>* split = new vector<string>();
		stringstream ss(str); // Turn the string into a stream.
		string s;

		while (getline(ss, s, delimiter))
			split->push_back(s);


		return split;
	}

	// Check if object is in vector
	static bool isInVec(vector<string> vec, string item)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec.at(i) == item)
				return true;
		}
		return false;
	}

	static int Hash(KeyType key, int MAX_SIZE)
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
//}