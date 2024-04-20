#include "participant.h"
#include <bits/stdc++.h>

using namespace std;
string Participant::getKey() const {
    std::string key = lastName;
    key += firstName;
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    return key;
}
