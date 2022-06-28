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
#include <map>
#include <set>
#include "AVLTree.h"

using namespace rapidjson;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::setw;
using std::left;
using std::string;
using std::vector;
using std::map;
using std::set;

class ReadInData {
private:
    void readJsonFile(const char *fileName, set<string> stopWords, AVLTree<string, set<long>> &personTree,
                      AVLTree<string, set<long>> &orgTree, AVLTree<string, set<long>> &textTree, long &documentId,
                      map<long, string> &documentIDAndTitle);

public:
    void readInStopWords(std::set<std::string> &stopWords);

    void indexAllFiles(const char *path, set<std::string> &stopWords, AVLTree<string, set<long>> &personTree,
                       AVLTree<string, set<long>> &orgTree, AVLTree<string, set<long>> &textTree,
                       map<long, string> &documentIDAndName, map<long, string> &documentIDAndTitle);

    void wordRetrieveViaQuery(vector<std::string> &query, AVLTree<string, set<long>> &tree,
                              map<long, string> &documentIdAndName,
                              map<long, string> &documentIdAndTitle);


};


#endif //INC_22SU_SEARCH_ENGINE_READINDATA_H
