#ifndef CHAIN_NODE_HPP
#define CHAIN_NODE_HPP
#include <iostream>
template <class T> class Chain;
template <class T> class ChainIterator;

template <class T> class ChainNode {
  friend Chain<T>;
  friend ChainIterator<T>;

private:
  T data;
  ChainNode<T> *link;
};
#endif

#ifndef CHAIN_HPP
#define CHAIN_HPP
template <class T> class Chain {
  friend ChainIterator<T>;

public:
  Chain() { first = 0; }
  ~Chain();
  bool IsEmpty() const { return first == 0; }
  uint16_t Length() const;
  bool Find(int k, T &x) const;
  int Search(const T &x) const;
  Chain<T> &Delete(int k, T &x);
  Chain<T> &Insert(int k, const T &x);
  void Output(std::ostream &out) const;
  void Erase();
  Chain<T> &Append(const T &x);

private:
  ChainNode<T> *first; // pointer to first node
  ChainNode<T> *last;  // pointer to last node
};
template <class T>
std::ostream &operator<<(std::ostream &out, const Chain<T> &x);
#endif

#ifndef CHAIN_ITERATOR_HPP
#define CHAIN_ITERATOR_HPP
template <class T> class ChainIterator {
private:
  ChainNode<T> *location;

public:
  T *Init(const Chain<T> &c);
  T *Next();
};
#endif
