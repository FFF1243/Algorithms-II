#include "Salesman.h"
#include <iostream>
#include <iomanip>

void Salesman::getNextPermutation(Array<int> & arr, int * p, int & i)
{
		int j;
		p[i]--;

		if (i % 2 == 1)
			j = p[i];
		else
			j = 0;

		swap(arr[j], arr[i]);
		i = 1;

		while (p[i] == 0)
		{
			p[i] = i;
			i++;
		}
}

Array<int> Salesman::getRandomPermutation()
{
	Array<int> result;

	for(int i = 1; i < numberOfCities; i++)
	{
		result.Add(i, result.GetSize());
	}

	int swaps = numberOfCities / 2;
	int i, j;
	while(swaps > 0)
	{
		do
		{
			i = rand() % (numberOfCities - 1);
			j = rand() % (numberOfCities - 1);
		} while (i == j);
		result.Swap(i, j);
		swaps--;
	}

	//SalesmanSolution* sol = GreedySolution();																	// Odkomentowac jesli ma zwracac permutacje z algorytmu zachlannego
	//result = sol->GetSolution();
	//result.Delete(result.GetSize() - 1);
	//result.Delete(0);
	//delete sol;

	return result;
}

Array<int> Salesman::twoOptSwap(Array<int> & path, int i, int k)
{
	int d = k - i;

	Array<int> newRoute;

	for(int p = 0; p < i; p++)
	{
		newRoute.Add(path.Get(p), newRoute.GetSize());
	}
	int temp = 0;
	for(int p = i; p <= k; p++)
	{
		newRoute.Add(path.Get(k-temp), newRoute.GetSize());
		temp++;
	}
	for(int p = k + 1; p < path.GetSize(); p++)
	{
		newRoute.Add(path.Get(p), newRoute.GetSize());
	}

	
	return newRoute;

}

SalesmanSolution* Salesman::generateSolution(Array<int>& path)
{
	SalesmanSolution* solution = new SalesmanSolution();
	solution->AddCity(0, data->GetRow(0)->Get(path.Get(0)));
	for (int i = 0; i < path.GetSize() - 1; i++)
	{
		solution->AddCity(path.Get(i), data->GetRow(path.Get(i))->Get(path.Get(i + 1)));
	}
	solution->AddCity(path.Get(path.GetSize() - 1), data->GetRow(path.Get(path.GetSize() - 1))->Get(0));
	solution->AddCity(0, 0);

	return solution;
}

Salesman::Salesman()
{
	numberOfCities = 0;
	data = nullptr;
}

Salesman::Salesman(int cities)
{
	numberOfCities = cities;
	data = nullptr;
}

Matrix* Salesman::GetData()
{
	return data;
}

void Salesman::LoadDataFromFile(string path)
{
	data = Matrix::ReadDataFromFile(path);
	if (!data)
		return;
	numberOfCities = data->GetVertexes();
}

void Salesman::PrintData()
{
	if (data)
	{
		cout << "Travelling salesman problem" << endl << "Number of citites: " << numberOfCities << endl << endl;
		data->PrintData();
	}
	else
		cout << "Nie wczytano danych" << endl;
}

SalesmanSolution* Salesman::GreedySolution()
{
	if (!data)
		return nullptr;

	SalesmanSolution* solution = new SalesmanSolution("Greedy");
	bool * visited = new bool[numberOfCities];
		for (int i = 0; i < numberOfCities; i++)
		{
			visited[i] = false;
		}

		int city = 0;
		int nextCity = 0;
		for (int i = 0; i < numberOfCities - 1; i++)
		{
			city = nextCity;
			visited[city] = true;
			nextCity = data->GetRow(city)->GetIndexOfMin(visited, city);
			solution->AddCity(city, data->GetRow(city)->Get(nextCity));
		}
		city = nextCity;
		solution->AddCity(city, data->GetRow(city)->Get(nextCity));
		solution->AddCity(0, data->GetRow(nextCity)->Get(0));


	delete[] visited;
	return solution;
}

SalesmanSolution* Salesman::FullSearch()
{
	SalesmanSolution * solution;
	SalesmanSolution * bestSolution = nullptr;

	Array<int>* allCities = new Array<int>(numberOfCities - 1);
	int * p = new int[numberOfCities];
	for(int i = 0; i < numberOfCities - 1; i++)
	{
		allCities->Insert(i + 1, i);
		p[i] = i;
	}
	p[numberOfCities - 1] = numberOfCities - 1;

	int k = 0;
	while(k < allCities->GetSize())
	{
		getNextPermutation(*allCities, p, k);
		solution = generateSolution(*allCities);
		if(!bestSolution || solution->GetDistance() < bestSolution->GetDistance())
		{
			delete bestSolution;
			bestSolution = solution;
		}
		else
		{
			delete solution;
		}
	}

	delete[] p;
	delete allCities;

	bestSolution->SolutionName = "Full Search";
	return bestSolution;
}

SalesmanSolution* Salesman::TwoOpt()
{
	SalesmanSolution* solution = nullptr;
	SalesmanSolution* bestSolution = nullptr;
	Array<int> permutation = getRandomPermutation();
	bestSolution = generateSolution(permutation);
	bool improvement;

	do
	{
		improvement = false;
		//bestSolution->PrintSolution();
		for (int i = 0; i < permutation.GetSize() - 1; i++)
		{
			for (int j = i + 1; j < permutation.GetSize(); j++)
			{
				permutation = twoOptSwap(permutation, i, j);
				solution = generateSolution(permutation);
				if (solution->GetDistance() < bestSolution->GetDistance())
				{
					delete bestSolution;
					bestSolution = solution;
					improvement = true;
					i = permutation.GetSize() - 1;
					break;
				}
				else
				{
					delete solution;
				}
			}
		}
	} while (improvement);
	

	bestSolution->SolutionName = "2-Opt Optimalization";
	return bestSolution;
}

Salesman::~Salesman()
{
	delete data;
}

SalesmanSolution::SalesmanSolution(SalesmanSolution& rvalue)
{
	cities = rvalue.cities;
	distance = rvalue.distance;
	solution = new Array<int>();
	for (int i = 0; i < rvalue.solution->GetSize(); i++)
	{
		solution->Add(rvalue.solution->Get(i), solution->GetSize());
	}
}

SalesmanSolution::SalesmanSolution(string name)
{
	distance = 0;
	solution = new Array<int>();
	cities = 0;
	SolutionName = name;
}

SalesmanSolution::SalesmanSolution()
{
	distance = 0;
	solution = new Array<int>();
	cities = 0;
	SolutionName = "Unknown";
}

SalesmanSolution::~SalesmanSolution()
{
	delete solution;
}

void SalesmanSolution::AddCity(int city, int dist)
{
	solution->Add(city, solution->GetSize());
	distance += dist;
	cities++;
}

void SalesmanSolution::PrintSolution()
{
	cout << "Solution" << endl << SolutionName << endl << "------------------------------------" << endl;
	cout << right << setw(10) << "Length = " << distance << endl;
	cout << right << setw(10) << "Path = ";
	for(int i = 0; i < cities; i++)
	{
		cout << solution->Get(i) << " - ";
	}
	cout << endl << endl;

}

Array<int> SalesmanSolution::GetSolution()
{
	return *solution;
}

int SalesmanSolution::GetDistance()
{
	return distance;
}

bool SalesmanSolution::operator<(SalesmanSolution const & right)
{
	return this->distance < right.distance;
}

bool SalesmanSolution::operator>(SalesmanSolution const& right)
{
	return this->distance > right.distance;
}

bool SalesmanSolution::operator==(SalesmanSolution const& right)
{
	return this->distance == right.distance;
}

SalesmanSolution& SalesmanSolution::operator=(SalesmanSolution& rvalue)
{
	if(this != &rvalue)
	{
		cities = rvalue.cities;
		distance = rvalue.distance;
		solution = new Array<int>();
		for(int i = 0; i < rvalue.solution->GetSize(); i++)
		{
			solution->Add(rvalue.solution->Get(i), solution->GetSize());
		}
	}

	return *this;
}

