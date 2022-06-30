//
// Created by Max Link on 6/26/22.
//
#include "SearchEngine.h"
#include "ReadInData.h"
#include "Index.h"
#include "Interface.h"

#include <vector>
#include <set>

using namespace std;

SearchEngine::SearchEngine(string absolutePathToDataFilesDir) {
    std::set<std::string> stopWords; //holds stopWords in a set

    ReadInData reader;
    reader.readInStopWords(stopWords); //reads in stopWords

    Index index;
    index.indexAllFiles(absolutePathToDataFilesDir, stopWords); // optional but here as default behavior to index all files everytime the search engine class is called

    Interface interface;
    interface.userInterface(absolutePathToDataFilesDir, stopWords, index); //interface class gets path to file, stopWords, & index

}