#pragma once
#include <vector>

using namespace std;

/*MAX HEAP*/

template <class K>
class Queue
{
private:
	vector<K *> maxHeap;
	K *min;
	int LeftChild(int i) const;
	int RightChild(int i) const;
	int Parent(int i) const;

public:
	Queue(int size = 10);
	~Queue();
	void Insert(const K &elem);
	void PrintQueue() const;
	bool Empty() const;
	int Size() const;
	void BuildQueue(K **arr);
	void HeapifyDown(int i);
	K *FindMax();
	K *FindMin() const;
	K *ExtractMax();
};

template <class K>
Queue<K>::Queue(int size)
{
	maxHeap.reserve(size);
}

template <class K>
Queue<K>::~Queue()
{
	maxHeap.clear();
	delete min;
}

template <class K>
int Queue<K>::LeftChild(int i) const
{
	return 2 * i + 1;
}

template <class K>
int Queue<K>::RightChild(int i) const
{
	return 2 * i + 2;
}

template <class K>
int Queue<K>::Parent(int i) const
{
	return (i - 1) / 2;
}

template <class K>
void Queue<K>::Insert(const K &elem)
{
	if (maxHeap.empty())
	{
		K *newElem = new K(elem);
		maxHeap.emplace_back(newElem);
		min = newElem;
	}
	else
	{
		K *newElem = new K(elem);
		maxHeap.emplace_back(newElem);
		if (*min > elem)
		{
			min = newElem;
		}
		int sz = maxHeap.size() - 1;
		int parentIndex = Parent(sz);
		if ((*maxHeap[parentIndex] < *maxHeap[sz]))
		{
			while (*maxHeap[parentIndex] < *maxHeap[sz])
			{
				K *temp = maxHeap[sz];
				maxHeap[sz] = maxHeap[parentIndex];
				maxHeap[parentIndex] = temp;

				sz = parentIndex;
				parentIndex = Parent(sz);
			}
		}
	}
}

template <class K>
void Queue<K>::PrintQueue() const
{
	int sz = maxHeap.size();
	for (int i = 0; i < sz; i++)
	{
		cout << *maxHeap[i];
	}
}

template <class K>
bool Queue<K>::Empty() const
{
	return maxHeap.empty();
}

template <class K>
int Queue<K>::Size() const
{
	return maxHeap.size();
}

template <class K>
K *Queue<K>::FindMax()
{
	return maxHeap[0];
}

template <class K>
K *Queue<K>::FindMin() const
{
	return min;
}

template <class K>
void Queue<K>::HeapifyDown(int i)
{
	int left = LeftChild(i);
	int right = RightChild(i);
	int sz = this->Size() - 1;

	int high = i;
	if (left <= sz && *maxHeap[left] > *maxHeap[i])
	{
		high = left;
	}
	if (right <= sz && *maxHeap[right] > *maxHeap[high])
	{
		high = right;
	}
	if (high != i)
	{
		K *temp = maxHeap[high];
		maxHeap[high] = maxHeap[i];
		maxHeap[i] = temp;
		HeapifyDown(high);
	}
}

template <class K>
void Queue<K>::BuildQueue(K **arr)
{
	int sz = elems.size();
	if (!maxHeap.empty())
	{
		maxHeap.clear();
	}
	for (int i = 0; i < sz; i++)
	{
		maxHeap.push_back(arr[i]);
	}
	for (int i = sz / 2; i >= 0; i--)
	{
		HeapifyDown(i);
	}
}

template <class K>
K *Queue<K>::ExtractMax()
{
	K *max = this->FindMax();
	int sz = this->Size();
	if (Empty())
	{
		throw out_of_range("The heap is empty");
	}
	if (sz == 1)
	{
		maxHeap.pop_back();
		return max;
	}
	else
	{
		maxHeap[0] = maxHeap[sz - 1];
		maxHeap.pop_back();
		HeapifyDown(0);
		return max;
	}
}