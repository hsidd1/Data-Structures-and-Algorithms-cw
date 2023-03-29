#include "BSTSet.h"
#include <iostream>
#include <vector>
using namespace std;

/*initializes the BSTSet object to represent the empty set (an empty
tree).*/
BSTSet::BSTSet()
{
	root = NULL;
}

BSTSet::BSTSet(const std::vector<int>& input)
{
    for (int i = 0; i < input.size(); i++) {
        insert(input[i], root);
    }
}

BSTSet::~BSTSet()
{
    Destruction(root);
}
void BSTSet::Destruction(TNode* node) {
    if (node) {
        Destruction(node->left);
        Destruction(node->right);
        delete node;
    }
}

bool BSTSet::isIn(int v)
{
    if (root == NULL) return false;
    TNode* curr = root;
    while (curr) {
       if (curr->element == v) return true;
       if (curr->element > v) curr = curr->left;
       if (curr->element < v) curr = curr->right;
    }
    return false;
}

void BSTSet::add(int v)
{
    insert(v, root);
}
void BSTSet::insert(int v, TNode* &Node) {
   
    if (Node == NULL)
        Node = new TNode(v, NULL, NULL);
    else if (v < Node->element)
        insert(v, Node->left);
    else if (v > Node->element)
        insert(v, Node->right);
}

bool BSTSet::remove(int v)
{
    if ( removeNode(v, root) ){
        return true;
    }
    return false;
}
 int BSTSet::findMin(TNode* t) {
    if (t == NULL) {
        return NULL;
    }
    while (t->left) t = t->left;
    return (t->element);
}

 int BSTSet::getMax(TNode* node) { // T(n) = O(logn), S(n) = O(1)

     int v = 0;
     while (node->right) {
         node = node->right;
     }

     v = node->element;
     return v;
 }
 bool BSTSet::removeNode(int v, TNode*& node) { // O (logn) or O (n) for worst case

     if (!node) {
         return false;
     }
     else if (v > node->element) {
         return removeNode(v, node->right);
     }

     else if (v < node->element) {
         return removeNode(v, node->left);
     }

     else if (node->left != NULL && node->right != NULL) {
         node->element = getMax(node->left);
         removeNode(node->element, node->left);
         return true;
     }

     else {
         TNode* temp = node;
         if (node->left) {
             node = node->left;
             delete temp;
             return true;
         }
         else {
             node = node->right;
             delete temp;
             return true;
         }
     }
 }

void BSTSet::Union(TNode* node)
{
    if (!node) {
        return;
    }

    Union(node->left);
    Union(node->right);
    insert(node->element, root);
}

void BSTSet::intersection(TNode* node)
{

}
bool BSTSet::isInTree(int v, TNode* node) { // O(logn)

    if (!node) {
        return false;
    }
    else if (v > node->element) {
        return isInTree(v, node->right);
    }

    else if (v < node->element) {
        return isInTree(v, node->left);
    }

    else {
        return true;
    }
}

void BSTSet::difference(const BSTSet& s)
{
	// TODO
}

int BSTSet::size()
{
	// TODO
    return -1; //change this after completing this function
}

int BSTSet::height()
{
	// TODO
    return -2; //change this after completing this function
}

// create and use class MyStack
void BSTSet::printNonRec()
{
	// TODO
	cout << "-2"; //change this after completing this function
}

// Do not modify following provided methods

void BSTSet::printBSTSet()
{
    if (root == NULL)
        std::cout << "";
    else {
        printBSTSet(root);
    }
}

void BSTSet::printBSTSet(TNode* t) {
    if (t != NULL) {
        printBSTSet(t->left);
        std::cout << t->element << ",";
        printBSTSet(t->right);
    }
}
