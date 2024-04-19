#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "activity.h"
#include <iostream>

using namespace std;

class Participant {
private:
  char *firstName[20];
  char *lastName[20];
  double milesWalked;
  float height;
  Activity participantActivities[365];
  int maxIndex;

public:
  Participant() : maxIndex(0), height(0), milesWalked(0) {}
  string getKey() const { return firstName + lastName; };
  void setFirstName(const string fname) { firstName = fname; }
  void setLastName(const string lname) { lastName = lname; }
  bool operator<(const Participant &part) const {
    return (this->getKey() < part.getKey());
  }
  float getStepLength() const { return height * 0.414; }
};

#endif