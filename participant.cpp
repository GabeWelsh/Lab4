#include "participant.h"
#include <cstring>

char* Participant::getKey() const {
    char *key = new char[strlen(firstName) + strlen(lastName) + 1];
    strcpy(key, firstName);
    strcat(key, lastName);
    return key;
}
