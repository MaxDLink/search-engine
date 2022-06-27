//
// Created by Max Link on 6/26/22.
//
#include "ProjectTimingDemo.h"
#include "QueryParser.h"

#include <iostream>
#include <string>
#include <vector>
#include "rapidjson/document.h"

#include "ReadInData.h"
#include <set>

using namespace std;

/*
cd /Users/maxlink/Desktop/22su-search-engine-max

#build debug
/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/maxlink/Desktop/22su-search-engine-max/cmake-build-debug --target 22su_search_engine
run debug
clear; time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-10
clear; time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-221
clear; time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-6000

#build release
/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/maxlink/Desktop/22su-search-engine-max/cmake-build-release --target 22su_search_engine
run release
clear; time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-10
clear; time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-221
clear; time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-6000

# timer
#  https://en.cppreference.com/w/cpp/chrono

auto start = std::chrono::steady_clock::now();

auto end = std::chrono::steady_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::cout << "FileReadStream: " << elapsed_seconds.count() << "s\n";

 6000 test
 ./cmake-build-release/22su_search_engine year   408.10s user 0.97s system 99% cpu 6:50.44 total

 */
ProjectTimingDemo::ProjectTimingDemo(string query, string absolutePathToDataFilesDir, map<int, std::string> &documentIdAndName) {
    std::set<std::string> stopWords;
    ReadInData data;
    data.readInStopWords(stopWords);
    // todo tune read speed char readBuffer[65536];
    data.indexAllFiles(absolutePathToDataFilesDir.c_str(), stopWords, emptyTree, emptyTree, textTree,
                       documentIdAndName);


    QueryParser qp(query, stopWords); // todo implement stem etc.
    std::vector<std::string> wordVector = qp.termVector();
    if (wordVector.empty()) {
        cout << "query was a stop word" << endl;
    } else {
        data.wordRetrieveViaQuery(wordVector, textTree, documentIdAndName);
    }
}