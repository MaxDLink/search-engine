//
// Created by Max Link on 6/26/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_QUERYPARSER_H
#define INC_22SU_SEARCH_ENGINE_QUERYPARSER_H

#include <string>
#include <vector>
#include <set>

using namespace std;

class QueryParser {

private:
    vector<string> wordList; //holds words
    bool wordListAnd; //and bool for words

    vector<string> personList; //holds persons
    bool personListAnd; // true if "PERSON p1 AND p1"

    vector<string> orgList; //holds orgs
    bool orgListAnd; // true if "ORG co1 AND co1"

    vector<string> notWordList; //holds not words
    bool notWordListAnd; //AND bool for not words

public:
    QueryParser(string &query, set<string> stopWords); //query parser function
    //getters for word types (word, person, org, not words)
    vector<string> getWordList();
    vector<string> getPersonList();
    vector<string> getOrgList();
    vector<string> getNotWordList();
    //getters for AND bool types (words, person, org)
    bool isWordListAnd();
    bool isPersonListAnd();
    bool isOrgListAnd();
    bool isNotWordListAnd();
};


#endif //INC_22SU_SEARCH_ENGINE_QUERYPARSER_H
