#pragma once
#include "Matrix.h"

using namespace std;
class SalesmanSolution;
class Salesman
{
private:
	Matrix* data;
	int numberOfCities;
	void getNextPermutation(Array<int> & arr, int * p, int & i);			//Na podstawie algorytmu z: quickperm.org
	Array<int> getRandomPermutation();
	Array<int> twoOptSwap(Array<int> & path, int i, int k);
	SalesmanSolution* generateSolution(Array<int> & path);
public:
	Salesman();
	Salesman(int cities);
	~Salesman();
	Matrix* GetData();
	void LoadDataFromFile(string path);
	void PrintData();
	SalesmanSolution* GreedySolution();
	SalesmanSolution* FullSearch();
	SalesmanSolution* TwoOpt();
};

class SalesmanSolution
{
private:
	int distance;
	int cities;
	Array<int>* solution;

public:
	SalesmanSolution(SalesmanSolution & value);
	SalesmanSolution(string name);
	SalesmanSolution();
	~SalesmanSolution();
	void AddCity(int city, int dist);
	void PrintSolution();
	Array<int> GetSolution();
	string SolutionName;
	int GetDistance();
	bool operator<(SalesmanSolution const & right);
	bool operator>(SalesmanSolution const & right);
	bool operator==(SalesmanSolution const & right);
	SalesmanSolution & operator=(SalesmanSolution & rvalue);

};