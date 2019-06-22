#pragma once
#include"HashNode.h"
#include<iostream>
#include<cstring>
#include<cstdio>
using std::cout;

#include<fstream>
using std::ofstream;
using std::string;
namespace MINE_STL 
{
	template<class K, class V, class H>
	class Map
	{
	private:
		H getHash;
		HashNode<K, V> **bucketArray;
		// Current capacity of array list 
		int numBuckets;

		// Current size of array list 
		int size;
		int getBucketIndex(const K &key);
		void _Rehash()
		{
			HashNode<K, V> **temp = bucketArray;

			size = 0;
			numBuckets = 2 * numBuckets;
			bucketArray = new HashNode<K, V> *[numBuckets];

			for (int i = 0; i < numBuckets; ++i)
				bucketArray[i] = nullptr;

			for (int i = 0; i < numBuckets / 2; ++i)
			{
				auto headNode = temp[i];
				while (headNode != nullptr)
				{
					insert(headNode->key, headNode->value);
					headNode = headNode->pNext;
				}
			}
		}
	public:
		Map();
		~Map();

		int Size() { return size; }
		bool isEmpty() { return size == 0; }

		void PrintForViz(ofstream& fout)
		{
			fout << "digraph{\nrankdir=LR;\nsubgraph steps{\nrank = same;\n";
			bool foundNotEmpty = false;
			for (int i = 0; i < numBuckets; ++i)
			{
				auto elem = bucketArray[i];
				if (elem && !foundNotEmpty)
				{
					foundNotEmpty = true;
					fout << "item" << i;
				}
				else if (elem)
					fout << "->item" << i;
			}
			fout << "}\n";
			for (int i = 0; i < numBuckets; ++i)
			{
				auto elem = bucketArray[i];
				if (elem)
				{
					fout << "subgraph cluster" << i << " {node[style = filled];";
					fout << "label=\"process #" << i << "\";color = blue;\n";
					int counter = 0;
					while (elem)
					{
						fout << "\"node" << i << "." << counter++ << "\"[label=\"";
						fout << elem->key << ";shape=record];\n";
						elem = elem->pNext;
					}
					counter = 0;
					elem = bucketArray[i];
					fout << "\"node" << i << "." << counter++ << "\":p";
					while (elem->pNext)
					{
						fout << "->\"node" << i << "." << counter++ << "\":p";
						elem = elem->pNext;
					}
					fout << "}\n";
					fout << "item" << i << "->\"node" << i << ".0\":p\n";
				}
			}
			fout << "}}";

		}
		void show()
		{
			printf("%s=%d <=> max_size=%d\n", "size", size, numBuckets);
			for (int i = 0; i < numBuckets; ++i)
			{
				cout << i << ": ";
				auto elem = bucketArray[i];
				if (elem)
				{
					while (elem)
					{
						cout << elem->key << "->";
						cout << elem->value << ", ";
						elem = elem->pNext;
					}
				}
				cout << ";\n";
			}
		}

		V remove(const K &key)
		{
			// Apply hash function to find index for given key 
			int bucketIndex = getBucketIndex(key);

			// Get head of chain 
			HashNode<K, V> *head = bucketArray[bucketIndex];

			// Search for key in its chain 
			HashNode<K, V> *prev = nullptr;
			while (head != nullptr)
			{
				// If Key found 
				if (head->key == key)
					break;

				// Else keep moving in chain 
				prev = head;
				head = head->pNext;
			}

			// If key was not there 
			if (head == nullptr)
				return -1;

			// Reduce size 
			--size;


			int returnData = head->value;
			// Remove key 
			if (prev != nullptr)
				prev->pNext = head->pNext;
			else
				bucketArray[bucketIndex] = head->pNext;

			delete head;
			return returnData;//head->value;
		}

		//Returns value for a key 
		V get(const K &key)
		{
			// Find head of chain for given key 
			int bucketIndex = getBucketIndex(key);
			HashNode<K, V> *head = bucketArray[bucketIndex];

			// Search key in chain 
			while (head != nullptr)
			{
				if (head->key == key)
					return head->value;
				head = head->pNext;
			}

			// If key not found
			return -1;
		}

		// Adds a key value pair to hash 
		void insert(const K &key, const V &value)
		{
			// Find head of chain for given key 
			int bucketIndex = getBucketIndex(key);
			HashNode<K, V> *head = bucketArray[bucketIndex];

			// Check if key is already present 
			while (head != nullptr)
			{
				if (head->key == key)
				{
					head->value = value;
					return;
				}
				head = head->pNext;
			}

			// Insert key in chain 
			size++;
			head = bucketArray[bucketIndex];
			HashNode<K, V> *newNode = new HashNode<K, V>(key, value);
			newNode->pNext = head;
			bucketArray[bucketIndex] = newNode;

			// If load factor goes beyond threshold, then 
			// double hash table size 
			if ((1.0*size) / numBuckets >= 0.7)
			{
				_Rehash();
			}
		}
	};
};

#include"HashMap.tpp"