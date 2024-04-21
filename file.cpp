#include "activity.h"
#include "participant.h"

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
    // Write Participant object to binary file
    outputFile.write(reinterpret_cast<const char *>(&participant),
                     sizeof(Participant));
  }

  // Close files
  inputFile.close();
  outputFile.close();
}

int main() {
    convertTextToBinary("input.txt", "input.bin");
    return 0;
}
