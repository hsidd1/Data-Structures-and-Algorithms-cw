# Data-Structures-and-Algorithms-cw

Coursework for Data Structures and Algorithms course.

## Overview of Contents

### [Operations with Huge Integers](/Operations-with-Huge-Integers/)

The range of integers that can be represented in C++ using a primitive data
type is only from $−2^{63} \ \text{to} \ 2^{63} − 1$. What if we need to manipulate integer values beyond
this range?

This project implements a HugeInteger class which is able to represent arbitrar-
ily large integer numbers. This class implements arithmetic operations on integers
such as addition, subtraction, multiplication and comparison. 

### [Polynomial-Using-Linked-List](Polynomial-Using-Linked-List)

This program implements polynomials and operations on polynomials using a
sorted singly linked list with a dummy header.


### [Set ADT Using Binary Search Trees](Set-ADT-Using-Binary-Search-Trees)


This program implements the Set abstract data type using binary search trees. The specification considers sets of integers where each integer will 
be stored in a tree node. Additionally, a Stack is implemented to perform non-recursive tree traversal. 

### [Hash Tables with Linear and Quadratic Probing](Hash-Tables-with-Linear-and-Quadratic-Probing)

This program implements a hash table with linear probing and perform simulations
to observe its performance. The hash table stores positive integers. The hash
function used is h(x) = x%M (the remainder after dividing x by M), where M
is the size of the hash table. The set of possible keys x is the set of positive integers
representable by the int data type.

## Notes

All labs here are configured as `.sln` C++ projects on Visual Studio.
