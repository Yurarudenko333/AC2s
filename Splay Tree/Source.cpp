//#include"Splay_Tree/Splay_Tree.h"
#include"Splay_Tree\Splay_Tree.h"
#include"MyType\Food_object.h"
#include<iostream>
using std::cout;

void TestINT();
void TestMyType();
int main()
{
	TestINT();
	TestMyType();
	system("pause");
	return 0;
}
void TestINT()
{
	Splay_Tree<int,int> node1;

	node1.Insert({ 100,100 });
	node1.Insert({ 50,50 });
	node1.Insert({ 200,200 });
	node1.Insert({ 40,40 });
	node1.Insert({ 30,30 });
	node1.Insert({ 20,20 });

	cout << "After insertion of 100,50,200,40,30,20 the Splay tree is\n";
	node1.Print();
	node1.PrintForViz("Output/IntTest/0BeginState.gv");

	node1.Delete(50);
	cout << "After deletion of 50 the Splay tree is\n";
	node1.Print();
	node1.PrintForViz("Output/IntTest/1AfterDelete50.gv");

	node1.Insert({ 80,80 });
	cout << "After insertion of 80 the Splay tree is\n";
	node1.Print();
	node1.PrintForViz("Output/IntTest/2AfterInsert80.gv");

	node1.Delete(34);
	cout << "After deletion of 34(not present) the Splay tree is\n";
	node1.Print();
	node1.PrintForViz("Output/IntTest/3AfterDelete34.gv");

	node1.Search(200);
	cout << "After search of 200(is present) the Splay tree is\n";
	node1.Print();
	node1.PrintForViz("Output/IntTest/4AfterSearch200.gv");

	node1.Search(56);
	cout << "After search of 56(not present) the Splay tree is\n";
	node1.Print();
	node1.PrintForViz("Output/IntTest/5AfterSearch56.gv");
}

void TestMyType()
{
	Splay_Tree<double, Food::Food_object> node1;
	auto data = Food::get_data();
	for (auto& value : data)
	{
		node1.Insert(value);
	}
	//node1.Print();
	node1.PrintForViz("Output/MyTypeTest/0BeginState.gv");

	node1.Insert({ 4.25, Food::Food_object{"tomato", 12, 4.25, &Food::vegetables } });
	node1.PrintForViz("Output/MyTypeTest/1InsertedTomato.gv");

	node1.Delete(12.0);
	node1.PrintForViz("Output/MyTypeTest/2AfterDelete12.gv");

	node1.Delete(5.0);
	//5.0 key is not present
	node1.PrintForViz("Output/MyTypeTest/3AfterDelete5.gv");

	node1.Search(3.5);
	//3.5 key is not present
	node1.PrintForViz("Output/MyTypeTest/4Search3.5.gv");

	node1.Search(10.0);
	node1.PrintForViz("Output/MyTypeTest/5Search10.gv");
}
