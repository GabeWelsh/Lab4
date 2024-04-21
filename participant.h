#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "activity.h"
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

class Participant {
private:
  char firstName[20];
  char lastName[20];
  double milesWalked;
  float height;
  Activity participantActivities[365];
  int maxIndex;
  // used when adding an activity
  // updates `milesWalked` based on `participantActivities`
  void calculateTotalMilesWalked() {
    if (maxIndex < 0) {
      milesWalked = 0;
      return;
    }
    int i;
    double miles = 0;
    for (i = 0; i <= maxIndex; i++) {
      miles += participantActivities[i].getInMiles(height);
    }
    milesWalked = miles;
  }

public:
  Participant() : maxIndex(-1), height(0), milesWalked(0) {}
  Participant(float h, const char *fName, const char *lName)
      : height(h), maxIndex(-1), milesWalked(0) {
    strncpy(firstName, fName, sizeof(firstName));
    strncpy(lastName, lName, sizeof(lastName));
  }
  // returns the participant's key
  // just a concatination of lastName and firstName in lowercase
  string getKey() const;
  // set first name
  void setFirstName(const char *fname) { strcpy(firstName, fname); }
  // set last name
  void setLastName(const char *lname) { strcpy(lastName, lname); }
  // set height
  void setHeight(const float h) { height = h; }
  // return `firstName`
  const char *getFirstName() const { return firstName; }
  // return `lastName`
  const char *getLastName() const { return lastName; }
  // return `height`
  float getHeight() const { return height; }
  // adds supplied activity
  void addActivity(const Activity::Activity_Code code, const double minutes) {
    Activity temp(minutes, code);
    participantActivities[maxIndex + 1] = temp;
    maxIndex++;
    calculateTotalMilesWalked();
  }
  // Returns activity stored at the supplied index
  // returns and empty `Activity` if the supplied index is bigger than
  //         `maxIndex`
  Activity getActivity(const int index) const {
    if (index < maxIndex)
      return participantActivities[index];
    else
      return Activity();
  }
  // returns the activity at `maxIndex`
  // if the list is empty, this function will return an empty `Activity`
  Activity getLastActivity() const {
    if (maxIndex >= 0)
      return participantActivities[maxIndex];
    else
      return Activity();
  }
  // return `milesWalked`
  double getMilesWalked() const { return milesWalked; }
  // prints name and total miles walked
  void printStats() const {
    cout << "Participant " << firstName << " " << lastName << ", "
         << milesWalked << " total miles walked";
  }
  // write self to supplied `ofstream`
  void writeToBinaryFile(ofstream &outFile) const {
    outFile.write(reinterpret_cast<const char *>(this), sizeof(*this));
  }
  // reads data from supplied `ifstream` into self
  void readFromBinaryFile(ifstream &inFile) {
    inFile.read(firstName, sizeof(firstName));
    inFile.read(lastName, sizeof(lastName));
    inFile.read(reinterpret_cast<char *>(&milesWalked), sizeof(milesWalked));
    inFile.read(reinterpret_cast<char *>(&height), sizeof(height));
    inFile.read(reinterpret_cast<char *>(&maxIndex), sizeof(maxIndex));
    inFile.read(reinterpret_cast<char *>(&height), sizeof(height));
  }

  bool operator<=(const Participant &part) const {
    return (this->getKey() <= part.getKey());
  }
  bool operator<(const Participant &part) const {
    return (this->getKey() < part.getKey());
  }
  bool operator>=(const Participant &part) const {
    return (this->getKey() >= part.getKey());
  }
  bool operator>(const Participant &part) const {
    return (this->getKey() > part.getKey());
  }
  bool operator==(const Participant &part) const {
    return (this->getKey() == part.getKey());
  }
  bool operator!=(const Participant &part) const {
    return (this->getKey() == part.getKey());
  }
  // adds name and total miles walked to the supplied `ostream`
  friend std::ostream &operator<<(std::ostream &os,
                                  const Participant &participant) {
    os << participant.firstName << " " << participant.lastName << " "
       << participant.getMilesWalked();
    return os;
  }
};

#endif