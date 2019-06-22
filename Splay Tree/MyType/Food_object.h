#ifndef FOOD_OBJECT_H_
#define FOOD_OBJECT_H_
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
using std::vector;
using std::string;
namespace Food {
	struct Food_object
	{
		string name;
		int number_of_objects;
		double price;
		vector<Food_object>* category;
		friend std::ostream& operator <<(std::ostream& os, const Food_object& obj);
	};
	extern vector<Food_object> vegetables;
	extern vector<Food_object> fruits;
	extern vector<Food_object> pastry;
	vector<std::pair<double, Food_object>> get_data();
}

#endif // FOOD_OBJECT_H_