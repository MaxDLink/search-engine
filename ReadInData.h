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
#include "AVLMap.h"
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
    void readJsonFile(const char *fileName, set<string> stopWords,  AVLMap<string, set<long>> &personTree,
                      AVLMap<string, set<long>> &orgTree,
                      AVLMap<string, set<long>> &textTree, long &documentId);

    void lowerCaseAndRemovePunct(Document &d, vector<string> &textContent, AVLMap<string, set<long>> &textTree, long documentId);

    void removeStopWords(std::set<string> &stopWords, vector<string> &text, AVLMap<string, set<long>> &textTree);

    void testPrintOutput(vector<string> &text);

public:
    void indexAllFiles(const char *path, std::set<std::string> &stopWords, AVLMap<string, set<long>> &personTree, AVLMap<string, set<long>> &orgTree, AVLMap<string, set<long>> &textTree);

    void stemWords(vector<string> &textContent, AVLMap<string, set<long>> &textTree);

    void readInStopWords(std::set<std::string> &stopWords);

    void wordRetrieveViaQuery(std::vector<std::string> &query, AVLMap<string, set<long>> &tree);

    };


#endif //INC_22SU_SEARCH_ENGINE_READINDATA_H
