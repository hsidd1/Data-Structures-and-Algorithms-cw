#ifndef MYSTACK_H_
#define MYSTACK_H_

#include "LLNode.h"


template <typename E>
class MyStack
{
private:
    LLNode<E>* head;

public:
    MyStack();
    ~MyStack();
    E pop();
    void push(E e);
    bool isEmpty();
};

#endif