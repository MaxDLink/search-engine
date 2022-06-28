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
    //lowercase & remove capitals
    std::string word = query;
    std::string lowerWord;

// lower case, no punct
// only for terms (not person and org)
//    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
//                   [](unsigned char c) {
//                       c = std::tolower(c);
//                       if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9') {
//                           return c;
//                       } else {
//                           return (unsigned char) ' ';
//                       }
//                   });

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

    //if current word is not a stop word then stem & pushback to query vector
    if (!stopWords.count(lowerWord)) {
        Porter2Stemmer::stem(lowerWord);
        // todo trim lowerWord
        queryVector.push_back(lowerWord);
    }
}

std::vector<std::string> QueryParser::termVector() {
    return queryVector;
}
