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
    vector<string> wordList;
    bool wordListAnd;

    vector<string> personList;
    bool personListAnd; // true if "PERSON p1 AND p1"

    vector<string> orgList;
    bool orgListAnd; // true if "ORG co1 AND co1"

    vector<string> notWordList;
    bool notWordListAnd;

public:
    QueryParser(string query, set<string> stopWords);
    vector<string> getWordList();
    vector<string> getPersonList();
    vector<string> getOrgList();
    vector<string> getNotWordList();

    bool isWordListAnd();
    bool isPersonListAnd();
    bool isOrgListAnd();
    bool isNotWordListAnd();
};


#endif //INC_22SU_SEARCH_ENGINE_QUERYPARSER_H
