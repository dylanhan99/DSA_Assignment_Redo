#pragma once
#include <string>

// Total number of chars involved: 26 * 2 Alphabet, 10 Numbers
static int NUMOF_CHARS = 62;

// Paths
static string PATH_BASE = "Full\\";
static string PATH_FARES		= PATH_BASE + "Fares.csv";
static string PATH_INTERCHANGES = PATH_BASE + "Interchanges.csv";
static string PATH_ROUTES		= PATH_BASE + "Routes.csv";
static string PATH_STATIONS		= PATH_BASE + "Stations.csv";

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