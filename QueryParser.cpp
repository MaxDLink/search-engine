//
// Created by Max Link on 6/26/22.
//

#include "QueryParser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "stemmer.h"

QueryParser::QueryParser(std::string query, std::__1::set<std::string> stopWords) {

    // todo QueryParser - take in userInput

    // todo query trim

    // todo query lowercase
    // todo query You need to stem this word before looking for it in your index.

    //lowercase & remove capitals
    std::string word = query;
    std::string lowerWord;
    for (int i = 0; i < word.size(); i++) {//todo - check lower casing for correct words being recorded
        //if(tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z' || tolower(word.at(i)) >= '0' && tolower(word.at(i)) <= '9'){//lowercases words
        if (tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z' ||
            tolower(word.at(i)) >= '0' && tolower(word.at(i)) <= '9') {
            lowerWord += tolower(word.at(i));
        } else {//continues if punctuation
            continue;
        }
    }
    //removes punctuation from string
    for (int i = 0; i < word.size(); i++) {
        if (ispunct(word.at(i))) {//todo - change is punct to not use .erase
            word = word.erase(i, 1); //erases any punctuation from word
        }
    }
//    if (lowerWord != "") {//check for empty in lowerWord
//        queryVector.push_back(lowerWord);
//    }
    //if current word is not a stop word then stem & pushback to query vector
    if (!stopWords.count(lowerWord)) {
        //stem word //todo - add trim later to lowerWord
        Porter2Stemmer::stem(lowerWord);
        queryVector.push_back(lowerWord); //todo - if error change back to query
    }
}

std::vector<std::string> QueryParser::termVector() {
    return queryVector;
}
