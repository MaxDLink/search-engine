//
// Created by Max Link on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_INDEX_H
#define INC_22SU_SEARCH_ENGINE_INDEX_H

#include "AVLTree.h"
#include "porter2_stemmer.h"

//RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"


#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace rapidjson;
using namespace std;

class Index {
private:
    AVLTree<string, set<long>> personTree;
    AVLTree<string, set<long>> orgTree;
    AVLTree<string, set<long>> textTree;

    map<long, string> documentIDAndName;
    map<long, string> documentIDAndTitle;

    void readJsonFile(string fileName, set<string> stopWords, long &documentId);
    set<long> getDocIds(vector<string> words, bool isAnd);

public:

    void indexAllFiles(string path, set<string> &stopWords);

    void search(string &query, set<std::string> &stopWords);
    void clear();
    void save();
    void load();
    void stats();

    Index();
};


#endif //INC_22SU_SEARCH_ENGINE_INDEX_H
