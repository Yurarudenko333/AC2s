#include "Splay_Tree.h"
#include<cstdio> 
#include<cstdlib>
#include<iostream>
using std::cout;


template class Splay_Tree<int,int>;
template class Splay_Tree<double, Food::Food_object>;
template<typename T,class _Val>
void Splay_Tree<T,_Val>::bst_print_dot_null(const string& name, int nullcount, ofstream & fout)
{
	fout << "    null" << nullcount << "[shape=point];\n";
	fout << "    " << name << " -> null" << nullcount << ";\n";
}
template<typename T,class _Val>
void Splay_Tree<T,_Val>::bst_print_dot_aux(Node * node, ofstream & fout)
{
	static int nullcount = 0;
	static int validcount = 0;

	string parent = "node" + std::to_string(validcount);
	fout << parent << "[label=\"{" << node->value << "}\"];\n";
	if (node->left != nullptr)
	{
		fout << parent << " -> " << "node" << ++validcount << ";\n";
		bst_print_dot_aux(node->left, fout);
	}
	else
		bst_print_dot_null(parent, nullcount++, fout);

	if (node->right != nullptr)
	{
		fout << parent << " -> " << "node" << ++validcount << ";\n";
		bst_print_dot_aux(node->right, fout);
	}
	else
		bst_print_dot_null(parent, nullcount++, fout);
}
// A utility function to right rotate subtree rooted with y 
//				y                                     x
//             / \     Zig (Right Rotation)          /  \
//            x   T3   � - � - � - � - - ->         T1   y 
//           / \       < - - - - - - - - -              / \
//          T1  T2     Zag (Left Rotation)            T2   T3
template<class T, class _Val>
typename Splay_Tree<T, _Val>::Node* Splay_Tree<T, _Val>::rightRotate(Node *y)
{
	Node *x = y->left;
	y->left = x->right;
	x->right = y;
	return x;
}

// A utility function to left rotate subtree rooted with x
//				y                                     x
//             / \     Zig (Right Rotation)          /  \
//            x   T3   � - � - � - � - - ->         T1   y 
//           / \       < - - - - - - - - -              / \
//          T1  T2     Zag (Left Rotation)            T2   T3
template<class T,class _Val>
typename Splay_Tree<T,_Val>::Node* Splay_Tree<T,_Val>::leftRotate(Node *x)
{
	Node *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

// This function brings the key at root if key is present in tree. 
// If key is not present, then it brings the last accessed item at 
// root.  This function modifies the tree and returns the new root
template<class T,class _Val>
typename Splay_Tree<T,_Val>::Node* Splay_Tree<T,_Val>::splay(Node *root, const T &key)
{
	// Base cases: root is NULL or key is present at root 
	if (root == nullptr || root->key == key)
		return root;

	// Key lies in left subtree 
	if (root->key > key)
	{
		// Key is not in tree, we are done 
		if (root->left == nullptr) return root;

		// Zig-Zig (Left Left) 
		if (root->left->key > key)
		{
			// First recursively bring the key as root of left-left 
			root->left->left = splay(root->left->left, key);

			// Do first rotation for root, second rotation is done after else 
			root = rightRotate(root);
		}
		else if (root->left->key < key) // Zag-Zig (Left Right) 
		{
			// First recursively bring the key as root of left-right 
			root->left->right = splay(root->left->right, key);

			// Do first rotation for root->left 
			if (root->left->right != nullptr)
				root->left = leftRotate(root->left);
		}

		// Do second rotation for root 
		return (root->left == nullptr) ? root : rightRotate(root);
	}
	else // Key lies in right subtree 
	{
		// Key is not in tree, we are done 
		if (root->right == nullptr) return root;

		// Zig-Zag (Right Left) 
		if (root->right->key > key)
		{
			// Bring the key as root of right-left 
			root->right->left = splay(root->right->left, key);

			// Do first rotation for root->right 
			if (root->right->left != nullptr)
				root->right = rightRotate(root->right);
		}
		else if (root->right->key < key)// Zag-Zag (Right Right) 
		{
			// Bring the key as root of right-right and do first rotation 
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

		// Do second rotation for root 
		return (root->right == nullptr) ? root : leftRotate(root);
	}
}

// The search function for Splay tree.  Note that this function 
// returns the new root of Splay Tree.  If key is present in tree 
// then, it is moved to root.
template<class T,class _Val>
typename Splay_Tree<T,_Val>::Node* Splay_Tree<T,_Val>::search(Node *root, const T &key)
{
	return splay(root, key);
}

// Function to insert a new key k in splay tree with given root
template<class T, class _Val>
typename Splay_Tree<T,_Val>::Node* Splay_Tree<T,_Val>::insert(Node *root, const pair<T,_Val> &k)
{
	
	// Simple Case: If tree is empty 
	if (root == nullptr) return new Node(k);

	// Bring the closest leaf node to root 
	root = splay(root, k.first);

	// If key is already present, then return 
	if (root->key == k.first) return root;

	// Otherwise allocate memory for new node 
	Node *newnode = new Node(k);

	// If root's key is greater, make root as right child 
	// of newnode and copy the left child of root to newnode 
	if (root->key > k.first)
	{
		newnode->right = root;
		newnode->left = root->left;
		root->left = nullptr;
	}

	// If root's key is smaller, make root as left child 
	// of newnode and copy the right child of root to newnode
	//left child of root is smaller that key, otherwise left child would stay in root
	else
	{
		newnode->left = root;
		newnode->right = root->right;
		root->right = NULL;
	}

	return newnode; // newnode becomes new root 
}

// The delete function for Splay tree. Note that this function 
// returns the new root of Splay Tree after removing the key
template<class T, class _Val>
typename Splay_Tree<T, _Val>::Node* Splay_Tree<T, _Val>::delete_key(Node *root, const T &key)
{
	if (!root)
		return nullptr;

	// Splay the given key     
	root = splay(root, key);

	// If key is not present, then 
	// return root 
	if (key != root->key)
		return root;

	// If key is present 
	// If left child of root does not exist 
	// make root->right as root 
	Node *temp;
	if (!root->left)
	{
		temp = root;
		root = root->right;
	}

	// Else if left child exits 
	else
	{
		temp = root;

		/*Note: Since key == root->key,
		so after Splay(root->left_child, key),
		the tree we get will have no right child tree
		and maximum node in left subtree will get splayed*/
		// New root 
		root = splay(root->left, key);

		// Make right child of previous root  as 
		// new root's right child 
		root->right = temp->right;
	}

	// free the previous root node, that is, 
	// the node containing the key 
	delete temp;

	// return root of the new Splay Tree 
	return root;
}

template<typename T, typename _Val> void Splay_Tree<T, _Val>::print_tree(Node *root, int shift)
{
	if (root != nullptr)
	{
		print_tree(root->right, shift + 1);
		for (int i = 0; i <= shift; i++)
			cout << "  ";
		cout << root->value << "\n";
		print_tree(root->left, shift + 1);
	}
}

template<typename T, typename _Val> void Splay_Tree<T, _Val>::freeMemory(Node * root)
{
	if (!root)
		return;

	freeMemory(root->left);
	freeMemory(root->right);

	delete root;
}

template<typename T, typename _Val> Splay_Tree<T, _Val>::Splay_Tree()
{
}


template<typename T, typename _Val> Splay_Tree<T,_Val>:: ~Splay_Tree()
{
	freeMemory(tree);
}

template<typename T, typename _Val> void Splay_Tree<T, _Val>::Search(T key)
{
	tree = search(tree, key);
}
template<typename T, typename _Val> void Splay_Tree<T, _Val>::Insert(pair<T,_Val> value)
{
	tree = insert(tree, value);
}
template<typename T, typename _Val> void Splay_Tree<T, _Val>::Delete(T key)
{
	tree = delete_key(tree, key);
}
template<typename T, typename _Val> void Splay_Tree<T,_Val>::Print()
{
	print_tree(tree, 0);
	cout << "\n\n";
}

template<typename T, typename _Val>
void Splay_Tree<T,_Val>::PrintForViz(const char * path)
{
	ofstream fout(path);

	fout << "digraph BST {\n";
	fout << "    node [fontname=\"Arial\"\n    fontsize = \"16\"\n    shape = \"record\"];\n";

	if (tree == nullptr)
		fout << "\n";
	else if (tree->right == nullptr && tree->left == nullptr)
		fout << "    \"" << tree->value << "\";\n";
	else
		bst_print_dot_aux(tree, fout);

	fout << "}\n";
	fout.close();
}

