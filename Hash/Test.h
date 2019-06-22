#pragma once
#include"Product.h"
#include"Branch.h"
namespace TestOnly
{
	extern Product p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;
	extern Branch b1, b2, b3, b4;
	class Tester
	{
	private:
	public:
		static void TestingMap1();
		static void VizualizeTest1(const char* name);
	};
}