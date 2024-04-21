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

public:
  Participant() : maxIndex(-1), height(0), milesWalked(0) {}
  Participant(float h, const char* fName, const char* lName) : height(h), maxIndex(-1), milesWalked(0) {
    strncpy(firstName, fName, sizeof(firstName));
    strncpy(lastName, lName, sizeof(lastName));
  }
  string getKey() const;
  void setFirstName(const char *fname) { strcpy(firstName, fname); }
  void setLastName(const char *lname) { strcpy(lastName, lname); }
  void setHeight(const float h) { height = h; }
  const char *getFirstName() const { return firstName; }
  const char *getLastName() const { return lastName; }
  float getHeight() const { return height; }
  void addActivity(const Activity::Activity_Code code, const double minutes) {
    Activity temp(minutes, code);
    participantActivities[maxIndex + 1] = temp;
    maxIndex++;
    calculateTotalMilesWalked();
  }
  Activity getActivity(const int index) const {
    if (index < 365)
      return participantActivities[index];
    else
      return Activity();
  }
  Activity getLastActivity() const {
    if (maxIndex >= 0)
      return participantActivities[maxIndex];
    else
      return Activity();
  }
  double getMilesWalked() const {
    return milesWalked;
  }
  void printStats() const {
    cout << "Participant " << firstName << " " << lastName << ", " << milesWalked << " total miles walked";
  }

  void writeToBinaryFile(ofstream &outFile) const {
    outFile.write(reinterpret_cast<const char *>(this), sizeof(*this));
  }

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

  friend std::ostream &operator<<(std::ostream &os,
                                  const Participant &participant) {
    os << participant.firstName << " " << participant.lastName
       << " " << participant.getMilesWalked();
    return os;
  }
};

#endif