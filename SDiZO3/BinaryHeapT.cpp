#include "BinaryHeapT.h"
#include <iostream>
#include <iomanip>
using namespace std;

template class BinaryHeapT<int>;
template class BinaryHeapT<Item>;

template <class T>
int BinaryHeapT<T>::getLeftChild(int index)
{
	int result = 2 * index + 1;
	return result;
}

template <class T>
int BinaryHeapT<T>::getRightChild(int index)
{
	int result = 2 * index + 2;
	return result;
}

template <class T>
int BinaryHeapT<T>::getParent(int index)
{
	int result = (index - 1) / 2;

	return result;
}

template <class T>
void BinaryHeapT<T>::printBT(std::string sp, std::string sn, std::string cr, std::string cp, std::string cl, int v)
{
	string s;

	if (v < heapSize)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printBT(s + cp, cr, cr, cp, cl, 2 * v + 2);

		s = s.substr(0, sp.length() - 2);

		//	cout << s << sn << array[v].Start << ":" << array[v].End << "-" << array[v].Weight << endl;
		cout << s << sn << array[v] << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printBT(s + cp, cl, cr, cp, cl, 2 * v + 1);
	}
}

template <class T>
BinaryHeapT<T>::BinaryHeapT(int size)
{
	array = new T[size];
	this->size = size;
	heapSize = 0;
}

template <class T>
BinaryHeapT<T>::~BinaryHeapT()
{
	delete[] array;
}

template <class T>
void BinaryHeapT<T>::PrintData()
{
	string cr, cl, cp;

	for (int i = 0; i < heapSize; i++)
	{
		cout << setw(8) << array[i];
	}
	cout << endl;

	cr = cl = cp = "  ";
	//cr = "┌─";
	//cl = "└─";
	//cp = "│ ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	printBT("", "", cr, cp, cl, 0);
}

template <class T>
void BinaryHeapT<T>::Add(T item)
{
	if (heapSize == size)
	{
		T* temp = new T[heapSize + 1];
		for (int i = 0; i < heapSize; i++)
		{
			temp[i] = array[i];
		}
		delete[] array;
		array = temp;
		size++;
	}

	int parent;
	int index = heapSize;
	parent = getParent(index);

	while (index > 0 && array[parent] < item)
	{
		array[index] = array[parent];
		index = parent;
		parent = getParent(index);
	}

	array[index] = item;

	heapSize++;
}

template <class T>
T BinaryHeapT<T>::GetFront()
{
	if (heapSize >= 1 && size >= 1)
		return array[0];

	return T();
}

template <class T>
void BinaryHeapT<T>::Delete()
{
	if (heapSize)
	{
		int index = 0;																				  //Zawsze bedziemy usuwac 1 element
		T item;
		int child;
		heapSize--;
		array[0] = array[heapSize];

		child = getLeftChild(index);
		item = array[0];
		while (child < heapSize)
		{
			if (child + 1 < heapSize && array[child + 1]> array[child])								// Wybor wiekszego dziecka
			{
				child++;
			}
			if (item > array[child])																//Czy wartosc juz jest w dobrym miejscu
			{
				break;
			}
			array[index] = array[child];															//Jesli nie to przejscie w dol
			index = child;
			child = getLeftChild(index);
		}
		array[index] = item;
	}

}

template <class T>
bool BinaryHeapT<T>::Search(T value)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == value)
			return true;
	}
	return false;
}

template <class T>
int BinaryHeapT<T>::GetSize()
{
	return heapSize;
}

template <class T>
int BinaryHeapT<T>::GetIndex(T item)
{
	for (int i = 0; i < heapSize; i++)
	{
		if (item == array[i])
			return i;
	}
	return -1;
}

//template <class T>
//void BinaryHeapT<T>::DeleteFrom(int index)
//{
//
//	if (heapSize)
//	{
//		heapSize--;
//		array[index] = array[heapSize];
//		T item = array[index];
//
//		if (item > array[getParent(index)])
//		{
//			int child = getLeftChild(index);
//			while (child < heapSize)
//			{
//				if (child + 1 < heapSize && array[child + 1]< array[child])								// Wybor wiekszego dziecka
//				{
//					child++;
//				}
//				if (item < array[child])																//Czy wartosc juz jest w dobrym miejscu
//				{
//					break;
//				}
//				array[index] = array[child];															//Jesli nie to przejscie w dol
//				index = child;
//				child = getLeftChild(index);
//			}
//			array[index] = item;
//		}
//		else
//		{
//			int parent;
//			parent = getParent(index);
//			while (index > 0 && array[parent] > item)
//			{
//				array[index] = array[parent];
//				index = parent;
//				parent = getParent(index);
//			}
//			array[index] = item;
//		}
//
//	}
//
//}


Item::Item(bool useOnlyValue)
{
	Value = 0;
	Weight = 0;
	Index = -1;
	OrderByValue = useOnlyValue;
}

Item::Item(int value, int weight, int index)
{
	Value = value;
	Weight = weight;
	Index = index;
}

bool Item::operator<(const Item& right)
{
	if(OrderByValue)
	{
		if ((this->Value) < (right.Value))
			return true;
		 return false;
	}
	if( this->Value/static_cast<double>(this->Weight) < right.Value /static_cast<double>(right.Weight) ) 
	{
		return true;
	}
	return false;

}

bool Item::operator>(const Item& right)
{
	if (OrderByValue)
	{
		if ((this->Value) > (right.Value))
			return true;
		return false;
	}
	if (this->Value / static_cast<double>(this->Weight) > right.Value / static_cast<double>(right.Weight))
	{
		return true;
	}
	return false;
}

bool Item::operator==(const Item& right)
{
	if (OrderByValue)
	{
		if ((this->Value) == (right.Value))
			return true;
		return false;
	}
	if (this->Value / static_cast<double>(this->Weight) == right.Value / static_cast<double>(right.Weight))
	{
		return true;
	}
	return false;
}

Item::~Item()
{
	
}


std::ostream& operator<<(std::ostream& s, const Item& item)
{
	 s << item.Value << ":" << (item.Weight);
	if(!item.OrderByValue)
	{
		s << ":" <<  item.Value / static_cast<double>(item.Weight);
	}
	 return s;
}
