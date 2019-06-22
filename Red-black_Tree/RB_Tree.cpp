#include "RB_Tree.h"
#include<utility>
#include<queue>
#include<iostream>
using std::queue;
using std::cout;
using std::swap;
int RB_Tree::_getColor(Node *&node){
	if (node == nullptr)
		return BLACK;
	return node->color;
}

void RB_Tree::_setColor(Node *&node, int color) {
	if (node == nullptr)
		return;
	node->color = color;
}

Node * RB_Tree::_Tree_Successor(Node *&root)
{
	Node *ptr = root;
	while (ptr->left != nullptr)
		ptr = ptr->left;

	return ptr;
}

void RB_Tree::_RotateLeft(Node* &tree, Node* &pt)
{
	Node *pt_right = pt->right;
	pt->right = pt_right->left;

	if (pt->right != nullptr)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == nullptr)
		tree = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RB_Tree::_RotateRight(Node* &tree, Node* &pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != nullptr)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == nullptr)
		tree = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

void RB_Tree::_fixInsertRBTree(Node* &tree, Node *&pt)
{
	Node *parent_pt = nullptr;
	Node *grand_parent_pt = nullptr;

	while ((pt != tree) && (pt->color != BLACK) && (pt->parent->color == RED))
	{
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/*  Case : A
			Parent of pt is left child of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left)
		{
			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			   The uncle of pt is also red
			   Only Recoloring required */
			if (uncle_pt != nullptr && uncle_pt->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else
			{
				/* Case : 2
				   pt is right child of its parent
				   Left-rotation required */
				if (pt == parent_pt->right)
				{
					_RotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				   pt is left child of its parent
				   Right-rotation required */
				_RotateRight(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/* Case : B
		   Parent of pt is right child of Grand-parent of pt */
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			/*  Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != nullptr) && (uncle_pt->color == RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				   pt is left child of its parent
				   Right-rotation required */
				if (pt == parent_pt->left)
				{
					_RotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				   pt is right child of its parent
				   Left-rotation required */
				_RotateLeft(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	tree->color = BLACK;
}
void RB_Tree::_fixDeleteRBTree(Node *& tree, Node * &pt)
{
	while (pt != tree && pt->color == BLACK)
	{
		if (pt == pt->parent->left)
		{
			Node* w = pt->parent->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				pt->parent->color = RED;
				_RotateLeft(tree, pt->parent);
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				pt = pt->parent;
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					_RotateRight(root, w);
					w = pt->parent->right;
				}
				w->color = pt->parent->color;
				pt->parent->color = BLACK;
				w->right->color = BLACK;
				_RotateLeft(tree, pt->parent);
				pt = tree;
			}
		}
		else
		{
			Node* w = pt->parent->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				pt->parent->color = RED;
				_RotateRight(tree, pt->parent);
			}
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				pt = pt->parent;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					_RotateLeft(root, w);
					w = pt->parent->left;
				}
				w->color = pt->parent->color;
				pt->parent->color = BLACK;
				w->left->color = BLACK;
				_RotateRight(tree, pt->parent);
				pt = tree;
			}
		}
	}
}

Node* RB_Tree::_SearchBST(Node* &tree, Node* &toSearch)
{
	Node* ptr = tree;
	while (ptr != nullptr)
	{
		if (toSearch->data < ptr->data)
			ptr = ptr->left;
		else if (toSearch->data > ptr->data)
			ptr = ptr->right;
		else
			break;
	}

	return ptr;
}
void RB_Tree::_InsertBST(Node* &tree, Node* &toInsert)
{
	Node *toInsert_parent = nullptr;
	Node *ptr = tree;

	while (ptr != nullptr)
	{
		toInsert_parent = ptr;
		if (toInsert->data < ptr->data)
			ptr = ptr->left;
		else if (ptr->data < toInsert->data)
			ptr = ptr->right;
		else
			break;
	}

	toInsert->parent = toInsert_parent;
	if (toInsert_parent == nullptr)
		root = toInsert;
	else if(toInsert->data < toInsert_parent->data)
		toInsert_parent->left = toInsert;
	else if(toInsert_parent->data < toInsert->data)
		toInsert_parent->right = toInsert;
}
Node* RB_Tree::_DeleteBST(Node* &tree, Node* &toDelete) {

	if (tree == nullptr)
		return tree;

	if (toDelete->data < tree->data)
		return _DeleteBST(tree->left, toDelete);

	if (toDelete->data > root->data)
		return _DeleteBST(tree->right, toDelete);

	if (tree->left == nullptr || tree->right == nullptr)
		return tree;

	Node *temp = _Tree_Successor(tree->right);
	root->data = temp->data;
	return _DeleteBST(tree->right, temp);
}

void RB_Tree::_inOrderPrint(Node *& tree)
{
	if (tree == nullptr)
		return;

	_inOrderPrint(tree->left);
	std::cout << tree->data << "  ";
	_inOrderPrint(tree->right);
}
void RB_Tree::_printRB_Tree(Node *& tree, int shift)
{
	if (tree != nullptr)
	{
		_printRB_Tree(tree->right, shift + 1);
		for (int i = 0; i <= shift; i++)
			printf("  ");
		printf("%d\n", tree->data);
		_printRB_Tree(tree->left, shift + 1);
	}
}

void RB_Tree::_levelOrderPrint(Node *& tree)
{
	if (tree == nullptr)
		return;

	queue<Node *> q;
	q.push(tree);

	while (!q.empty())
	{
		Node *temp = q.front();
		cout << temp->data << "  ";
		q.pop();

		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);
	}
}

RB_Tree::RB_Tree()
{
	root = nullptr;
}


RB_Tree::~RB_Tree()
{
}

int RB_Tree::Search(const int & data)
{
	Node *toSearch = new Node(data);
	Node *response = _SearchBST(root, toSearch);

	int res;
	if (response != nullptr)
		res = response->data;
	else
		res = -1;

	delete toSearch;
	return res;
}

// Function to insert a new node with given data 
void RB_Tree::Insert(const int &data)
{
	Node *toInsert = new Node(data);

	// Do a normal BST insert 
	_InsertBST(root, toInsert);

	// fix Red Black Tree violations 
	_fixInsertRBTree(root, toInsert);
}
void RB_Tree::Delete(const int &data)
{
	Node *toDelete = new Node(data);
	Node *toSearch = _SearchBST(root, toDelete);

	if (toSearch != nullptr)
	{
		root = _DeleteBST(root, toDelete);
		_fixDeleteRBTree(root, toDelete);
	}
	delete toDelete;
}

void RB_Tree::Print()
{
	_printRB_Tree(root, 0);
	cout << "\n";
}
