//
// Created by Max Link on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_READINDATA_H
#define INC_22SU_SEARCH_ENGINE_READINDATA_H

#include <string>
#include <set>
#include <fstream>

using namespace std;

class ReadInData {
private:

public:
    void readInStopWords(set<string> &stopWords);
};


#endif //INC_22SU_SEARCH_ENGINE_READINDATA_H
