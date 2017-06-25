#pragma once
#include "Array.h"
#include "BinaryHeapT.h"
#ifndef MATRIX_HEADER
#define MATRIX_HEADER
class Matrix
{
private:
	Array<int>** matrix;
	int edges;
	int vertexes;
	bool directed;
public:
	Matrix(int ver);											//Rezerwuje miejsce dla macierzy, wywoluje konstruktor klasy Array
	void InsertEdge(int start, int end, int val);						//Wstawia krawedz do podanego miejsca w grafie
//	Edge GetEdge(int start, int end);

	void PrintData();

	Array<int>* GetRow(int index);
	int GetEdges();
	int GetVertexes();
	static Matrix* ReadDataFromFile(std::string path);
	~Matrix();

};
#endif#pragma once
