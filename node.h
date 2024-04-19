/* FILE: node.h
 * PURPOSE: create Node class
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>

template <class T>
class BinarySearchTree;            // declaration for friend statement below
template <class T> class Position; // declaration for friend statement below
template <class T> class Node {
public:
  Node(); // default constuctor
  // constructor that takes node’s dat
  Node(const T &);
  // copy constructor.
  Node(const Node<T> &);
  virtual ~Node<T>() {} // destructor
  void setItem(const T &);
  T getItem() const { return item; }
  Node<T> &operator=(const Node<T> &);
  friend class BinarySearchTree<T>;
  friend class Position<T>; // Position is an iterator class
private:
  Node<T> *leftPtr;
  Node<T> *rightPtr;
  Node<T> *parentPtr;
  T item;
};

template <class T> Node<T>::Node() { leftPtr = rightPtr = parentPtr = NULL; }

template <class T> Node<T>::Node(const Node<T> &n) {
  this->item = n.item;
  leftPtr = rightPtr = parentPtr = NULL;
}

template <class T> Node<T> &Node<T>::operator=(const Node<T> &n) {
  leftPtr = rightPtr = parentPtr = NULL;
  item = n.item;
  return *this;
}

#endif