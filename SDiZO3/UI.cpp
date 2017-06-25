#include "UI.h"
#include <iostream>
#include <string>
#include "Matrix.h"
#include "Salesman.h"
#include "Knapsack.h"
using namespace std;
int UI::ShowTSPMenu()
{
	int a;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		cout << endl << "Wybierz operacje " << endl
			<< "1. Wczytaj dane" << endl
			<< "2. Wszystkie algorytmy" << endl
			<< "3. Przeglad zupelny" << endl
			<< "4. Algorytm zachlanny" << endl
			<< "5. Algorytm 2-opt" << endl
			<< "6. Wyjscie" << endl;

		cin >> a;

	} while (a > 6 || a < 1 || std::cin.fail());
	return a;
}

int UI::ShowKnapsackMenu()
{
	int a;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		cout << endl << "Wybierz operacje " << endl
			<< "1. Wczytaj dane" << endl
			<< "2. Wszystkie algorytmy" << endl
			<< "3. Przeglad zupelny" << endl
			<< "4. Algorytm zachlanny" << endl
			<< "5. Programowanie dynamiczne" << endl
			<< "6. Wyjscie" << endl;

		cin >> a;

	} while (a > 6 || a < 1 || std::cin.fail());
	return a;
}

int UI::ShowMainMenu()
{
	int a;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		cout << endl << "Wybierz operacje " << endl
			<< "1. Problem komiwojazera" << endl
			<< "2. Problem plecakowy" << endl
			<< "3. Wyjscie" << endl;

		cin >> a;

	} while (a > 3 || a < 1 || std::cin.fail());
	return a;
}

void UI::TSPMenu()
{
	string path = "";
	Salesman* data = new Salesman();
	SalesmanSolution* solution;
	do
	{
		switch (ShowTSPMenu())
		{
		case 1:
		{
			cin.ignore();
			while (!data->GetData())
			{
				path = ReadPath();
				data->LoadDataFromFile(path);
			}
			cout << "Wczytano dane." << endl;
			break;
		}
		case 2:
		{
			if (data->GetData())
			{
				data->PrintData();

				solution = data->GreedySolution();
				solution->PrintSolution();
				delete solution;

				solution = data->TwoOpt();
				solution->PrintSolution();
				delete solution;

				solution = data->FullSearch();
				solution->PrintSolution();
				delete solution;

				solution = nullptr;
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 3:
		{
			if (data->GetData())
			{
				data->PrintData();
				solution = data->FullSearch();
				solution->PrintSolution();
				delete solution;

				solution = nullptr;
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 4:
		{
			if (data->GetData())
			{
				data->PrintData();
				solution = data->GreedySolution();
				solution->PrintSolution();
				delete solution;

				solution = nullptr;
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 5:
		{
			if (data->GetData())
			{
				data->PrintData();
				solution = data->TwoOpt();
				solution->PrintSolution();
				delete solution;

				solution = nullptr;
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 6:
		{
			if (data->GetData())
			{
				delete data;
			}
			Start();
			return;
		}
		default:
		{
			if (data->GetData())
			{
				delete data;
			}
			Start();
			return;
		}
		}
	} while (true);
}

void UI::KnapsackMenu()
{
	string path = "";
	Knapsack* data = nullptr;
	KnapsackSolution* solution;
	do
	{
		switch (ShowKnapsackMenu())
		{
		case 1:
		{
			cin.ignore();
			while (!data)
			{
				path = ReadPath();
				data = Knapsack::LoadDataFromFile(path);
			}
			cout << "Wczytano dane." << endl;
			break;
		}
		case 2:
		{
			if (data)
			{
				data->PrintAllItems();

				solution = data->GreedySolution(true);
				solution->PrintData();
				delete solution;

				solution = data->GreedySolution(false);
				solution->PrintData();
				delete solution;

				solution = data->DynamicSolution();
				solution->PrintData();
				delete solution;

				solution = data->FullSearch();
				solution->PrintData();
				delete solution;

				solution = nullptr;
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 3:
		{
			if (data)
			{
				data->PrintAllItems();
				solution = data->FullSearch();
				solution->PrintData();
				delete solution;

				solution = nullptr;
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 4:
		{
			if (data)
			{
				data->PrintAllItems();
				solution = data->GreedySolution(true);
				solution->PrintData();
				delete solution;

				solution = data->GreedySolution(false);
				solution->PrintData();
				delete solution;

				solution = nullptr;
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 5:
		{
			if (data)
			{
				data->PrintAllItems();
				solution = data->DynamicSolution();
				solution->PrintData();
				delete solution;

				solution = nullptr;
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 6:
		{
			if (!data)
			{
				delete data;
			}
			Start();
			return;
		}
		default:
		{
			if (!data)
			{
				delete data;
			}
			Start();
			return;
		}
		}
	} while (true);
}


std::string UI::ReadPath()
{
	std::string path;
	cout << "Podaj nazwe pliku: ";
	getline(cin, path);
	return path;
}

void UI::Start()
{
	do
	{
		switch (ShowMainMenu())
		{
		case 1:
		{
			TSPMenu();
			break;
		}
		case 2:
		{
			KnapsackMenu();
			break;
		}
		case 3:
		{
			exit(0);
			return;
		}
		default:
		{
			return;
		}
		}
	} while (true);
}

