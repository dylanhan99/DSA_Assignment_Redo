#pragma once
#include <string>

using namespace std;

// Total number of chars involved: 26 * 2 Alphabet, 10 Numbers
static int NUMOF_CHARS = 62;

// Convert char to int
// 0 - 9   Numbers
// 10 - 35 Uppercase
// 36 - 61 Lowercase
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