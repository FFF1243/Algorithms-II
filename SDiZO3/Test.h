#pragma once
#pragma once
#include <string>
#include "BinaryHeapT.h"


class Test
{
private:


public:
	static void GenerateTSP(int size);
	static void GenerateKP(int size, int capacity);
	static std::string PATH;

	static void TSPGreedy(int size);
	static void TSPTwoOpt(int size);
	static void TSPFullSearch(int size);

	static void KPGreedy(int size, int capacity);
	static void KPDynamic(int size, int capacity);
	static void KPFullSearch(int size, int capacity);

};
