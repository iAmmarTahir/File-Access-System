#pragma once
#include <vector>
#include <functional>
#include <list>

using namespace std;

template <class K, class T>
class HashTable
{
private:
	vector<list<T *>> table;
	int currentSize;

public:
	HashTable(int size = 11);
	~HashTable();
	void clear();
	bool Find(const K &key, T *&elem);
	bool IsPresent(const K &key);
	bool Insert(const K &key, T *elem);
	bool Delete(const K &key);
	int hash(const K &key);
	void resize(const int &sz);
	void print() const;
};

template <class K, class T>
HashTable<K, T>::HashTable(int size)
{
	table.resize(size);
	currentSize = 0;
}

template <class K, class T>
void HashTable<K, T>::print() const
{
	if (currentSize == 0)
	{
		cout << "Hash table is empty\n";
		return;
	}
	else
	{
		int sz = table.size();
		int a = 1;
		for (int i = 0; i < sz; i++)
		{
			if (!table[i].empty())
			{
				for (auto &ite = table[i].begin(); ite != table[i].end(); ite++)
				{
					cout << "H" << a << "->" << *(*ite);
				}
				a++;
			}
		}
	}
}

template <class K, class T>
void HashTable<K, T>::resize(const int &sz)
{
	table.resize(sz);
	currentSize = 0;
}

template <class K, class T>
bool HashTable<K, T>::Find(const K &key, T *&elem)
{
	int hashedKey = hash(key);
	if (!table[hashedKey].empty())
	{
		for (auto &ite = table[hashedKey].begin(); ite != table[hashedKey].end(); ite++)
		{
			if (*(*ite) == key)
			{
				elem = *ite;
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

template <class K, class T>
HashTable<K, T>::~HashTable()
{
	table.clear();
}

template <class K, class T>
int HashTable<K, T>::hash(const K &key)
{
	std::hash<K> h;
	int sz = table.size();
	return h(key) % sz;
}

template <class K, class T>
bool HashTable<K, T>::Insert(const K &key, T *elem)
{
	int hashedKey = hash(key);
	table[hashedKey].push_back(elem);
	currentSize++;
	return true;
}

template <class K, class T>
bool HashTable<K, T>::Delete(const K &key)
{
	int hashedKey = hash(key);
	if (!table[hashedKey].empty())
	{
		for (auto &ite = table[hashedKey].begin(); ite != table[hashedKey].end(); ite++)
		{
			if (*(*ite) == key)
			{
				table[hashedKey].erase(ite);
				currentSize--;
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

template <class K, class T>
void HashTable<K, T>::clear()
{
	if (currentSize != 0)
		table.clear();
}

template <class K, class T>
bool HashTable<K, T>::IsPresent(const K &key)
{
	int hashedKey = hash(key);
	if (!table[hashedKey].empty())
	{
		for (auto &ite = table[hashedKey].begin(); ite != table[hashedKey].end(); ite++)
		{
			if (*(*ite) == key)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}