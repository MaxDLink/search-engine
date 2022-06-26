//
// Created by Max Link on 6/26/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_QUERYPARSER_H
#define INC_22SU_SEARCH_ENGINE_QUERYPARSER_H


#include <string>
#include <vector>
#include <set>

class QueryParser {

private:
    std::vector<std::string> queryVector;

public:
    QueryParser(std::string query, std::__1::set<std::string> set);
    std::vector<std::string> termVector();
};


#endif //INC_22SU_SEARCH_ENGINE_QUERYPARSER_H
