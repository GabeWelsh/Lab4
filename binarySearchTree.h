/* FILE: binarySearchTree.h
 * PURPOSE: create BinarySearchTree class
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "activity.h"
#include "node.h"
#include "participant.h"
#include "position.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>

using namespace std;

// declaration for friend statement below
template <class T> class Position;

const int PREORDER = 1;
const int INORDER = 2;
const int POSTORDER = 3;

template <class T> class BinarySearchTree {
public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree &);
  // returns num nodes in tree
  int size() const { return numNodes; } // asdfasdfhasdjkfasdgoa
  // returns true if tree empty of real nodes
  bool empty() const { return numNodes == 0; } // aksdhfoiauwebsidbvoisd
  // superroot right pointer always points to real root node
  Position<T> root() const { return Position<T>(superRootPtr->rightPtr); }
  void traverseAndPrint(const Position<T> &p, int type) const;
  int depth(const Position<T> &) const;
  int height(const Position<T> &) const;
  Position<T> begin() const; // asgiphsgsoifnawegas
  // returns NULL iterator
  Position<T> end() const { return Position<T>(); }
  Position<T> find(const T &) const;
  Position<T> findParticipant(const string &) const;
  Position<T> insert(const T &);
  bool erase(const T &);
  bool erase(const Position<T> &);
  BinarySearchTree<T> &operator=(const BinarySearchTree<T> *);
  virtual ~BinarySearchTree() { deleteUtility(superRootPtr); }
  friend class Position<T>;
  Node<T> *copyTree(Node<T> *, Node<T> *);
  void readFromBinaryFile(ifstream &inFile);
  void addActivityToPosition(Position<Participant> &p, Activity &a);
  double getTotalMilesFromActivities() const;
  void writeToBinaryFile(ofstream &outFile) const;

private:
  Node<T> *superRootPtr;
  // number real nodes in tree, not including fake super
  // root and fake ends nodes
  int numNodes;
  void preorderTraverseAndPrint(const Position<T> &) const;  // one of these idk
  void inorderTraverseAndPrint(const Position<T> &) const;   // one of these idk
  void postorderTraverseAndPrint(const Position<T> &) const; // one of these idk

  void inorderTraverseAndWrite(ofstream &outFile, const Position<Participant> &p) const;

  // finds item in tree starting at position
  Position<T> findUtility(const T &item,
                          const Position<T> &) const; // askudhgaoskeghs
  Position<T> findParticipantUtility(const string &key, const Position<T> &) const;
  // inserts item into tree
  Position<T> insertUtility(const T &item);
  // deletes all nodes in the tree
  void deleteUtility(Node<T> *);
  // erases just one node from the tree at position p
  Position<T> eraseUtility(const Position<T> &p);
  // insert item data at position p
  void expandExternal(const T &item, Position<T> &p); // asoidugaseuigajdgbsdiug
  // remove node above fake leaf node at position p
  Position<T> removeAboveExternal(const Position<T> &p);
};

template<>
inline double BinarySearchTree<Participant>::getTotalMilesFromActivities() const {
  Position<Participant> pos = begin();
  double totalMiles = 0;
  do {
    totalMiles += pos.getItem().getMilesWalked();
    ++pos;
  } while (pos != end());
  return totalMiles;
}

template<>
inline void BinarySearchTree<Participant>::addActivityToPosition(Position<Participant> &p, Activity &a) {
  if (p.isExternal()) {
    return;
  }
  p.nodePtr->item.addActivity(a.getActivity(), a.getMinutes());
}
template <>
inline void BinarySearchTree<Participant>::inorderTraverseAndWrite(ofstream &outFile,
                                                             const Position<Participant> &p) const {
  if (p.isInternal()) {
    p.nodePtr->item.writeToBinaryFile(outFile);
    inorderTraverseAndWrite(outFile, p.left());
    inorderTraverseAndWrite(outFile, p.right());
  }
}

template <>
inline void BinarySearchTree<Participant>::writeToBinaryFile(ofstream &outFile) const {
  if (!outFile.is_open()) {
    cerr << "Error: Unable to open file for writing." << endl;
    return;
  }
  inorderTraverseAndWrite(outFile, root());
}

template <class T>
void BinarySearchTree<T>::readFromBinaryFile(ifstream &inFile) {
  if (!inFile.is_open()) {
    return;
  }

  T item;
  while (inFile.read(reinterpret_cast<char *>(&item), sizeof(item))) {
    insert(item); // Insert each item read from the file into the tree
  }
}

template <class T>
Position<T> BinarySearchTree<T>::removeAboveExternal(const Position<T> &p) {
  Node<T> *w = p.nodePtr;
  Node<T> *v = p.nodePtr->parentPtr;
  Node<T> *siblingPtr;
  if (v->leftPtr == w) { // set the sibling
    siblingPtr = v->rightPtr;
  } else {
    siblingPtr = v->leftPtr;
  }
  if (v == superRootPtr->rightPtr) { // root
    siblingPtr->parentPtr =
        superRootPtr; // we know the root's parent it superRoot
    superRootPtr->rightPtr = siblingPtr;
  } else {                                  // not removing root
    Node<T> *grandparentPtr = v->parentPtr; // find grandparent
    if (v == grandparentPtr->leftPtr) {     // should i left or should i right
      grandparentPtr->leftPtr = siblingPtr;
      siblingPtr->parentPtr = grandparentPtr;
    } else {
      grandparentPtr->rightPtr = siblingPtr;
      siblingPtr->parentPtr = grandparentPtr;
    }
  }
  delete w; // remove external
  delete v; // remove the external's parent
  numNodes--;
  return Position<T>(siblingPtr);
}

template <class T>
void BinarySearchTree<T>::expandExternal(const T &item, Position<T> &p) {
  Node<T> *left = new Node<T>();
  Node<T> *right = new Node<T>();
  p.nodePtr->leftPtr = left;
  p.nodePtr->rightPtr = right;
  left->parentPtr = p.nodePtr;
  right->parentPtr = p.nodePtr;
  p.nodePtr->item = item;
  numNodes++;
}

// erases just one node from the tree at position p
template <class T>
Position<T> BinarySearchTree<T>::eraseUtility(const Position<T> &p) {
  Position<T> w;
  if (p.left() == end()) {
    w = p.left();
  } else if (p.right() == end()) {
    w = p.right();
  } else {
    w = p.right();
    do {
      if (w.nodePtr->leftPtr != NULL)
        w = w.left();
    } while (w.isInternal());
    Position<T> u = w.parent();
    p.nodePtr->item = u.nodePtr->item;
  }
  return removeAboveExternal(w);
}

/* erase removes a node above Position p
 * Precondition position p is a valid position in tree
 * Returns true if successful
 */
template <class T> bool BinarySearchTree<T>::erase(const Position<T> &p) {
  // can't remove superroot or fake external node
  if (!p.isSuperRoot() && p.isInternal()) {
    eraseUtility(p);
    return true;
  } else {
    return false;
  }
}

/* erase node that matches value given
 * returns false if not found; true if found and erased;
 */
template <class T> bool BinarySearchTree<T>::erase(T const &value) {
  Position<T> a = findUtility(value, root());
  if (a == end()) {
    return false;
  }
  return erase(a);
}

// deletes all nodes in the tree
template <class T> void BinarySearchTree<T>::deleteUtility(Node<T> *n) {
  if (n == NULL) {
    return;
  } else {
    deleteUtility(n->leftPtr);
    deleteUtility(n->rightPtr);
    delete n;
  }
}

/* default ctor sets up an empty tree with two nodes:
 * fake root whose right ptr points to fake end
 */
template <class T> BinarySearchTree<T>::BinarySearchTree() {
  superRootPtr = new Node<T>();
  superRootPtr->rightPtr = new Node<T>();
  superRootPtr->rightPtr->parentPtr = superRootPtr;
  superRootPtr->leftPtr = NULL;
  numNodes = 0;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &tree) {
  superRootPtr = new Node<T>();
  numNodes = tree.numNodes;
  if (numNodes == 0) {
    superRootPtr->rightPtr = new Node<T>();
    superRootPtr->rightPtr->parentPtr = superRootPtr;
  } else {
    superRootPtr->rightPtr =
        copyTree(superRootPtr, tree.superRootPtr->rightPtr);
  }
}

template <class T>
BinarySearchTree<T> &
BinarySearchTree<T>::operator=(const BinarySearchTree<T> *tree) {
  superRootPtr = new Node<T>();
  superRootPtr->rightPtr = copyTree(superRootPtr, tree->root());
  superRootPtr->rightPtr->parentPtr = superRootPtr;
  superRootPtr->leftPtr = NULL;
  numNodes = 0;
}

template <class T>
Node<T> *BinarySearchTree<T>::copyTree(Node<T> *papa, Node<T> *n) {
  if (n == NULL) {
    return NULL;
  }
  Node<T> *newNode = new Node<T>(*n);
  newNode->parentPtr = papa;
  newNode->leftPtr = copyTree(newNode, n->leftPtr);
  newNode->rightPtr = copyTree(newNode, n->rightPtr);
  return newNode;
}

/* depth returns distance from root to node at parameter
 * position
 * Parameter:
 * p position to compute depth of
 * Returns depth or -1 if position p is superroot
 */
template <class T> int BinarySearchTree<T>::depth(const Position<T> &p) const {
  if (p.isSuperRoot())
    return -1;
  if (p.isRoot())
    return 0;
  else
    return 1 + depth(p.parent());
}

/* height returns distance from node at parameter position to
 * lowest leaf
 * Parameter: position to computer height of
 */
template <class T> int BinarySearchTree<T>::height(const Position<T> &p) const {
  if (p.isExternal())
    return 0;
  int h = 0;
  // h = max of 0 and height of left subtree
  h = max(h, height(Position<T>(p.nodePtr->leftPtr)));
  // h = max of height of left subtree and
  // height of right subtree
  h = max(h, height(Position<T>(p.nodePtr->rightPtr)));
  return 1 + h;
}

/* begin: returns position iterator to first node on tree - the
leftmost
*/
template <class T> Position<T> BinarySearchTree<T>::begin() const {
  if (numNodes > 0) {
    Position<T> p = root();
    while (p.isInternal()) {
      p = p.left();
    }
    return p.parent();
  } else
    return Position<T>(superRootPtr);
}

/* finds a T object in tree
 * Parameters: the object to find
 * Pre-condition: class T has overloaded operator==
 * Returns iterator to object, superroot iterator if tree
 * is empty, fake leaf postion if not found
 */
template <class T> Position<T> BinarySearchTree<T>::find(const T &item) const {
  if (numNodes > 0) {
    Position<T> v = findUtility(item, root());
    return v;
  } else
    return Position<T>(superRootPtr);
}

/* finds a T object in tree
 * Parameters: the object to find
 * Pre-condition: class T has overloaded operator==
 * Returns iterator to object, superroot iterator if tree
 * is empty, fake leaf postion if not found
 */
template <class T> Position<T> BinarySearchTree<T>::findParticipant(const string &key) const {
  if (numNodes > 0) {
    Position<T> v = findParticipantUtility(key, root());
    return v;
  } else
    return Position<T>(superRootPtr);
}

/* inserts object T in the binary tree
 * Parameter: the object to insert
 * Pre-condition: class T has overloaded operator<
 * Returns iterator to newly inserted object or superRootPtr
 * if item already in tree
 */
template <class T> Position<T> BinarySearchTree<T>::insert(const T &item) {
  // root() = superroot's right ptr
  Position<T> p = insertUtility(item);
  // return iterator to position where new node inserted
  return p;
}

template <class T>
Position<T> BinarySearchTree<T>::insertUtility(const T &item) {
  Position<T> pos = findUtility(item, root());
  if (pos.isExternal()) {
    expandExternal(item, pos);
    return pos;
  } else {
    return Position<T>(superRootPtr);
  }
}

// findUtility: recursive utility find function
// Parameters:
// item to look for
// p position to start looking from
// Pre-condition: class T has overloaded operator== and
// operator<, tree not empty of real nodes
// Returns position iterator where found or NULL iterator
template <class T>
Position<T> BinarySearchTree<T>::findUtility(const T &item,
                                             const Position<T> &pos) const {
  if (pos.isExternal()) {
    return pos;
  } else if (pos.nodePtr->getItem() == item) {
    return pos;
  } else if (pos.nodePtr->getItem() > item) {
    return findUtility(item, pos.left());
  } else {
    return findUtility(item, pos.right());
  }
}

// findUtility: recursive utility find function
// Parameters:
// item to look for
// p position to start looking from
// Pre-condition: class T has overloaded operator== and
// operator<, tree not empty of real nodes
// Returns position iterator where found or NULL iterator
template <class T>
Position<T> BinarySearchTree<T>::findParticipantUtility(const string &key,
                                             const Position<T> &pos) const {
  if (pos.isExternal()) {
    return pos;
  } else if (pos.nodePtr->item.getKey() == key.c_str()) { // found
    return pos;
  } else if (pos.nodePtr->item.getKey() > key.c_str()) { // left
    return findParticipantUtility(key, pos.left());
  } else {
    return findParticipantUtility(key, pos.right()); // right
  }
}

template <class T>
void BinarySearchTree<T>::preorderTraverseAndPrint(const Position<T> &a) const {
  if (a.isInternal()) {
    cout << a.nodePtr->getItem() << endl;
    preorderTraverseAndPrint(a.left());
    preorderTraverseAndPrint(a.right());
  }
}

template <class T>
void BinarySearchTree<T>::inorderTraverseAndPrint(const Position<T> &a) const {
  if (a.isInternal()) {
    inorderTraverseAndPrint(a.left());
    cout << a.nodePtr->getItem() << endl;
    inorderTraverseAndPrint(a.right());
  }
}

template <class T>
void BinarySearchTree<T>::postorderTraverseAndPrint(
    const Position<T> &a) const {
  if (a.isInternal()) {
    postorderTraverseAndPrint(a.left());
    postorderTraverseAndPrint(a.right());
    cout << a.nodePtr->getItem() << endl;
  }
}

template <class T>
void BinarySearchTree<T>::traverseAndPrint(const Position<T> &p,
                                           int type) const {
  switch (type) {
  case PREORDER:
    preorderTraverseAndPrint(p);
    break;
  case INORDER:
    inorderTraverseAndPrint(p);
    break;
  case POSTORDER:
    postorderTraverseAndPrint(p);
    break;
  }
}

#endif