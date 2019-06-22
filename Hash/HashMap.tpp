namespace MINE_STL {
	template<class K, class V, class H>
	int Map<K,V,H>::getBucketIndex(const K &key)
	{
		int hash = getHash(key);
		int index = abs(hash) % numBuckets;
		return index;
	}
	template<class K, class V, class H>
	Map<K, V, H>::Map()
	{
		numBuckets = 10;
		size = 0;
		bucketArray = new HashNode<K, V>*[numBuckets];

		for (int i = 0; i < numBuckets; ++i)
			bucketArray[i] = nullptr;
	}

	template<class K, class V, class H>
	Map<K,V,H>::~Map()
	{
		for (int i = 0; i < size; ++i)
		{
			auto cur = bucketArray[i];
			while (cur != nullptr)
			{
				auto nextNode = cur->pNext;
				delete cur;
				cur = nextNode;
			}
		}
	}
};