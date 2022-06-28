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
    istringstream queryAsStream(query); //todo - either leave this or change query to istringstream later
    string word = query;
    string lowerWord;
// todo parse the queries

    //string query
    //v currWl = wordList
    vector<string>* currWl = &wordList; //pointer to list of words
    string mode = "word"; //mode starts off as word to take in general words
    string token;
    //string mode; ///todo - set equal to word at first and then change to person mode or org mode accordingly
    char feed[50];
    while (queryAsStream >> token) {///todo - take token in by space with istream or get line
        if (token == "PERSON") {//todo - currWL changes between personList, orgList, & wordList during parsing
            currWl = &personList; //todo figure out what currWl should be set to
            mode = "person"; //detected person keyword so set mode to person
        } else if (token == "ORG") {
            currWl = &orgList; //todo figure out what orgList should be set to
            mode = "org";
        } else if (token == "AND") {
            //todo - mode for all bools
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
            //todo - defaults to false (include each bool false)
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

            if (!stopWords.count(token)) {
                Porter2Stemmer::stem(token);
                Porter2Stemmer::trim(token);
                //put words into current word list
                (*currWl).push_back(token);
            }
        } else if (mode == "person" || mode == "org") {
            //lowercase & return token //todo - double check that person's & org's will never have special punctuation/capitalization
            std::transform(token.begin(), token.end(), token.begin(),
                           [](unsigned char c) {
                               c = std::tolower(c);
                               return c;
                           });
            //add token to current word list
            (*currWl).push_back(token);
        }
    }

///lowercase junk
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

}

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
