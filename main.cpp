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


//todo - parse words out into individual words
//todo - lowercase words & take out punctuation
//todo - throw in AVL tree

using namespace std;

int main(int argc,
         char *argv[]) {

    //    //calls userInterface
//    interface userInterface;
//    userInterface.userInterface();
ReadInData data;

//    cout << "-------------------------------------------" << endl;
//    cout << "------ RapidJSON Doc Parsing Example ------" << endl;
//    cout << "-------------------------------------------" << endl;
////    testReadJsonFile("sample_data/news_0064567.json");
//    //data.testReadJsonFile("own_file_data_sample/news_0041337.json");

//    cout << "\n";
//    cout << "-------------------------------------------" << endl;
//    cout << "------     File System Example       ------" << endl;
//    cout << "-------------------------------------------" << endl;
////    testFileSystem("sample_data/");
    data.testFileSystem("own_file_data_sample/");


//    ///stemmer
//    string wordToStem = "running";
//    Porter2Stemmer::stem(wordToStem);

//    ///stemmer main //todo - clean up this block
//    std::ifstream in{"data/diffs.txt"};
//    std::string to_stem;
//    std::string stemmed;
//    bool mistake = false;
//    using timer = std::chrono::high_resolution_clock;
//    timer::time_point start_time = timer::now();
//    while (in >> to_stem >> stemmed)
//    {
//        std::string orig = to_stem;
//        Porter2Stemmer::trim(to_stem);
//        Porter2Stemmer::stem(to_stem);
//        if (to_stem != stemmed)
//        {
//            std::cout << "  incorrect!" << std::endl
//                      << std::endl
//                      << "to stem:  " << orig    << std::endl
//                      << "stemmed:  " << to_stem << std::endl
//                      << "expected: " << stemmed << std::endl;
//            mistake = true;
//        }
//    }
//    timer::time_point end_time = timer::now();
//
//    if (!mistake)
//        std::cout << "Passed all tests!" << std::endl;
//
//    std::cout << "Time elapsed: "
//              << std::chrono::duration_cast<std::chrono::milliseconds>(
//                      end_time - start_time).count() << "ms" << std::endl;

///stem
//    ///stem test
//    string to_stem = "running";
//    cout << "unstemmed: " << to_stem << endl;
//    Porter2Stemmer::trim(to_stem);
//    cout << "trimmed: " << to_stem << endl;
//    Porter2Stemmer::stem(to_stem);
//    cout << "stemmed: " << to_stem << endl;


}
