/* FILE: userFunctions.h
   PURPOSE: create functions to be used in user input
*/
#ifndef USERFUNCTIONS_H
#define USERFUNCTIONS_H

#include "activity.h"
#include "binarySearchTree.h"
#include "node.h"
#include "participant.h"

#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Returns nothing
// Purpose: ask user input to remove a participant from the Binary Tree
inline void removeParticipant(BinarySearchTree<Participant> &tree) {
  if (tree.empty()) {
    cout << "--- Tree is empty. Please add a participant. ---" << endl;
    return;
  }
  string firstName, lastName;
  cout << "Last Name: ";
  cin >> lastName;
  cout << "First Name: ";
  cin >> firstName;

  string key = lastName;
  key += firstName;
  // convert sring from: rANdOm -> random
  transform(key.begin(), key.end(), key.begin(), ::tolower);

  Position<Participant> thing = tree.findParticipant(key);
  if (thing.isExternal()) {
    cout << "--- Participant not found ---" << endl;
  } else {
    thing.getItem().printStats();
    tree.erase(thing);
    cout << " was removed." << endl;
  }
}

// Directly changes supplied string: `input`
// Sets first character to uppercase and the rest to lower.
// ex: "rAnDOM" -> "Random"
inline void fixString(std::string &input) {
  if (!input.empty()) {
    // Convert all characters to lowercase
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    // Capitalize the first character
    input[0] = toupper(input[0]);
  }
}

inline void addParticipant(BinarySearchTree<Participant> &tree) {
  string firstName, lastName;
  cout << "Last Name: ";
  cin >> lastName;
  cout << "First Name: ";
  cin >> firstName;
  string key = lastName;
  key += firstName;
  // make sure the key is all lowercase
  transform(key.begin(), key.end(), key.begin(), ::tolower);

  Position<Participant> thing = tree.findParticipant(key);
  if (thing.isExternal() || tree.empty()) {
    float height;
    cout << "Height in inches: ";
    cin >> height;
    fixString(firstName);
    fixString(lastName);

    Participant someGuy(height, firstName.c_str(), lastName.c_str());
    tree.insert(someGuy);

    cout << someGuy.getFirstName() << " " << someGuy.getLastName()
         << " has been added." << endl;
  } else {
    cout << thing.getItem().getFirstName() << " "
         << thing.getItem().getLastName() << " is already a participant"
         << endl;
  }
}

inline void addActivity(BinarySearchTree<Participant> &tree) {
  if (tree.empty()) {
    cout << "--- The tree is empty. Please add a participant. ---" << endl;
    return;
  }
  string firstName, lastName;
  cout << "Last Name: ";
  cin >> lastName;
  cout << "First Name: ";
  cin >> firstName;

  string key = lastName;
  key += firstName;
  transform(key.begin(), key.end(), key.begin(), ::tolower);

  fixString(firstName);
  fixString(lastName);

  Position<Participant> guy = tree.findParticipant(key);
  if (guy.isExternal()) {
    cout << "Participant not found." << endl;
  } else {
    bool validInput = false; // flag for user-input
    string sActivityInput, sMinutes;
    int iActivityInput;
    double dMinutes;
    // do-while loop is in case of errors in user input
    do {
      cout << "Activity code: ";
      cin >> sActivityInput;
      try {
        iActivityInput = stoi(sActivityInput);
      } catch (...) {
        cout << "---- <Enter a number dumbo> ----" << endl;
        continue;
      }
      if (iActivityInput > Activity::Activity_Code::Yoga ||
          iActivityInput < 0) {
        cout << "--- Your input must be between 0 and 27 ---" << endl;
        continue;
      }
      cout << "Minutes: ";
      cin >> sMinutes;
      try {
        dMinutes = stod(sMinutes);
      } catch (...) {
        cout << "---- <Enter a number dumbo> ----" << endl;
        continue;
      }
      validInput = true;
      Activity::Activity_Code activityCode =
          static_cast<Activity::Activity_Code>(iActivityInput);
      Activity activity(dMinutes, activityCode);
      tree.addActivityToPosition(guy, activity);
    } while (!validInput);
    
    // FirstName LastName, ActivityAdded, NumberOfMinutesAdded = NumberOfMilesAdded
    cout << guy.getItem().getFirstName() << " " << guy.getItem().getLastName()
         << ", " << guy.getItem().getLastActivity().getActivityName() << ", "
         << guy.getItem().getLastActivity().getMinutes() << " minutes" << " = "
         << guy.getItem().getLastActivity().getInMiles(
                guy.getItem().getHeight())
         << endl;
  }
}

inline void printTotalMilesWalked(BinarySearchTree<Participant> &tree) {
  if (tree.empty()) {
    cout << "0 miles walked (The Binary Tree is empty)" << endl;
  } else {
    cout << tree.getTotalMilesFromActivities() << " miles walked." << endl;
  }
}

inline void preOrderPrint(BinarySearchTree<Participant> &tree) {
  if (!tree.empty())
    tree.traverseAndPrint(tree.root(), PREORDER);
  else
    cout << "--- The Binary Tree is empty. Please add a participant. ---"
         << endl;
}

inline void exitAndSave(BinarySearchTree<Participant> &tree,
                        ofstream &outFile) {
  tree.writeToBinaryFile(outFile);
}

#endif