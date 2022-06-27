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
//    void readJsonFile(const char *fileName, set<string> stopWords, AVLTree<string, set<long>> personTree,
//                      AVLTree<string, set<long>> orgTree, AVLTree<string, set<long>> textTree, long &documentId);

    void readJsonFile(const char *fileName, set<string> stopWords, AVLTree<string, set<long>> &personTree,
                      AVLTree<string, set<long>> &orgTree, AVLTree<string, set<long>> &textTree, long &documentId);

    void lowerCaseAndRemovePunct(Document &d, vector<string> &textContent, AVLTree<string, set<long>> &textTree, long documentId, set<string> &stopWords);

    void removeStopWords(std::set<string> &stopWords, vector<string> &text, AVLTree<string, set<long>> &textTree);

    void testPrintOutput(vector<string> &text);

public:
    void indexAllFiles(const char *path, set<std::string> &stopWords, AVLTree<string, set<long>> &personTree,
                       AVLTree<string, set<long>> &orgTree, AVLTree<string, set<long>> &textTree,
                       map<long, string> &documentIDAndName);

    void stemWords(vector<string> &textContent, AVLTree<string, set<long>> &textTree);

    void readInStopWords(std::set<std::string> &stopWords);

    void wordRetrieveViaQuery(std::vector<std::string> &query, AVLTree<string, set<long>> &tree, map<long, string> &documentIdAndName);
};


#endif //INC_22SU_SEARCH_ENGINE_READINDATA_H
