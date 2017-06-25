#pragma once
#ifndef ARRAY_HEADER
#define ARRAY_HEADER


#include <string>
using namespace std;
template <class T>
class Array
{
private:
	int size;
	T* array;
	void addToBeginning(T x);
	void addToEnd(T x);

public:
	Array(int s = 0);
	Array(Array<T> & value);
	~Array();
	int GetSize();
	void Swap(int i, int j);
	void PrintData();
	void Add(T x, int index);
	T Get(int index);
	void Insert(T x, int index);
	void Delete(int index);
	bool Search(T value);

	Array<T> & operator=(Array<T> & value);
	int GetIndexOfMin(bool *  visited, int exclude);
	T & operator[](int i);
};



#endif

