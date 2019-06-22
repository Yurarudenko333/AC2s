#include"Food_object.h"
#include <sstream>
namespace Food {
	vector<Food_object> vegetables;
	vector<Food_object> fruits;
	vector<Food_object> pastry;
	std::ostream & Food::operator<<(std::ostream & os, const Food_object & obj)
	{
		os << &obj << "|pr:" << obj.price << "|" << obj.name << "|num:" << obj.number_of_objects;
		if (obj.category == &vegetables)
			os << "|vegetables";
		else if (obj.category == &fruits)
			os << "|fruits";
		else if (obj.category == &pastry)
			os << "|pastry";
		return os;
	}

	vector<std::pair<double, Food_object>> Food::get_data()
	{
		vector<std::pair<double, Food_object>> result;
		std::ifstream file("Products.txt");
		if (!file)
		{
			std::cerr << "Could not open the file!" << std::endl;
			return result;
		}
		else {

			string str;
			Food_object food;
			while (std::getline(file, str))
			{
				string name;
				int number_of_objects;
				double price;
				string category;
				{
					std::istringstream iss(str);
					iss >> name >> number_of_objects >> price >> category;
				}
				food.name = name;
				food.number_of_objects = number_of_objects;
				food.price = price;
				if (category == "vegetables")
				{
					vegetables.push_back(food);
					food.category = &vegetables;
				}
				else if (category == "fruits")
				{
					fruits.push_back(food);
					food.category = &fruits;
				}
				else if (category == "pastry")
				{
					pastry.push_back(food);
					food.category = &pastry;
				}

				result.push_back(std::make_pair(price, food));
			}

			file.close();

			return result;
		}
	}
}