/**
 * Summer 2022 Search Engine Template
 * includes some example code related to 2341 final project for summer 2022
 */
/*
 * code references:
 * stopwords list from https://gist.github.com/larsyencken/1440509
 * stringstream string splitting: https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
 *
 */
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
//todo - parse words out into individual words
//todo - lowercase words & take out punctuation
//todo - throw in AVL tree

using namespace std;

int main(int argc,
         char *argv[]) {
    std::vector<std::string> query;
    std::set<std::string> stopWords;
    //trees
    AVLMap<string, set<long>> personTree;
    AVLMap<string, set<long>> orgTree;
    AVLMap<string, set<long>> textTree;
    //data object
    ReadInData data;
    data.readInStopWords(stopWords);
    data.indexAllFiles("../../sample_data_sets/size-10", stopWords, personTree, orgTree, textTree);
//    data.indexAllFiles("../../fulldataset/", stopWords);
    //calls userInterface
    Interface userInterface;
    query = userInterface.userInterface(stopWords);
    if (query.at(0) == " ") { // todo handle empty query strings after processing
        cout << "query was a stop word" << endl;
    } else {
        data.wordRetrieveViaQuery(query, textTree);
    }

//reads in data

//data.indexAllFiles("sample_data/");
    //data.indexAllFiles("own_file_data_sample/");
    //data.indexAllFiles("../../fulldataset/");
    //data.indexAllFiles("../../sample_data_sets/size-10", stopWords);
//    tempTestAVLTree<float> t;
//    t.insert(1.3);
//    t.insert(2.4);
//    t.insert(3.5);
//    t.insert(4.6);
//    t.insert(5.7);
//    t.insert(6.8);
//    t.insert(7.9);
//    t.inorder();
//    t.remove(5.7);
//    t.remove(6.8);
//    t.remove(7.9);
//    t.inorder();

}
