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

//todo - parse words out into individual words
//todo - lowercase words & take out punctuation
//todo - throw in AVL tree

using namespace std;

int main(int argc,
         char *argv[]) {
    //calls userInterface
    //Interface userInterface;
    //userInterface.userInterface();

//reads in data
    ReadInData data;

////data.testFileSystem("sample_data/");
    data.testFileSystem("own_file_data_sample/");

}
