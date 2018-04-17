#include <iostream>
#ifndef CHAIN_NODE_HPP
#define CHAIN_NODE_HPP
template <class T>class Chain;

template <class T>
class ChainNode {
  friend Chain<T>;

private:
  T data;
  ChainNode<T> *link;
};
#endif

#ifndef CHAIN_HPP
#define CHAIN_HPP
template <class T>
class Chain {
public:
  Chain() { first = 0; }
  ~Chain();
  bool IsEmpty() const { return first == 0; }
  int Length() const;
  bool Find(int k, T &x) const;
  int Search(const T &x) const;
  Chain<T> &Delete(int k, T &x);
  Chain<T> &Insert(int k, const T &x);
  void Output(std::ostream &out) const;

private:
  ChainNode<T> *first; // pointer to first node
};
#endif
