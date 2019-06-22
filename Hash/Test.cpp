#include "Test.h"
#include"HashMap.h"
#include"Hasher.h"
#include<iostream>
#include<fstream>
using std::cout;
using std::ofstream;
using MINE_STL::Hasher;
using MINE_STL::Map;


namespace TestOnly {
#pragma region Products,Branches declaration
	Product p9, p10, p11, p12, p13;
	Product p1 = {
		"Calvin Klein", "Logo Hoodie Sweatshirt", (int)Product::ProductCondition::New,
		79.5,"72% Cotton, 28% Polyester"
	};
	Product p2 = {
		"Marshall", "Mid Wireless On-Ear Headphone", 2,
		79.99, "Driver impedance 32 ohm. Driver sensitivity 95 db spl. Frequency response 10 hz to 20 khz"
	};
	Product p3 = {
		"Columbia", "North Protection Hooded Jacket", 1,
		180.33, "Collegiate Navy/Night Tide, X-Large"
	};
	Product p4 = {
		"LEE", "Modern Series Jean", 0, 15.65,
		"Slim-fit Tapered-Leg Jean, Fletch, 34W x 34L"
	};
	Product p5 = {
		"Timberland", "Classic 2-Eye Boat Shoe", 1, 95.34,
		"100% Leather, Men's Shoe, Rootbeer/Brown, 11 M"
	};
	Product p6 = {
		"Acer", "Predator Helios 300 Gaming Laptop", 2, 755,
		"15.6,Full HD IPS, Intel i7 - 7700HQ CPU, 16GB DDR4 RAM, 256GB SSD, GeForce \
GTX 1060 - 6GB, VR Ready, Windows 10 64 - bit, G3 - 571 - 77QK"
	};
	Product p7 = {
		"Senheiser", "HD 599 Open Back Headphone", 1, 184.72,
		"Around-Ear, Open Back, 50 Ω, 12 – 38,500 Hz, 106 dB (1 kHz / 1 Vrms)"
	};
	Product p8 = {
		"Optimum Nutrition", "Gold Standard 100% Whey Protein Powder",1,57.87,
		"Double Rich Chocolate, 5 Pound"
	};

	Branch b1 = { "Discounts", {&p5,&p8,&p9} };
	Branch b2 = { "Clothes", {&p1,&p3,&p4} };
	Branch b3 = { "Electronics", {&p2,&p6,&p7} };
	Branch b4 = { "Default", {&p10,&p11,&p12,&p13} };
#pragma endregion

	void Tester::TestingMap1()
	{
		cout << "-----Testing on Product->int data types-----\n";
		Map<Product, int, Hasher<Product>> mp;

		mp.insert(p1, 2);
		mp.insert(p2, 4);
		mp.insert(p3, 5);
		mp.insert(p4, 7);
		mp.show();
		mp.remove(p3);
		mp.remove(p4);
		mp.remove(p11);
		mp.show();
		mp.insert(p5, -1);
		mp.insert(p6, -1);
		mp.insert(p7, 3);
		mp.insert(p7, 33);
		mp.insert(p8, -1);
		mp.insert(p9, -1);
		mp.show();
		mp.insert(p10, -1);
		mp.insert(p11, -1);
		mp.insert(p12, -1);
		mp.insert(p13, -1);
		mp.show();

		cout << mp.get(p7) << "\n";
	}
	void Tester::VizualizeTest1(const char*name)
	{
		ofstream fout("Output\\" + std::string(name));

		Map<Product, int, Hasher<Product>> mp;

		mp.insert(p1, 2);
		mp.insert(p2, 4);
		mp.insert(p3, 5);
		mp.insert(p4, 7);
		mp.insert(p5, -1);
		mp.insert(p6, -1);
		mp.insert(p7, 3);
		mp.insert(p7, 33);
		mp.insert(p8, -1);
		mp.insert(p9, -1);
		mp.insert(p10, -1);
		mp.insert(p11, -1);
		mp.insert(p12, -1);
		mp.insert(p13, -1);

		mp.PrintForViz(fout);
		fout.close();
	}
}
