//
// Created by Max Link on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_INTERFACE_H
#define INC_22SU_SEARCH_ENGINE_INTERFACE_H

#include "Index.h"
#include <set>
#include <string>

using namespace std;

class Interface {
private:

public:
    void userInterface(string &path, set<string> &stopWords, Index &index);
};

#endif //INC_22SU_SEARCH_ENGINE_INTERFACE_H