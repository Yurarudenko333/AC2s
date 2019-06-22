#pragma once
#include<ostream>
#include<fstream>

namespace MINE_STL
{
	template<class T>
	struct Hasher;
}

class Product
{
public:
	enum class ProductCondition : int {
		Used, New, Refurbished
	};
private:
	static int amount;
	friend class Branch;
	friend struct MINE_STL::Hasher<Product>;
	Branch* department;

	const char *name;
	const char *brand;
	double price; //in USD
	const char *desription;
	ProductCondition condition;
	size_t id;

	int quantity;
	double rating;
public:
	Product();
	Product(const char* brand, const char* name, int condition, double price,
		const char *description);
	Product(const Product& obj);
	friend std::ostream& operator <<(std::ostream& os, const Product& obj);
	friend std::ofstream& operator <<(std::ofstream& fout, const Product& obj);
	bool operator ==(const Product& obj);
	~Product();
};

