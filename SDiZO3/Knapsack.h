#pragma once
#ifndef KNAPSACK_H
#define KNAPSACK_H
#include "BinaryHeapT.h"
#include <memory>
#include "Array.h"
using namespace std;

class KnapsackSolution;
class Knapsack
{
private:
	Array<Item> items;
	int capacity;
	int numberOfItems;
	KnapsackSolution* Knapsack::getSubset(Array<Item> & set, int n,long long int bitmask);

public:
	Knapsack();
	Knapsack(int size, int items);
	static Knapsack* LoadDataFromFile(string path);
	void PrintAllItems();
	KnapsackSolution* GreedySolution(bool orderByValue);
	KnapsackSolution* DynamicSolution();
	KnapsackSolution* FullSearch();

};

class KnapsackSolution
{
private:
	Array<Item> items;
	int weight;
	int sumValue;
	int numberOfItems;
	string name;

public:
	KnapsackSolution(string);
	void AddItem(Item item);
	int GetTotalValue();
	int GetTotalWeight();
	void PrintData();
};
#endif