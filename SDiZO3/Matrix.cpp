#include "Matrix.h"
#include <iostream>
#include <fstream>
#include "HelperMethods.h"
#include <iomanip>


using namespace std;

int Matrix::GetEdges()
{
	return edges;
}

int Matrix::GetVertexes()
{
	return vertexes;
}

/*Edge Matrix::GetEdge(int start, int end)
{
	int weight;
	Edge* edge = new Edge();
	if (start < vertexes && end < vertexes)
	{
		weight = matrix[start]->Get(end);
	}
	edge->Start = start;
	edge->End = end;
	edge->Weight = weight;

	return *edge;
}*/

void Matrix::PrintData()
{
	cout << setw(7) << " ";
	for (int i = 0; i < vertexes; i++)
	{
		cout << setw(7) << i;
	}
	cout << endl << endl;
	for (int i = 0; i < vertexes; i++)
	{
		cout << setw(7) << i;
		matrix[i]->PrintData();
	}
	cout << endl << endl;
}

Array<int>* Matrix::GetRow(int index)
{
	if (index < vertexes)
		return matrix[index];
}

void Matrix::InsertEdge(int start, int end, int val)
{
	if (start < vertexes && end < vertexes)
	{
		matrix[start]->Insert(val, end);
	}
	if (!directed)
	{
		matrix[end]->Insert(val, start);
	}
}

Matrix::Matrix(int ver)
{
	directed = false;
	edges = ver * (ver - 1);
	vertexes = ver;
	matrix = new Array<int>*[ver];

	for (int i = 0; i < ver; i++)
	{
		matrix[i] = new Array<int>(ver);
	}

}

Matrix* Matrix::ReadDataFromFile(std::string path)
{
	Matrix* data = nullptr;
	int temp;
	ifstream file;
	int tab[4];
	file.open(path.c_str());
	if (file.is_open())
	{
		if (file >> temp)
		{
			data = new Matrix(temp);
			data->directed = true;
			for (int i = 0;  i < data->GetVertexes(); i++)
			{
				for(int j = 0; j < data->GetVertexes(); j++)
				{
						file >> temp;
						data->InsertEdge(i, j, temp);
					if(cin.bad())
					{
						cout << "File error - READ WEIGHT" << endl;
						break;
					}
				}
			}

		}
		else cout << "File error - READ INFO" << endl;
		file.close();
	}
	else
		cout << "File error - OPEN" << endl;

	return data;
}

Matrix::~Matrix()
{
	for (int i = 0; i < vertexes; i++)
	{
		delete matrix[i];
	}
	delete[] matrix;
}
