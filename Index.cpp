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
Index::indexAllFiles(string path, set<std::string> &stopWords) {
    auto start = std::chrono::steady_clock::now();

    //recursive_director_iterator used to "access" folder at parameter -path-
    //we are using the recursive iterator so it will go into subfolders.
    auto it = std::filesystem::recursive_directory_iterator(path.c_str());

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
void Index::readJsonFile(string fileName, set<string> stopWords, long &documentId) {
    FILE *fp = fopen(fileName.c_str(), "r");

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
        // tolower & replace punctuation with blanks
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
                       [](unsigned char c) {
                           c = std::tolower(c);
                           if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9') {
                               return c;
                           } else {
                               return (unsigned char) ' ';
                           }
                       });


        if (!stopWords.count(lowerWord)) {
            Porter2Stemmer::stem(lowerWord);
            set<long> docIds = textTree.searchTreeCall(lowerWord);
            docIds.insert(documentId);
            textTree.insert(lowerWord, docIds);
        }
    }
}

void Index::clear() {
    textTree.chopDownTree();
    personTree.chopDownTree();
    orgTree.chopDownTree();

    documentIDAndName.clear();
    documentIDAndTitle.clear();
}

void Index::stats() {
    textTree.print();
    personTree.print();
    orgTree.print();
    cout << "Document Id Title size: " << documentIDAndTitle.size() << endl;
    cout << "Document Id FileName size: " << documentIDAndName.size() << endl;
}

void Index::save() { // todo (copy assignment operator)
}

void Index::load() { // todo (copy assignment operator)
}

void Index::search(string &query, set<std::string> &stopWords) {
    QueryParser qp(query, stopWords);

    vector<string> words = qp.getWordList();
    vector<string> people = qp.getPersonList();
    vector<string> orgs = qp.getOrgList();
    vector<string> notWords = qp.getNotWordList();
    //todo - do testing with these sets
    set<long> notWordDocIds;
    set<long> wordDocIds = getDocIds(words, qp.isWordListAnd(), textTree, notWords, notWordDocIds); //year AND people
    set<long> personDocIds = getDocIds(people, qp.isPersonListAnd(), personTree, notWords,
                                       notWordDocIds); //michelle bachelet
    set<long> orgDocIds = getDocIds(orgs, qp.isOrgListAnd(), orgTree, notWords, notWordDocIds); //

    //set<long> notWordDocIds = getDocIds(notWords, qp.isNotWordListAnd(), notTree); //todo - not words stored in every tree so search every tree for not word ID's

    //search result ID's
    vector<long> intersection;
    set<long>::iterator itr; //todo - iterate through wordsDocId's set & put into intersection vector for intersection operations
    for(itr = wordDocIds.begin(); itr != wordDocIds.end(); itr++)
    intersection.push_back(*itr);
//todo - this intersection should happen if people have ID's
    if (!personDocIds.empty()) {
        std::set_intersection(wordDocIds.begin(), wordDocIds.end(),
                              personDocIds.begin(), personDocIds.end(),
                              std::back_inserter(intersection));
    }
    //todo - result = if org words inserted then take line 155 result & intersect with org words here
    if(!orgDocIds.empty()){//todo - can vector intersection be used correctly in set_intersection?
        std::set_intersection(intersection.begin(), intersection.end(),
                              orgDocIds.begin(), orgDocIds.end(),
                              std::back_inserter(intersection));
    }
//    //todo - subtract not words from result from line 156 (subtract notWords vector from result - google)
//    //todo - use set difference from #include <algorithm> to get difference between searchResult set & notWordDocId's set
    set<long> searchResult;
    std::set_difference(intersection.begin(), intersection.end(), notWordDocIds.begin(), notWordDocIds.end(),
                        std::inserter(searchResult, searchResult.end()));
//    //print out search results
    for (long const &Id: searchResult) { std::cout << Id << ' '; }
    cout << std::endl;
    for (long const &Id: searchResult) { std::cout << documentIDAndTitle[Id] << ", " << documentIDAndName[Id] << endl; }
    //todo - enable if above incorrect
//    for (long const &Id: wordDocIds) { std::cout << Id << ' '; }
//    cout << std::endl;

}

set<long> Index::getDocIds(vector<string> words, bool isAnd, AVLTree<string, set<long>> &tree, vector<string> &notWords,
                           set<long> &notWordDocIds) {
    set<long> result;
    vector<long> intersection;

    if (words.size() >
        0) { //todo - search diff trees. Word vector = textTree, org vect = orgTree, personVect = personTree
        result = tree.searchTreeCall(words.at(0));

    } else if (notWords.size() > 0) {
        //check if tree for notWords
        notWordDocIds = tree.searchTreeCall(notWords.at(0));
    }
    //continue to check for words, person, or orgs ID's
    for (int i = 1; i < words.size(); i++) {
        set<long> wordDocIds = tree.searchTreeCall(words.at(i));
        //what to do with wordDocs according to andBool
        if (isAnd) {//todo -set_intersection should be null if words following true and bool not found?
            std::set_intersection(result.begin(), result.end(),
                                  wordDocIds.begin(), wordDocIds.end(),
                                  std::back_inserter(intersection));
            // need to save for next call through - clear result to replace with contents of intersection vector
            result.clear();
            for (int k = 0; k < intersection.size(); k++) {//replace with contents of intersection vector
                result.insert(intersection.at(k));
            }
        } else {
            result.merge(wordDocIds); // or
        }
    }

    //continue to check for not words
    for (int i = 1; i < notWords.size(); i++) {
        set<long> wordDocIds = tree.searchTreeCall(notWords.at(i));
        //what to do with wordDocs according to andBool
        if (isAnd) {//todo -set_intersection should be null if words following true and bool not found?
            std::set_intersection(notWordDocIds.begin(), notWordDocIds.end(),
                                  notWordDocIds.begin(), notWordDocIds.end(),
                                  std::back_inserter(intersection));
            // need to save for next call through - clear result to replace with contents of intersection vector
            result.clear();
            for (int k = 0; k < intersection.size(); k++) {//replace with contents of intersection vector
                notWordDocIds.insert(intersection.at(k));
            }
        } else {
            notWordDocIds.merge(wordDocIds); // or
        }
    }
    //return result of passed in word, person, or org vector
    return result; //1, 6, 9 for year AND people
}

Index::Index() {
    //default constructor todo - initialize private data members of index???

}
