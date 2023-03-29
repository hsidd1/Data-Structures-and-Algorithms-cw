#include "MyStack.h"
#include "TNode.h"
#include "LLNode.h"
#include <iostream>
#include <vector>

template <typename E>
MyStack<E>::MyStack() {

    head = NULL;

}

template <typename E>
MyStack<E>::~MyStack() {

    LLNode<E>* temp;

    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }

}

template <typename E>
void MyStack<E>::push(E e) {

    head = new LLNode<E>(e, head);

}

template <typename E>
E MyStack<E>::pop() {

    if (isEmpty()) {
        throw std::underflow_error("Stack Underflow");
    }
    else {
        E element;
        LLNode<E>* temp;
        temp = head;
        head = head->next;
        element = temp->element;
        delete temp;
        return element;
    }

}

template <typename E>
bool MyStack<E>::isEmpty() {

    return head == NULL;

}

template class MyStack<int>;
template class MyStack<char>;
template class MyStack<float>;
template class MyStack<double>;
template class MyStack<long>;
template class MyStack<bool>;
template class MyStack<short>;
template class MyStack<TNode*>;