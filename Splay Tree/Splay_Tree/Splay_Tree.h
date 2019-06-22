#pragma once
#include"..\MyType\Food_object.h"
#include<fstream>
#include<string>
#include<utility>
using std::pair;
using std::string;
using std::ofstream;
template<typename T, typename _Val>
struct SplayNode
{
	T key;
	_Val value;
	SplayNode *left, *right;
	SplayNode(const T &key, const _Val& value)
	{
		this->key = key;
		this->value = value;
		left = right = nullptr;
	}
	SplayNode(const pair<T,_Val> &value) : SplayNode(value.first, value.second)
	{}
};

template<typename T, typename _Val>
class Splay_Tree
{
	using Node = SplayNode<T,_Val>;
private:
	void bst_print_dot_null(const string& name, int nullcount, ofstream& stream);
	void bst_print_dot_aux(Node* node, ofstream& stream);

	Node *rightRotate(Node *y);
	Node *leftRotate(Node *x);

	Node *splay(Node *root, const T &key);

	Node *search(Node *root, const T &key);
	Node *insert(Node *root, const pair<T, _Val> &value);
	Node* delete_key(Node *root, const T &key);


	void print_tree(Node* root, int shift);
	void freeMemory(Node * root);
	Node* tree;
public:
	Splay_Tree();
	~Splay_Tree();

	void Search(T key);
	void Insert(pair<T,_Val> value);
	void Delete(T key);
	void Print();
	void PrintForViz(const char* path);
};


