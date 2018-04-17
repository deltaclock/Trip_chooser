#include "chain.hpp"

template <class T> Chain<T> &Chain<T>::Insert(int k, const T &x) {
  // Insert x after the k'th element.
  // Throw OutOfBounds exception if no k'th element.
  // Pass NoMem exception if inadequate space.
  if (k < 0)
    throw std::out_of_range("Negative value..!!");
  // p will eventually point to k'th node
  ChainNode<T> *p = first;

  for (int index = 1; index < k && p; index++)
    p = p->link; // move p to k'th

  if (k > 0 && !p)
    throw std::out_of_range("No " + std::to_string(k) +
                            "th element"); // no k'th
  // insert
  ChainNode<T> *y = new ChainNode<T>;
  y->data = x;
  if (k) { // insert after p
    y->link = p->link;
    p->link = y;
  } else { // insert as first element
    y->link = first;
    first = y;
  }
  return *this;
}

template <class T> Chain<T> &Chain<T>::Delete(int k, T &x) {
  // Set x to the k'th element and delete it.
  // Throw OutOfBounds exception if no k'th element.
  if (k < 1 || !first)
    throw std::out_of_range("No " + std::to_string(k) +
                            "th element"); // no k'th

  // p will eventually point to k'th node
  ChainNode<T> *p = first;

  // move p to k'th & remove from chain
  if (k == 1)            // p already at k'th
    first = first->link; // remove
  else {                 // use q to get to k-1'st

    ChainNode<T> *q = first;

    for (int index = 1; index < k - 1 && q; index++)
      q = q->link;

    if (!q || !q->link)
      throw std::out_of_range("No " + std::to_string(k) +
                              "th element"); // no k'th

    p = q->link;
    q->link = p->link;
  }
  // remove k'th
  // save k'th element and free node p
  x = p->data;
  delete p;
  return *this;
}
