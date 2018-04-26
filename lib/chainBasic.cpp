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

template <class T> void Chain<T>::Erase() {
  // Delete all nodes in the chain
  ChainNode<T> *next;
  while (first) {
    next = first->link;
    delete first;
    first = next;
  }
}

template <class T> Chain<T> &Chain<T>::Append(const T &x) { // add x at the end.

  ChainNode<T> *y = new ChainNode<T>;
  y->data = x;
  y->link = 0;

  if (first) { // chain not empty
    last->link = y;
    last = y;
  } else {
    first = last = y;
  }
}
