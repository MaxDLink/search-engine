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



public:
    QueryParser(std::string query, std::__1::set<std::string> set);
    std::vector<std::string> termVector();
};


#endif //INC_22SU_SEARCH_ENGINE_QUERYPARSER_H
