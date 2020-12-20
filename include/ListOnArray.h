#pragma once
#include <iostream>

using namespace std;

template<class T1>
class ListOnArray;

template<class T2>
class ListOnArrayIterator
{
private:
	ListOnArray<T2>& link;
	int index;
public:
	ListOnArrayIterator(ListOnArray<T2>& _v, int _index = -1) :link(_v), index(_index) {}
	ListOnArrayIterator(ListOnArrayIterator& _v) :link(_v.link), index(_v.index) {}

	ListOnArrayIterator& operator =(const ListOnArrayIterator& _lhs)
	{
		index = _lhs.index;
		return(*this);
	}
	ListOnArrayIterator operator ++(int)
	{
		if (index != -1)
			index = link.links[index];
		return (*this);
	}

	T2& operator *()
	{
		if (this->index == -1)
			throw logic_error("end");
		return(link.data[index]);
	}
};

template<class T1>
class ListOnArray
{
private:
	T1* data;
	int* links;

	int root;
	int Size;
	int DataCount;

public:
	ListOnArray(int _size = 1);
	ListOnArray(ListOnArray& _list);
	~ListOnArray();

	bool IsEmpty() { return(root == -1); }
	bool IsFull() { return(DataCount == Size); }
	int GetSize() { return Size; }
	int GetCount() { return DataCount; }

	ListOnArrayIterator<T1> begin()
	{
		return ListOnArrayIterator<T1>(*this, root);
	}

	template<class T2>
	friend class ListOnArrayIterator;

	T1& operator[](const int index);
	void push_back(T1 value);
	void push_front(T1 value);
	T1 pop_front();
	T1 pop_back();

	template<class T2>
	friend ostream& operator << (ostream& ostr, ListOnArray<T2>& _l);
};

template<class T2>
ostream& operator<<(ostream& ostr, ListOnArray<T2>& _l)
{
	ListOnArrayIterator<int> k = _l.begin();
	for (int i = 0; i < _l.GetCount(); i++)
	{
		ostr << *k << " ";
		k++;
	}
	return ostr;
}

template<class T1>
ListOnArray<T1>::ListOnArray(int _size)
{
	Size = _size;
	DataCount = 0;

	data = new T1[_size];
	links = new int[_size];

	for (int i = 0; i < _size; i++)
		links[i] = -2;

	root = -1;
}

template<class T1>
ListOnArray<T1>::ListOnArray(ListOnArray& _list)
{
	data = new T1[_list.Size];
	links = new int[_list.Size];

	root = _list.root;
	for (int i = 0; i < _list.Size; i++)
		links[i] = _list.links[i];

	while (root != -1)
	{
		data[root] = _list.data[root];
		root = _list.links[root];
	}
	root = _list.root;
	Size = _list.Size;
	DataCount = _list.DataCount;
}

template<class T1>
ListOnArray<T1>::~ListOnArray()
{
	root = 0;
	Size = 0;
	DataCount = 0;
	if (links != nullptr)
		delete[] links;
	if (data != nullptr)
		delete[] data;
}

template<class T1>
inline T1& ListOnArray<T1>::operator[](const int index)
{
	if (index < 0 || index >= DataCount)
		throw - 1;

	int counter = 0;
	int temp = root;

	while (temp != -1)
	{
		if (counter == index)
			return this->data[temp];
		temp = this->links[temp];
		counter++;
	}
}

template<class T1>
void ListOnArray<T1>::push_back(T1 value)
{
	if (IsFull())
		throw - 1;

	if (IsEmpty())
	{
		root = 0;
		data[0] = value;
		links[0] = -1;
		DataCount++;
	}
	else
	{
		int k = 0;
		while (links[k] != -2)
			k++;

		int j = root;
		while (links[j] != -1)
			j = links[j];

		data[k] = value;
		links[j] = k;
		links[k] = -1;

		DataCount++;
	}

}

template<class T1>
void ListOnArray<T1>::push_front(T1 value)
{
	if (IsFull())
		throw - 1;

	if (IsEmpty())
	{
		root = 0;
		data[0] = value;
		links[0] = -1;
		DataCount++;
	}
	else
	{
		int current = 0;
		while (links[current] != -2)
			current++;

		data[current] = value;
		links[current] = root;
		root = current;
		DataCount++;
	}
}

template<class T1>
T1 ListOnArray<T1>::pop_front()
{
	if (IsEmpty())
		throw - 1;

	T1 temp = data[root];
	int current = links[root];

	links[root] = -2;
	root = current;
	DataCount--;

	return temp;
}

template<class T1>
T1 ListOnArray<T1>::pop_back()
{
	if (IsEmpty())
		throw - 1;

	T1 temp;

	if (links[root] == -1)
	{
		temp = data[root];
		links[root] = -2;
		root = -1;
	}
	else
	{
		int last = root;
		int previous = 0;
		for (int i = 0; i < DataCount; i++)
			if (links[last] != -1)
			{
				previous = last;
				last = links[last];
			}
			else
			{
				temp = data[last];
				links[last] = -2;
				links[previous] = -1;
			}
	}
	DataCount--;
	return temp;
}
