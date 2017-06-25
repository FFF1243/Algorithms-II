#include "Array.h"
#include <iostream>
#include <iomanip>
#include "BinaryHeapT.h"
using namespace std;

template class Array<Item>;
template class Array<int>;
template <class T>
void Array<T>::addToBeginning(T value)
{
	size++;
	T *temp = new T[size];
	temp[0] = value;
	for (int i = 1; i < size; i++)
	{
		temp[i] = array[i - 1];
	}
	delete[] array;
	array = temp;
}
template <class T>
void Array<T>::addToEnd(T value)
{
	size++;
	T* temp = new T[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = array[i];
	}
	temp[size - 1] = value;
	delete[] array;
	array = temp;
}



template <class T>
Array<T>::Array(int s)
{
	size = s > 0 ? s : 0;
	array = new T[size];
}

template <class T>
Array<T>::Array(Array<T>& value)
{
	size = value.size;
	array = new T[size];
		for (int i = 0; i < size; i++)
		{
			array[i] = value.array[i];
		}
}

template <class T>
Array<T>::~Array()
{
	delete[] array;
	array = nullptr;
}
template <class T>
int Array<T>::GetSize()
{
	return size;
}

template <class T>
void Array<T>::Swap(int i, int j)
{
	if (i > size || j > size)
		return;

	T temp = array[j];
	array[j] = array[i];
	array[i] = temp;
}

template <class T>
void Array<T>::PrintData()
{
	if (size == 0)
	{
		cout << "Nie ma zadnych elementow w strukturze" << endl;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			cout << setw(7) << array[i];
		}
		cout << endl;
	}
}
template <class T>
void Array<T>::Add(T value, int index)
{
	if (index == size - 1)
	{
		addToEnd(value);
	}
	else if (index == 0)
	{
		addToBeginning(value);
	}
	else
	{
		size++;
		T* temp = new T[size];
		for (int i = 0; i < index; i++)
		{
			temp[i] = array[i];
		}
		temp[index] = value;
		for (int i = index + 1; i < size; i++)
		{
			temp[i] = array[i - 1];
		}
		delete[] array;
		array = temp;
	}
}

template <class T>
T Array<T>::Get(int index)
{
	if (index < size)
	{
		return array[index];
	}
	return T();
}

template <class T>
void Array<T>::Insert(T x, int index)
{
	if (index < size)
	{
		array[index] = x;
	}
}

template <class T>
void Array<T>::Delete(int index)
{
	size--;
	T* temp = new T[size];
	for (int i = 0; i < index; i++)
	{
		temp[i] = array[i];
	}
	for (int i = index; i < size; i++)
	{
		temp[i] = array[i + 1];
	}
	delete[] array;
	array = temp;
}
template <class T>
bool Array<T>::Search(T value)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == value)
		{
			return true;
		}
	}
	return false;
}

template <class T>
Array<T>& Array<T>::operator=(Array<T>& value)
{
	if(this != &value)
	{
		size = value.size;
		array = new T[size];
		for (int i = 0; i < size; i++)
		{
			array[i] = value.array[i];
		}
	}

	return *this;
}

template <class T>
int Array<T>::GetIndexOfMin(bool * visited, int exclude)
{
	//for (int i = 0; i < size; i++)
	//{
	//	cout << visited[i] << " ";
	//}
	//cout << endl;
	int mini;
	for(int i = 0; i < size; i++)
	{
		if(!visited[i] && i != exclude)
		{
			mini = i;
			break;
		}
	}

	for (int i = mini + 1; i < size; i++)
	{
		if (array[i] < array[mini] && !visited[i] && i != exclude)
			mini = i;
	}
	return mini;
}


template <class T>
T& Array<T>::operator[](int i)
{
	return array[i];
}
