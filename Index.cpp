//
// Created by Max Link on 6/22/22.
// code for rapidjson filesystem readin https://rapidjson.org/md_doc_stream.html
// code for chrono clocks https://en.cppreference.com/w/cpp/chrono

#include "Index.h"
#include "QueryParser.h"
#include "rapidjson/filereadstream.h"
#include <chrono>
#include <set>
#include <algorithm>
#include <string>
#include "AVLTree.h"

using namespace std;

/**
 * example code for how to traverse the filesystem using std::filesystem
 * @param path an absolute or relative path to a folder containing files
 * you want to parse.
 */

void
Index::indexAllFiles(const char *path, set<std::string> &stopWords) {
    auto start = std::chrono::steady_clock::now();

    //recursive_director_iterator used to "access" folder at parameter -path-
    //we are using the recursive iterator so it will go into subfolders.
    auto it = std::filesystem::recursive_directory_iterator(path);

    //loop over all the entries & store document ID & .json file link in map
    long documentId = 0;
    for (const auto &entry: it) {
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            string jsonLink = entry.path();
            documentId++;
            documentIDAndName.insert(pair<int, string>(documentId, jsonLink));
            readJsonFile(entry.path().c_str(), stopWords, documentId);
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time to index all files: " << elapsed_seconds.count() << "s\n";
}

/**
 * example code that reads and parses a json file and extracts the title and person
 * entities.
 * @param fileName filename with relative or absolute path included.
 */
void Index::readJsonFile(const char *fileName, set<string> stopWords, long &documentId) {
    FILE *fp = fopen(fileName, "r");

    char readBuffer[128000];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    fclose(fp);

    // TITLE
    auto title = d["title"].GetString();
    documentIDAndTitle.insert(pair(documentId, title));

    // PERSONS
    auto persons = d["entities"]["persons"].GetArray();
    for (auto &p: persons) {
        string key = p["name"].GetString();
        std::transform(key.begin(), key.end(), key.begin(),
                       [](unsigned char c) {
                           return std::tolower(c);
                       });
        set<long> docIds = personTree.searchTreeCall(key);
        docIds.insert(documentId);
        personTree.insert(key,
                          docIds); // no operation noop when same; inserts if new    //insert person names into person tree
    }

    // ORGS
    auto orgs = d["entities"]["organizations"].GetArray();
    for (auto &o: orgs) {
        string key = o["name"].GetString();
        std::transform(key.begin(), key.end(), key.begin(),
                       [](unsigned char c) {
                           return std::tolower(c);
                       });
        set<long> docIds = orgTree.searchTreeCall(key);
        docIds.insert(documentId);
        orgTree.insert(key,
                       docIds); // no operation noop when same; inserts if new    //insert person names into person tree
    }

    //vector<string> stopWords;
    vector<string> textContent;
    auto text = d["text"].GetString();
    std::istringstream ss(text);
    string lowerWord;
    while (ss >> lowerWord) { //push all text into a vector to compare to stopwords vector
        // tolower & punctuation & capital word removal
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
                       [](unsigned char c) {
                           c = std::tolower(c);
                           if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9') {
                               return c;
                           } else {
                               return (unsigned char) ' ';
                           }
                       }); // todo put same in Query Parser


        if (!stopWords.count(lowerWord)) {
            Porter2Stemmer::stem(lowerWord);
            set<long> docIds = textTree.searchTreeCall(lowerWord);
            docIds.insert(documentId);
            textTree.insert(lowerWord, docIds);
        }
    }
}

void Index::search(string &query, set<std::string> &stopWords) {
    QueryParser qp(query, stopWords);

    std::vector<std::string> wordVector = qp.termVector();
//    std::vector<std::string> wordVector = qp.wordVector();
//    std::vector<std::string> wordVector = qp.personVector();
//    std::vector<std::string> wordVector = qp.orgVector();
//    std::vector<std::string> wordVector = qp.notWordVector();

//    if (wordVector.empty()) {
//        cout << "query was a stop word" << endl;
//    } else {
//        // todo use qp        index.search(qp);
//    }
    vector<string> words = qp.termVector();
    for (int i = 0; i < words.size(); i++) { //todo - put in org tree & person tree
        set<long> docId = textTree.searchTreeCall(words.at(i));
        //std::cout << words.at(i) << ": ";
        std::cout << "Query: " << words.at(i) << " ";
        for (long const &Id: docId) {
            std::cout << Id << ' ';
        }
        cout << std::endl;

        for (long const &Id: docId) {
            std::cout << documentIDAndTitle[Id] << ", " << documentIDAndName[Id] << endl;
        }
    }
}


