#include "Test.h"
#include <string>
#include "HelperMethods.h"
#include <random>
#include "Matrix.h"
#include <iostream>
#include <windows.h>
#include "Salesman.h"
#include "Knapsack.h"


void Test::GenerateTSP(int size)
{
	BinaryHeapT<Edge>* allEdges;
	std::fstream file;
	std::string path;
	std::random_device	rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 100);

	for (int i = 0; i < 100; i++)
	{
		path = PATH + "TSP\\" + std::to_string(size);
		path.append("\\" + std::to_string(i) + ".txt");
		file.open(path.c_str(), std::ios::out);
			if (file.good())
			{
				file << size << endl;
				for (int j = 0; j < size; j++)
				{
					for(int k = 0; k < size - 1; k++)
					{
						file << dist(gen) << " ";
					}
					file << dist(gen) << endl;
				}
				file.close();
			}
	}
}

void Test::GenerateKP(int size, int capacity)
{
	std::fstream file;
	std::string path;

	int sum;
	std::random_device	rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 100);
	std::uniform_int_distribution<> distV(20, 200);
	for (int i = 0; i < 100; i++)
	{

		path = PATH + "Knapsack\\" + std::to_string((size)) + "\\" + std::to_string(capacity);
		path.append("\\" + std::to_string(i) + ".txt");

		do
		{
			file.open(path.c_str(), std::ios::out);
			sum = 0;
			int weight;
			if (file.good())
			{
				file << capacity << " " << size << endl;
				for (int j = 0; j < size; j++)
				{
					weight = dist(gen);
					sum += weight;
					file << weight << " " << distV(gen) << endl;
				}
				file.close();
			}
		} while (sum < capacity);


	}
}

void Test::TSPGreedy(int size)
{
	long long int start, stop;
	Salesman* data = nullptr;
	SalesmanSolution* solution = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		data = new Salesman();
		path = PATH + "TSP\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		data->LoadDataFromFile(path);
		start = HelperMethods::ReadQPC();
		solution = data->GreedySolution();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("PrimAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);

		delete data;
		delete solution;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("TSPGreedy", size, avg);
}

void Test::TSPTwoOpt(int size)
{
	long long int start, stop;
	Salesman* data = nullptr;
	SalesmanSolution* solution = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		data = new Salesman();
		path = PATH + "TSP\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		data->LoadDataFromFile(path);
		start = HelperMethods::ReadQPC();
		solution = data->TwoOpt();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("PrimAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);

		delete data;
		delete solution;
	}
	avg = avg / 3.0;
	HelperMethods::SaveAvg("TSPTwoOpt", size, avg);
}

void Test::TSPFullSearch(int size)
{
	long long int start, stop;
	Salesman* data = nullptr;
	SalesmanSolution* solution = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		data = new Salesman();
		path = PATH + "TSP\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		data->LoadDataFromFile(path);
		start = HelperMethods::ReadQPC();
		solution = data->FullSearch();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("PrimAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);

		delete data;
		delete solution;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("TSPFullSearch1415", size, avg);
}

void Test::KPGreedy(int size, int capacity)
{
	long long int start, stop;
	Knapsack* data = nullptr;
	KnapsackSolution* solution = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		data = new Knapsack();
		path = PATH + "Knapsack\\" + std::to_string(size) + "\\" + std::to_string(capacity) + "\\";
		path.append(std::to_string(i) + ".txt");
		data = Knapsack::LoadDataFromFile(path);
		start = HelperMethods::ReadQPC();
		solution = data->GreedySolution(true);
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("PrimAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);

		delete data;
		delete solution;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("KPGreedy", size,capacity, avg);
}

void Test::KPDynamic(int size, int capacity)
{
	long long int start, stop;
	Knapsack* data = nullptr;
	KnapsackSolution* solution = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		data = new Knapsack();
		path = PATH + "Knapsack\\" + std::to_string(size) + "\\" + std::to_string(capacity) + "\\";
		path.append(std::to_string(i) + ".txt");
		data = Knapsack::LoadDataFromFile(path);
		start = HelperMethods::ReadQPC();
		solution = data->DynamicSolution();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("PrimAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);

		delete data;
		delete solution;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("KPDynamic", size, capacity, avg);
}

void Test::KPFullSearch(int size, int capacity)
{
	long long int start, stop;
	Knapsack* data = nullptr;
	KnapsackSolution* solution = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		data = new Knapsack();
		path = PATH + "Knapsack\\" + std::to_string(size) + "\\" + std::to_string(capacity) + "\\";
		path.append(std::to_string(i) + ".txt");
		data = Knapsack::LoadDataFromFile(path);
		start = HelperMethods::ReadQPC();
		solution = data->FullSearch();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("PrimAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);

		delete data;
		delete solution;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("KPFullSearch", size, capacity, avg);
}

std::string Test::PATH = "D:\\PWR\\SDiZO\\Projekt3Dane\\";
