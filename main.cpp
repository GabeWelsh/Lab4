#include "binarySearchTree.h"
#include "node.h"
#include "participant.h"
#include "position.h"

#include <fstream>
#include <iostream>

using namespace std;

int main() { 
  BinarySearchTree<Participant> tree;
  ifstream file("tracking.bin", ios::binary);
  if (file) {
    while (!file.eof()) {
    }
  }
  file.close();
}