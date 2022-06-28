//
// Created by Max Link on 6/26/22.
//

#include "QueryParser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "stemmer.h"

using namespace std;

QueryParser::QueryParser(string query, set<string> stopWords) {
    //lowercase & remove capitals
    string word = query;
    string lowerWord;

// todo parse the queries
    // i want to find a puppy PERSON steve or bill ORG dobe basset NOT cat mouse rat
    // i want to find a puppy AND bird  PERSON steve AND bill ORG dobe OR basset NOT cat mouse rat
    // v wordList, isAnd = false
    // v personList, isAnd
    // v orgList, isAnd
    // v notWordList, isAnd

    //string query
    //v currWl = wordList
    // string mode = "word"
    //while (token = getline(query, " ")) {
//       if (token == "PERSON" ) {
//           currWl = personList
//                   mode == "person"
//       } else if (token == "AND") {
//        currWl.isAnd = true
//    } else if (mode == word){
//           lower case it etc..
//           put in curr list
//           currWl.push_back(token)
//       } else if (mode == "person" || mode == "org" ) {
//           tolower
//           currWl.push_back(token)
//       }
    //}

// save for lower case, no punct for search word list (not person org)
// only for terms (not person and org)
//    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
//                   [](unsigned char c) {
//                       c = tolower(c);
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
        // todo remove bypass when parsing wordList.push_back(lowerWord);
    }
}

vector<string> QueryParser::getWordList() {
    // todo remove stub in data
    wordList.push_back("year"); // 1 5 6 9
    wordList.push_back("year"); // 1 5 6 9
    wordList.push_back("1"); // 2 7
    //
    return wordList;
}
vector<string> QueryParser::getPersonList() {
    // todo remove stub in data
    personList.push_back("hoge");
    //
    return personList;
}
vector<string> QueryParser::getOrgList() {
    // todo remove stub in data
    // orgList.push_back("hoge");
    //
    return orgList;
}
vector<string> QueryParser::getNotWordList() {
    // todo remove stub in data
    // notWordList.push_back("notThisWord");
    //
    return notWordList;
}
bool QueryParser::isWordListAnd() {
    return true; // todo
    return wordListAnd;
}

bool QueryParser::isPersonListAnd() {
    return personListAnd;
}

bool QueryParser::isOrgListAnd() {
    return orgListAnd;
}

bool QueryParser::isNotWordListAnd() {
    return notWordListAnd;
}
