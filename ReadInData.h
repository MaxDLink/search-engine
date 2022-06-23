//
// Created by Max Link on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_READINDATA_H
#define INC_22SU_SEARCH_ENGINE_READINDATA_H
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "porter2_stemmer.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
//RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "stemmer.h"

using namespace rapidjson;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::setw;
using std::left;
using std::string;
using std::vector;

class ReadInData {
private:
    void testReadJsonFile(const char *fileName);

public:
    void testFileSystem(const char *path);


};


#endif //INC_22SU_SEARCH_ENGINE_READINDATA_H
