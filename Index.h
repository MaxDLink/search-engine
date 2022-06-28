//
// Created by Max Link on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_INDEX_H
#define INC_22SU_SEARCH_ENGINE_INDEX_H

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
#include <map>
#include <set>
#include "AVLTree.h"

using namespace rapidjson;
using namespace std;

class Index {
private:
    void readJsonFile(const char *fileName, set<string> stopWords, long &documentId);

    AVLTree<string, set<long>> personTree;
    AVLTree<string, set<long>> orgTree;
    AVLTree<string, set<long>> textTree;

    map<long, string> documentIDAndName;
    map<long, string> documentIDAndTitle;

public:
    void indexAllFiles(const char *path, set<string> &stopWords);

    void search(string &query, set<std::string> &stopWords);
};


#endif //INC_22SU_SEARCH_ENGINE_INDEX_H
