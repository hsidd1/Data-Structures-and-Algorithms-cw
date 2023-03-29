#ifndef BSTSET_H_
#define BSTSET_H_

#include "TNode.h"
#include <vector>

class BSTSet
{
private:
	// must contain only one private field
	TNode* root = NULL;

public:
	// required constructors/destructor
	BSTSet();
	BSTSet(const std::vector<int>& input);
	~BSTSet();

	// required methods
	bool isIn(int v);
	void add(int v);
	bool remove(int v);
	void Union(TNode* node);
	void intersection(TNode* node);
	void difference(const BSTSet& s);
	int size();
	int height();
	void printNonRec(); // create and use class MyStack

	// provided recursive print method
	void printBSTSet();
	void insert(int v, TNode* &Node);
	void Destruction(TNode* node);
	void RealRemove(int v, TNode* root);
	 int findMin(TNode* b);
	 bool removeNode(int v, TNode*& node);
	 int getMax(TNode* node);
	 bool isInTree(int v, TNode* node);
	// void intersect(TNode* node, TNode* s);
	// Used for testing
	TNode* getRoot()
	{
		return root;
	}

private:
	// provided helper methods
	void printBSTSet(TNode* t);
};

#endif /* BSTSET_H_ */
