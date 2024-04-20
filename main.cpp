#include "activity.h"
#include "binarySearchTree.h"
#include "node.h"
#include "participant.h"
#include "position.h"
#include "userFunctions.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// was used to create binary file from supplied text file
void convertTextToBinary(const std::string &inputFileName,
                         const std::string &outputFileName) {
  std::ifstream inputFile(inputFileName); // Open text file for reading
  if (!inputFile.is_open()) {
    std::cerr << "Error: Unable to open input file for reading." << std::endl;
    return;
  }

  std::ofstream outputFile(outputFileName,
                           std::ios::binary); // Open binary file for writing
  if (!outputFile.is_open()) {
    std::cerr << "Error: Unable to open output file for writing." << std::endl;
    return;
  }

  std::string line;
  while (std::getline(inputFile, line)) { // for each line
    // get name, height, and number of activities
    std::istringstream firstLineISS(line);
    std::string firstName, lastName;
    float height;
    int numActivities;
    firstLineISS >> firstName >> lastName >> height >> numActivities;

    Participant participant;
    participant.setFirstName(firstName.c_str());
    participant.setLastName(lastName.c_str());
    participant.setHeight(height);

    // read each activity
    for (int i = 0; i < numActivities; ++i) {
      int activityCode, minutes;
      // go to next line
      getline(inputFile, line);
      istringstream activitiesISS(line);
      activitiesISS >> activityCode >> minutes; // Read activity and minutes
      participant.addActivity(
          static_cast<Activity::Activity_Code>(activityCode), minutes);
    }
    participant.calculateMilesWalked();
    // Write Participant object to binary file
    outputFile.write(reinterpret_cast<const char *>(&participant),
                     sizeof(Participant));
  }

  // Close files
  inputFile.close();
  outputFile.close();
}

int main() {
  ifstream inFile("input.bin", ios::binary);
  BinarySearchTree<Participant> tree;
  tree.readFromBinaryFile(inFile);

  string sInput;
  do {
    cout << "----- Choose an option below -----\n";
    cout << "  1: Remove participant\n"
         << "  2: Add participant\n"
         << "  3: Add activity\n"
         << "  4: Calculate total miles walked\n"
         << "  5: Pre-order print\n"
         << "  6: Exit and save\n";
    cout << "Option> ";
    cin >> sInput;
    int iInput;
    try {
      iInput = stoi(sInput);
    } catch (...) {
      cout << "----- <Enter a number dumbo> -----\n";
      continue;
    }

    switch (iInput) {
    case 1:
      removeParticipant(tree);
      break;
    case 2:
      addParticipant(tree);
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      tree.traverseAndPrint(tree.root(), PREORDER);
      break;
    case 6:
      break;
    }
  } while (sInput != "6");

  inFile.close();
  return 0;
}