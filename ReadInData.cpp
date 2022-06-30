//
// Created by Max Link on 6/22/22.
// code for rapidjson filesystem readin https://rapidjson.org/md_doc_stream.html
//code for chrono clocks https://en.cppreference.com/w/cpp/chrono

#include "ReadInData.h"
#include <set>
#include <iostream>

using namespace std;

void ReadInData::readInStopWords(std::set<std::string> &stopWords) {
    ifstream stopWordsFile("data/stopwords.txt");
    if (!stopWordsFile.is_open()) {
        cout << "Error opening stopWordsFile" << endl;
    }
    char stopWordsBuffer[500];

    while (!stopWordsFile.eof()) {//reads stopWords into buffer & inserts into vector
        stopWordsFile.getline(stopWordsBuffer, 500);
        string buffer = stopWordsBuffer;
        stopWords.insert(buffer); //fills stopWords vector with the list of stopwords from the stopWords.txt file
    }

    stopWordsFile.close();
}




