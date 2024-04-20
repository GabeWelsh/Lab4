/* FILE: userFunctions.h
   PURPOSE: create functions to be used in user input
*/
#ifndef USERFUNCTIONS_H
#define USERFUNCTIONS_H

#include "activity.h"
#include "binarySearchTree.h"
#include "node.h"
#include "participant.h"

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

inline void removeParticipant(BinarySearchTree<Participant> &tree) {
  string firstName, lastName;
  cout << "Last Name: ";
  cin >> lastName;
  cout << "First Name: ";
  cin >> firstName;

  string key = lastName;
  key += firstName;
  transform(key.begin(), key.end(), key.begin(), ::tolower);
  

  Position<Participant> thing = tree.findParticipant(key);
  if (thing.isExternal()) {
    cout << "Participant not found" << endl;
  } else {
    thing.getItem().printStats();
    tree.erase(thing);
    cout << " was removed." << endl;
  }
}

inline void addParticipant(BinarySearchTree<Participant> &tree) {
  
}

#endif