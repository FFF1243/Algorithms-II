#pragma once
#pragma once
#ifndef UI_HEADER
#define UI_HEADER
#include <string>


class UI
{
private:

public:
	static int ShowMainMenu();
	static void TSPMenu();
	static void KnapsackMenu();
	static std::string ReadPath();
	static void Start();
	static int ShowTSPMenu();
	static int ShowKnapsackMenu();
};

#endif