#include "chain.hpp"

template <class T>
int Chain<T>::Length() const { // Return the number of elements in the chain.
  ChainNode<T> *current = first;
  int len = 0;
  while (current) {
    len++;
    current = current->link;
  }
  return len;
}

template <class T>
Chain<T>::~Chain() {  // Chain destructor. Delete all nodes in chain.
  ChainNode<T> *next; // next node
  while (first) {
    next = first->link;
    delete first;
    first = next;
  }
}
