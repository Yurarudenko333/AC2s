#pragma once
template <class T> class F_Heap;

template <class T> struct Node {
private:
	Node* prev;
	Node* next;
	Node* child;
	Node* parent;
	T value;
	int degree;
	bool marked;
	friend class F_Heap<T>;
public:
	
	Node* getPrev() { return prev; }
	Node* getNext() { return next; }
	Node* getChild() { return child; }
	Node* getParent() { return parent; }
	T getValue() { return value; }
	bool isMarked() { return marked; }

	bool hasChildren() { return child; }
	bool hasParent() { return parent; }

};

template <class T> 
class F_Heap {
protected:
	Node<T>* _heap;
public:
	F_Heap() {
		_heap = _empty();
	}
	~F_Heap() {
		if (_heap) {
			_deleteAll(_heap);
		}
	}

	Node<T>* insert(const T &value) {
		Node<T>* ret = _singleton(value);
		_heap = _merge(_heap, ret);
		return ret;
	}

	void merge(F_Heap& other) {
		_heap = _merge(_heap, other._heap);
		other._heap = _empty();
	}

	bool isEmpty() {
		return _heap == NULL;
	}
	T removeMinimum() {
		Node<T>* mini = _heap;

		_heap = _removeMinimum(_heap);
		T res = mini->value;

		delete mini;
		return res;
	}
	T getMinimum() {
		return _heap->value;
	}

	void decreaseKey(Node<T>* node, const T &value) {
		_heap = _decreaseKey(_heap, node, value);
	}

	Node<T>* find(const T &value) {
		return _find(_heap, value);
	}
private:
	Node<T>* _empty() {
		return NULL;
	}
	Node<T>* _singleton(const T &value) {
		Node<T>* single_Heap = new Node<T>;
		single_Heap->value = value;
		single_Heap->prev = single_Heap->next = single_Heap;
		single_Heap->degree = 0;
		single_Heap->marked = false;
		single_Heap->child = NULL;
		single_Heap->parent = NULL;
		return single_Heap;
	}

	Node<T>* _merge(Node<T>* a, Node<T>* b) {
		if (a == NULL)return b;
		if (b == NULL)return a;

		if (a->value > b->value)
			std::swap(a, b);

		Node<T>* a_next = a->next;
		Node<T>* b_prev = b->prev;
		a->next = b;
		b->prev = a;
		a_next->prev = b_prev;
		b_prev->next = a_next;
		return a;
	}

	void _deleteAll(Node<T>* tree) {
		if (tree != NULL) {
			Node<T>* cur = tree;
			do {
				Node<T>* temp = cur;
				cur = cur->next;
				_deleteAll(temp->child);
				delete temp;
			} while (cur != tree);
		}
	}

	Node<T>* _cut(Node<T>* heap, Node<T>* node) {
		if (node->next == node) {
			node->parent->child = NULL;
		}
		else {
			node->next->prev = node->prev;
			node->prev->next = node->next;
			node->parent->child = node->next;
		}
		node->next = node->prev = node;
		node->marked = false;
		return _merge(heap, node);
	}

	Node<T>* _decreaseKey(Node<T>* heap, Node<T>* node, const T &value) {
		if (node->value < value)
			return heap;

		node->value = value;
		if (node->parent) {
			if (node->value < node->parent->value) {
				heap = _cut(heap, node);

				Node<T>* parent = node->parent;
				node->parent = NULL;
				while (parent != NULL && parent->marked) {
					heap = _cut(heap, parent);
					node = parent;
					parent = node->parent;
					node->parent = NULL;
				}
				if (parent != NULL && parent->parent != NULL)
					parent->marked = true;
			}
		}
		else {
			if (node->value < heap->value) {
				heap = node;
			}
		}
		return heap;
	}

	void _unMarkAndUnParentAll(Node<T>* n) {
		if (n == NULL)
			return;
		Node<T>* c = n;
		do {
			c->marked = false;
			c->parent = NULL;
			c = c->next;
		} while (c != n);
	}

	void _addChild(Node<T>* parent, Node<T>* child) {
		child->prev = child->next = child;
		child->parent = parent;
		parent->degree++;
		parent->child = _merge(parent->child, child);
	}

	Node<T>* _removeMinimum(Node<T>* n) {
		_unMarkAndUnParentAll(n->child);
		if (n->next == n) {
			n = n->child;
		}
		else {
			n->next->prev = n->prev;
			n->prev->next = n->next;
			n = _merge(n->next, n->child);
		}
		if (n == NULL)return n;
		Node<T>* trees[64] = { NULL };

		while (true) {
			if (trees[n->degree] != NULL) {
				Node<T>* t = trees[n->degree];
				if (t == n)
					break;
				trees[n->degree] = NULL;
				if (n->value < t->value) {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					_addChild(n, t);
				}
				else {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					if (n->next == n) {
						t->next = t->prev = t;
						_addChild(t, n);
						n = t;
					}
					else {
						n->prev->next = t;
						n->next->prev = t;
						t->next = n->next;
						t->prev = n->prev;
						_addChild(t, n);
						n = t;
					}
				}
				continue;
			}
			else {
				trees[n->degree] = n;
			}
			n = n->next;
		}
		Node<T>* min = n;
		Node<T>* start = n;
		do {
			if (n->value < min->value)
				min = n;
			n = n->next;
		} while (n != start);
		return min;
	}

	Node<T>* _find(Node<T>* heap, const T &value) {
		Node<T>* cur = heap;
		if (cur == NULL)return NULL;
		do {
			if (cur->value == value)return cur;
			Node<T>* found = _find(cur->child, value);
			if (found)
				return found;
			cur = cur->next;
		} while (cur != heap);
		return NULL;
	}
};
