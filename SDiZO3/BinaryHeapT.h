#pragma once
#include <string>

#ifndef BINARY_HEAPT_HEADER
#define BINARY_HEAPT_HEADER
class Edge;
template <class T>
class BinaryHeapT
{
private:
	T* array;
	int heapSize;
	int size;
	int getLeftChild(int index);
	int getRightChild(int index);
	int getParent(int index);
	void printBT(std::string sp, std::string sn, std::string cr, std::string cp, std::string cl, int v);		// Zrodlo: eduinf.waw.pl/inf/alg/001_search/0113.php
public:
	BinaryHeapT(int size = 0);
	~BinaryHeapT();
	void PrintData();
	inline void Add(T value);
	inline T GetFront();
	inline void Delete();
	inline bool Search(T value);
	inline int GetSize();
	inline int GetIndex(T item);
//	inline void DeleteFrom(int index);
};

class Item
{
private:

public:
	bool OrderByValue;
	int Index;
	int Value;
	int Weight;
	Item(bool useOnlyValue = true);
	Item(int value, int weight, int index);
	friend std::ostream& operator<<(std::ostream & s, const Item & edge);
	bool operator<(const Item & right);
	bool operator>(const Item & right);
	bool operator==(const Item & right);
	~Item();
};

#endif
