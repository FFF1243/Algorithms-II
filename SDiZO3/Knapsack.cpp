#include "Knapsack.h"
#include <iostream>
#include <fstream>
#include "HelperMethods.h"
#include <memory>
#include <windows.h>
#include <iomanip>
using namespace std;


KnapsackSolution* Knapsack::getSubset(Array<Item> & set, int n,long long int bitmask)
{
	KnapsackSolution * sol = new KnapsackSolution("Full Search");
	for (long long int k = 0; k < n; k++)
	{
		if ((1 << k) & bitmask)
		{
			sol->AddItem(set.Get(k));
			//subset->Add(set.Get(k), subset->GetSize());
		}
	}
	return sol;
}

Knapsack::Knapsack() : items()
{
	this->capacity = 0;
	this->numberOfItems = 0;
}


Knapsack::Knapsack(int size, int items) : items()
{
	this->capacity = size;
	this->numberOfItems = items;
}

Knapsack* Knapsack::LoadDataFromFile(string path)
{
	ifstream file;
	Knapsack* data = nullptr;
	int tab[2];
	file.open(path.c_str());
	if (file.is_open())
	{
		if (HelperMethods::File_read_line(file, tab, 2))
		{
			data = new Knapsack(tab[0], tab[1]);
			for (int i = 0; i < data->numberOfItems; i++)
				if (HelperMethods::File_read_line(file, tab, 2))
				{
					Item tempItem(tab[1], tab[0], i);
					data->items.Add(tempItem, data->items.GetSize());
				}
				else
				{
					cout << "File error - READ EDGE" << endl;
					break;
				}
		}
		else cout << "File error - READ INFO" << endl;
		file.close();
	}
	else
		cout << "File error - OPEN" << endl;

	return data;
}

void Knapsack::PrintAllItems()
{
	cout << "Problem" << endl << "Capacity: " << capacity << endl << "Items: "<< numberOfItems << endl << "-------------------------" << endl;
	cout << setw(8) << "Item" << setw(8) << "Size" << setw(8) << "Value" << endl;
	for (int i = 0; i < numberOfItems; i++)
	{
		cout << setw(8) << items[i].Index << setw(8) << items[i].Weight << setw(8) << items[i].Value << endl;
	}
	cout << endl;
}

KnapsackSolution* Knapsack::GreedySolution(bool orderByValue)
{
	string name;
	if (orderByValue)
		name = "value";
	else
		name = "value / weight";
	BinaryHeapT<Item> * queue = new BinaryHeapT<Item>(numberOfItems);
	KnapsackSolution * solution = new KnapsackSolution("Approxximation Solution - Ordering by " + name);
	for(int i = 0; i < numberOfItems; i++)
	{
		items[i].OrderByValue = orderByValue;
		queue->Add(items[i]);
	}

	int currentWeight = 0;
	//queue->PrintData();
	while(currentWeight < capacity && queue->GetSize() > 0)
	{
		Item item = queue->GetFront();
		if(item.Weight + currentWeight <= capacity)
		{
			solution->AddItem(item);
			currentWeight += item.Weight;
		}

		queue->Delete();
	}


	delete queue;
	return solution;
}

KnapsackSolution* Knapsack::DynamicSolution()
{
	int** array  = new int*[numberOfItems + 1];
	int** picked = new int*[numberOfItems + 1];
	KnapsackSolution * solution = new KnapsackSolution("Dynamic Programming");

	for(int i = 0 ; i < numberOfItems + 1; i++)
	{
		array[i] = new int[capacity + 1];
		picked[i] = new int[capacity + 1];
	}

	for (int i = 0; i < numberOfItems + 1; i++)
	{
		for(int j = 0; j < capacity + 1; j++)
		{
			if (i == 0 || j == 0)
				array[i][j] = 0;
			else if (items[i - 1].Weight <= j)
			{
				array[i][j] = max(items[i - 1].Value + array[i - 1][j - items[i - 1].Weight], array[i - 1][j]);
				if (items[i - 1].Value + array[i - 1][j - items[i - 1].Weight] > array[i - 1][j])
					picked[i][j] = 1;
				else
					picked[i][j] = -1;
			}
			else
			{
				array[i][j] = array[i - 1][j];
				picked[i][j] = -1;
			}

		}
	}

	int i = numberOfItems;
	int j = capacity;
	while(i > 0)
	{
		if (picked[i][j] == 1)
		{
			solution->AddItem(items[i - 1]);
			j -= items[i - 1].Weight;
		}
		i--;
	}

	for (int i = 0; i < numberOfItems + 1; i++)
	{
		delete[] array[i];
		delete[] picked[i];
	}

	delete[] array;
	delete[] picked;

	return solution;
}

KnapsackSolution* Knapsack::FullSearch()
{
	KnapsackSolution * solution;
	KnapsackSolution * bestSolution = new KnapsackSolution("Full Search");
	long long int maxBitmask =( static_cast<long long>(1) << numberOfItems);

	for (long long int i = 1; i < maxBitmask; i++)
	{
		solution = getSubset(items, numberOfItems, i);
		//solution->PrintData();
		if(solution->GetTotalWeight() <= capacity && solution->GetTotalValue() > bestSolution->GetTotalValue())
		{
			delete bestSolution;
			bestSolution = solution;
			solution = nullptr;
		}
		else
		{
			delete solution;
		}
	}

	return bestSolution;

}

KnapsackSolution::KnapsackSolution(string name) : sumValue(0), weight(0), numberOfItems(0), items(0), name(name)
{
	
}

void KnapsackSolution::AddItem(Item item)
{
	items.Add(item, items.GetSize());
	weight += item.Weight;
	numberOfItems++;
	sumValue += item.Value;
}

int KnapsackSolution::GetTotalValue()
{
	return sumValue;
}

int KnapsackSolution::GetTotalWeight()
{
	return weight;
}

void KnapsackSolution::PrintData()
{
	cout << "Solution" << endl << name << endl << "-------------------------" << endl;
	cout << setw(8) << "Item" << setw(8) << "Size" << setw(8) << "Value" << endl;
	for(int i = 0; i < numberOfItems; i++)
	{
		cout << setw(8) << items[i].Index << setw(8) << items[i].Weight << setw(8) << items[i].Value << endl;
	}
	cout << setw(24) << "------------------------" << endl;
	cout << setw(8) << "TOTAL" << setw(8) << weight << setw(8) << sumValue << endl << endl;
}

