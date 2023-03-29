#ifndef BSTSET_H_
#define BSTSET_H_

#include "TNode.h"
#include "LLNode.h"
#include "MyStack.h"
#include <iostream>
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
	void Union(const BSTSet& s);
	void intersection(const BSTSet& s);
	void difference(const BSTSet& s);
	int size();
	int height();
	void printNonRec(); // create and use class MyStack

	void insert(int data, TNode* &node);
	void deleteTree(TNode* node);
	bool isInTree(int v, TNode* node);
	bool removeNode(int v, TNode* &node);
	int getSize(int x, TNode* node);
	int getMax(TNode* node);
	int getMin(TNode* node);
	void Union(TNode* node);
	void intersect(TNode* node, TNode* s);
	void difference(TNode* node, TNode* s);
	int getHeight(TNode* node);



	// provided recursive print method
	void printBSTSet();

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