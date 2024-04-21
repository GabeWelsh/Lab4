#include "participant.h"
#include <bits/stdc++.h>

using namespace std;
// creates key based on `lastName` and `firstName`
// then lowercases it.
string Participant::getKey() const {
    std::string key = lastName;
    key += firstName;
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    return key;
}
