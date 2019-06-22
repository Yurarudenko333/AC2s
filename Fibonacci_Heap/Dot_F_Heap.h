#pragma once
#include"F_Heap.h"
#include<cstdio>
#include<string>
#include<fstream>
using namespace std;
class Dot_F_Heap : public F_Heap<int> {
public:
	void dump(const string& path) {
		ofstream fout(path);
		fout << "digraph G {\n";
		if (_heap == NULL) {
			fout << "empty;\n}\n";
			return;
		}
		fout << "minimum -> \"" << _heap << "\" [constraint=false];\n";
		Node<int>* c = _heap;
		do {
			_dumpChildren(c,fout);
			c = c->getNext();
		} while (c != _heap);
		fout << "}\n";
	}

private:

	void _dumpChildren(Node<int>* n, ofstream &fout) {
		fout << "\"" << n << "\" -> \"" << n->getNext() << "\" [constraint=false,arrowhead=lnormal];\n";
		fout << "\"" << n << "\" -> \"" << n->getPrev() << "\" [constraint=false,arrowhead=lnormal];\n";
		if (n->isMarked())
			fout << "\"" << n << "\" [style=filled,fillcolor=grey];\n";
		if (n->hasParent()) {
			fout << "\"" << n << "\" -> \"" << n->getParent() << "\" [constraint=false,arrowhead=onormal];\n";
		}
		fout << "\"" << n << "\" [label=" << n->getValue() << "];\n";
		if (n->hasChildren()) {
			Node<int>* c = n->getChild();
			do {
				fout << "\"" << n << "\"  -> \"" << c << "\";\n";
				_dumpChildren(c,fout);
				c = c->getNext();
			} while (c != n->getChild());
		}
	}
};

void test() {
	Dot_F_Heap h;
	h.insert(2);
	h.insert(3);
	h.insert(1);
	h.insert(4);
	h.removeMinimum();
	h.removeMinimum();
	h.insert(5);
	h.insert(7);
	h.removeMinimum();
	h.insert(2);
	Node<int>* nine = h.insert(90);
	h.removeMinimum();
	h.removeMinimum();
	h.removeMinimum();
	for (int i = 0; i < 20; i += 2)h.insert(30 - i);
	for (int i = 0; i < 4; i++)h.removeMinimum();
	for (int i = 0; i < 20; i += 2)h.insert(30 - i);
	h.insert(23);
	for (int i = 0; i < 7; i++)h.removeMinimum();
	h.decreaseKey(nine, 1);
	h.decreaseKey(h.find(28), 2);
	h.decreaseKey(h.find(23), 3);

	h.dump("test.gv");
}