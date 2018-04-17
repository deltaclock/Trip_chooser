#include "chain.hpp"

template <class T> bool Chain<T>::Find(int k, T &x) const {
  // Set x to the k'th element in the chain.
  // Return false if no k'th; return true otherwise.
  if (k < 1)
    return false;

  ChainNode<T> *current = first;
  int index = 1; // index of current

  while (index < k && current) {
    current = current->link;
    index++;
  }

  if (current) {
    x = current->data;
    return true;
  }

  return false; // no k'th element
}

template <class T> int Chain<T>::Search(const T &x) const {
  // Locate x. Return position of x if found.
  // Return 0 if x not in the chain.

  ChainNode<T> *current = first;
  int index = 1; // index of current

  while (current && current->data != x) {
    current = current->link;
    index++;
  }
  
  if (current)
    return index;
  return 0;
}
