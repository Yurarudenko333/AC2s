#pragma once

namespace MINE_STL {
	template<class K, class V, class Hasher>
	class Map;
}

namespace MINE_STL {
	template<class K, class V>
	class HashNode
	{
	private:
		K key;
		V value;

		// Reference to next node 
		HashNode<K, V> *pNext;
		template<class K, class V, class Hasher>
		friend class Map;

		// Constructor 
		HashNode(const K &key, const V &value)
		{
			this->key = key;
			this->value = value;
		}
	};
}