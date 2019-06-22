#pragma once
enum Color { RED, BLACK };

struct Node
{
	int data;
	bool color;
	Node *left, *right, *parent;
	int size;
	// Constructor 
	Node(int data) : size(0)
	{
		this->data = data;
		left = right = parent = nullptr;
		color = RED;
	}
};
class RB_Tree
{
private:
	Node *root;
	int _getColor(Node *& node);
	void _setColor(Node* &node, int color);
	Node* _Tree_Successor(Node *&root);
	void _RotateLeft(Node* &tree, Node* &pt);
	void _RotateRight(Node* &tree, Node* &pt);

	Node* _SearchBST(Node* &tree, Node* &toSearch);
	void _fixInsertRBTree(Node* &tree, Node *&pt);
	void _fixDeleteRBTree(Node* &tree, Node *&pt);
	void _InsertBST(Node* &tree, Node* &toInsert);
	Node* _DeleteBST(Node* &tree, Node* &toDelete);

	void _inOrderPrint(Node* &tree);
	void _printRB_Tree(Node* &tree, int shift);
	void _levelOrderPrint(Node* &tree);
public:
	RB_Tree();
	~RB_Tree();

	int Search(const int& data);
	void Insert(const int& data);
	void Delete(const int& data);
	void Print();
	void InOrderPrint()
	{
		_inOrderPrint(root);
	}
	void LevelPrint()
	{
		_levelOrderPrint(root);
	}
};

