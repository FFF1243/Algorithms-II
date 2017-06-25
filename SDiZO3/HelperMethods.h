#pragma once
#include <fstream>

#ifndef HELPER_METHODS
#define HELPER_METHODS
class HelperMethods
{
public:
	static bool File_read_line(std::ifstream &file, int tab[], int size);
	static long long ReadQPC();
	static double GetElapsedTime(long long start, long long stop);
	static void SaveToCsv(std::string operation, int size, double result, int density);
	static void SaveAvg(std::string operation, int size, double result);
	static void SaveAvg(std::string operation, int size,int capacity,  double result);
};
#endif