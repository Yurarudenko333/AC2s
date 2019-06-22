#ifndef Hash_Functor_H
#define Hash_Functor_H
#include"Product.h"
#include"Branch.h"
class Product;
class Branch;
namespace MINE_STL
{
	size_t _FNV_offset_basis = 2166136261U;
	size_t _FNV_prime = 16777619U;

	template<class _Kty>
	size_t _Hash_representation(const _Kty& _Keyval)
	{	// bitwise hashes the representation of a key
		const unsigned char* const _First = 
			&reinterpret_cast<const unsigned char&>(_Keyval);
		const size_t _Count = sizeof(_Kty);
		size_t _Val = _FNV_offset_basis;
		for (size_t i = 0; i < _Count; ++i)
		{
			_Val ^= static_cast<size_t>(_First[i]);
			_Val *= _FNV_prime;
		}
		return _Val;
	}

	void hash_combine(size_t& seed, size_t value)
	{
		seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	template<class _Kty>
	struct Hasher
	{
		size_t operator()(const _Kty& _Keyval) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
			return (_Hash_representation(_Keyval));
		}
	};

	template<>
	size_t Hasher<Product>::operator()(const Product& _Keyval) const
	{
		size_t seed = 0;
		hash_combine(seed, _Hash_representation(_Keyval.name));
		hash_combine(seed, _Hash_representation(_Keyval.id));
		return seed;
	}

	template<>
	size_t Hasher<Branch>::operator()(const Branch& _Keyval) const
	{
		size_t seed = 0;
		hash_combine(seed, _Hash_representation(_Keyval.name));
		hash_combine(seed, _Hash_representation(_Keyval.id));
		return seed;
	}


	template <typename T>
	inline size_t get_hash_code(const T& value)
	{
		return Hasher<T>{}(value);
	}
};
#endif