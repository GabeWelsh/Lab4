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

inline string fixString(const std::string &input) {
  string result = input;
  if (!result.empty()) {
    // Capitalize the first character
    result[0] = toupper(result[0]);
    // Convert the rest of the characters to lowercase
    for (size_t i = 1; i < result.length(); ++i) {
      result[i] = std::tolower(result[i]);
    }
  }
  return result;
}

inline void addParticipant(BinarySearchTree<Participant> &tree) {
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
    float height;
    cout << "Height in inches: ";
    cin >> height;
    firstName = fixString(firstName);
    lastName = fixString(lastName);

    Participant someGuy(height, firstName.c_str(), lastName.c_str());
    tree.insert(someGuy);

    cout << someGuy.getFirstName() << " " << someGuy.getLastName()
         << " has been added." << endl;
  } else {
    cout << thing.getItem().getFirstName() << " "
         << thing.getItem().getLastName() << " is already a participant";
  }
}

#endif