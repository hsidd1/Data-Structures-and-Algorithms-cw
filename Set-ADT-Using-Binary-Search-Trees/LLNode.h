#ifndef LLNODE_H_
#define LLNODE_H_

template <typename E>
class LLNode
{
public:
    E element;
    LLNode* next;

    LLNode(E i, LLNode* n)
    {
        element = i; next = n;
    }
};

#endif /* LLNODE_H_ */