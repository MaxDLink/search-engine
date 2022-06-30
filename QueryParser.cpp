//
// Created by Max Link on 6/26/22.
//

#include "QueryParser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "stemmer.h"
#include "vector"
#include "sstream"

using namespace std;

QueryParser::QueryParser(string &query, set<string> stopWords) {
    //lowercase & remove capitals
    istringstream queryAsStream(query);
    string word = query;
    string lowerWord;

    //string query
    //v currWl = wordList
    vector<string>* currWl = &wordList; //pointer to list of words
    string mode = "word"; //mode starts off as word to take in general words
    string token;
    char feed[50];
    while (queryAsStream >> token) {//feed in each word from user phrase & check its mode and bool status
        if (token == "PERSON") {
            currWl = &personList;
            mode = "person"; //detected person keyword so set mode to person
        } else if (token == "ORG") {
            currWl = &orgList;
            mode = "org";
        } else if (token == "AND") {
            if (mode == "word") {
                wordListAnd = true; //detected AND keyword so set wordListAnd == true. if false means that an OR was detected
            } else if (mode == "person") {
                personListAnd = true;
            } else if (mode == "org") {
                orgListAnd = true;
            } else {
                notWordListAnd = true;
            }
        } else if (token == "OR") {//or detected so set wordListAnd to false
            if (mode == "word") {
                wordListAnd = false; //detected AND keyword so set wordListAnd == true. if false means that an OR was detected
            } else if (mode == "person") {
                personListAnd = false;
            } else if (mode == "org") {
                orgListAnd = false;
            } else {
                notWordListAnd = false;
            }
        } else if (token == "NOT") {//detected a not
            currWl = &notWordList;
            mode = "not";
        } else if (mode == "word" || mode == "not") {
            //lower & replace punctuation with blanks
            std::transform(token.begin(), token.end(), token.begin(),
                           [](unsigned char c) {
                               c = std::tolower(c);
                               if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9') {
                                   return c;
                               } else {
                                   return (unsigned char) ' ';
                               }
                           });

            if (!stopWords.count(token)) {//only put in words that are not stopwords & stem/trim to match document words
                Porter2Stemmer::stem(token);
                Porter2Stemmer::trim(token);
                //put words into current word list
                (*currWl).push_back(token);
            }
        } else if (mode == "person" || mode == "org") {
            //lowercase & return token
            std::transform(token.begin(), token.end(), token.begin(),
                           [](unsigned char c) {
                               c = std::tolower(c);
                               return c;
                           });
            //add token to current word list
            (*currWl).push_back(token);
        }
    }

}
//getters for vectors in Index.cpp
vector<string> QueryParser::getWordList() {

    return wordList;
}

vector<string> QueryParser::getPersonList() {
    return personList;
}

vector<string> QueryParser::getOrgList() {
    return orgList;
}

vector<string> QueryParser::getNotWordList() {
    return notWordList;
}
//getters for AND bool for index.cpp
bool QueryParser::isWordListAnd() {
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
