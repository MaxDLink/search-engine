//
// Created by Max Link on 6/26/22.
//

#include "ProjectTimingDemo.h"

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

#include "ReadInData.h"
#include "Interface.h"
#include "tempTestAVLTree.h"
#include <string>
#include <set>

using namespace std;

/*
cd /Users/maxlink/Desktop/22su-search-engine-max

#build debug
/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/maxlink/Desktop/22su-search-engine-max/cmake-build-debug --target 22su_search_engine
run debug
time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-10
time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-221
time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-6000

#build release
/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/maxlink/Desktop/22su-search-engine-max/cmake-build-release --target 22su_search_engine
run release
time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-10
time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-221
time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-6000

 */
ProjectTimingDemo::ProjectTimingDemo(string query, string absolutePathToDataFilesDir) {
    // todo Timing data will be gathered using the time command.

    std::set<std::string> stopWords;

    ReadInData data;
    data.readInStopWords(stopWords);
    // todo turn off org/person indexing
    data.indexAllFiles(absolutePathToDataFilesDir.c_str(), stopWords, textTree, emptyTree, emptyTree);


    // todo QueryParser
    // todo query You need to stem this word before looking for it in your index.
    // todo query lowercase
    // todo query trim
    std::vector<std::string> queryVector;
    queryVector.push_back(query);

    if (queryVector.at(0) == " ") {
        cout << "query was a stop word" << endl;
    } else {
        data.wordRetrieveViaQuery(queryVector, textTree);
    }
}