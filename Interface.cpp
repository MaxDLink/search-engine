//
// Created by Max Link on 6/22/22.
//

#include "Interface.h"
#include "iostream"
#include "stemmer.h"
#include "QueryParser.h"
#include <sstream>
#include <vector>
#include <set>
std::vector<std::string> Interface::userInterface(std::set<std::string> &stopWords) {
    std::string userInput = "1";
    std::vector<std::string> query;
    while (userInput != "0") {
        std::cout << "1. clear index" << std::endl << "2. manage persistent index" << std::endl
                  << "3. parse to populate index" << std::endl << "4. parse to read from persistence file" << std::endl
                  << "5. enter bool query" << std::endl << "6. output statistics" << std::endl << "0. Quit"
                  << std::endl;

        getline(std::cin, userInput);

        if (userInput == "1") {
            std::cout << "clearing index" << std::endl;
        } else if (userInput == "2") {
            std::cout << "managing persistent index" << std::endl;
        } else if (userInput == "3") {
            std::cout << "parsing to populate index" << std::endl;
        } else if (userInput == "4") {
            std::cout << "parsing to read from persistence file" << std::endl;
        } else if (userInput == "5") {
            std::cout << "enter query here: " << std::flush;
            getline(std::cin, userInput);
            QueryParser qp(userInput, stopWords); // todo implement stem etc.
//            //lowercase & remove capitals
//            std::istringstream ss(userInput);
//           std::string word;
//            while (ss >> word) {//push all text into a vector to compare to stopwords vector
//                std::string lowerWord;
//                for (int i = 0; i < word.size(); i++) {//todo - check lower casing for correct words being recorded
//                    //if(tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z' || tolower(word.at(i)) >= '0' && tolower(word.at(i)) <= '9'){//lowercases words
//                    if (tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z' ||
//                        tolower(word.at(i)) >= '0' && tolower(word.at(i)) <= '9') {
//                        lowerWord += tolower(word.at(i));
//                    } else {//continues if punctuation
//                        continue;
//                    }
//                }
//                //removes punctuation from string
//                for (int i = 0; i < word.size(); i++) {
//                    if (ispunct(word.at(i))) {
//                        word = word.erase(i, 1); //erases any punctuation from word
//                    }
//                }
//                if (lowerWord != "") {//check for empty in lowerWord
//                    query.push_back(lowerWord);
//                    //textTree.insert(lowerWord, documentId); //inserts lower cased words to tree with given documentId
//                    //todo - avl tree instead of textContent vector
//                }
//                //remove stop words
//                for (int j = 0; j < query.size(); j++) {
//                    if (stopWords.count(query.at(j))) {
//                        query.at(j) = " "; //todo - filter out blank spaces from text on file writing
//                    }
//                }
//                //stem word
//                for (int i = 0; i < query.size(); i++) {
//                    Porter2Stemmer::stem(query.at(i));
//                    //todo - stem avlmap instead of textContent
//                }
//            }
//            for(auto q : query)
//                std::cout << q << std::endl;
        } else if (userInput == "6") {
            std::cout << "outputting stats" << std::endl;
        }
        std::cout << std::endl;
        return query;
    }
    return query;
    std::cout << "exiting program" << std::endl;
}