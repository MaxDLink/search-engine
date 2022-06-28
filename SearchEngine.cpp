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
    std::set<std::string> stopWords;

    ReadInData reader;
    reader.readInStopWords(stopWords);

    Index index;
    index.indexAllFiles(absolutePathToDataFilesDir, stopWords); // optional but here as default behavior

    Interface interface;
    interface.userInterface(absolutePathToDataFilesDir, stopWords, index);

}