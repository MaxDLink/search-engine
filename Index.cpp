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
        //lowercase's person words
        std::transform(key.begin(), key.end(), key.begin(),
                       [](unsigned char c) {
                           return std::tolower(c);
                       });
        set<long> docIds = personTree.searchTreeCall(key);
        docIds.insert(documentId);
        //insert person names into person tree
        personTree.insert(key, docIds);
    }

    // ORGS
    auto orgs = d["entities"]["organizations"].GetArray();
    for (auto &o: orgs) {
        string key = o["name"].GetString();
        //lowercase's org words
        std::transform(key.begin(), key.end(), key.begin(),
                       [](unsigned char c) {
                           return std::tolower(c);
                       });
        set<long> docIds = orgTree.searchTreeCall(key);
        docIds.insert(documentId);
        //inserts org into orgTree
        orgTree.insert(key, docIds);
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
            uniqueWords++; //todo - unique words
            //todo - put lowerWord in lowerFreq map
            //wordFreqMap.insert(lowerWord, docIds);
            wordFreqMap.insert(pair(lowerWord, documentId));

            //todo - put lowerword in idf map
            //idfMap.insert(lowerWord, docIds);
            idfMap.insert(pair(lowerWord, documentId));
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
//    textTree.print();
//    personTree.print();
//    orgTree.print();
    cout << "total # of articles parsed: " << documentIDAndTitle.size() << endl;
    if(documentIDAndTitle.size() == 0){
        uniqueWords = 0;
    }
    cout << "total # of parsed words: " << uniqueWords << endl;
    cout << "Document Id Title size: " << documentIDAndTitle.size() << endl;
    cout << "Document Id FileName size: " << documentIDAndName.size() << endl;
}

void Index::save() { // todo (copy assignment operator)

    personTreeCopy = personTree;

    orgTreeCopy = orgTree;

    textTreeCopy = textTree;
}

void Index::load() { // todo (copy assignment operator)
    personTree = personTreeCopy;
    orgTree = orgTreeCopy;
    textTree = textTreeCopy;
}

void Index::search(string &query, set<std::string> &stopWords) {
    QueryParser qp(query, stopWords);

    vector<string> words = qp.getWordList();
    vector<string> people = qp.getPersonList();
    vector<string> orgs = qp.getOrgList();
    vector<string> notWords = qp.getNotWordList();

    set<long> notWordDocIds;
    set<long> wordDocIds = getDocIds(words, qp.isWordListAnd(), textTree, notWords, notWordDocIds); //year AND people
    set<long> personDocIds = getDocIds(people, qp.isPersonListAnd(), personTree, notWords,
                                       notWordDocIds); //michelle bachelet
    set<long> orgDocIds = getDocIds(orgs, qp.isOrgListAnd(), orgTree, notWords, notWordDocIds);

    //search result ID's
    vector<long> intersection;
    set<long>::iterator itr;
    for (itr = wordDocIds.begin(); itr != wordDocIds.end(); itr++)
        intersection.push_back(*itr);
    //performs intersection with person ID's if personDocId's set is not empty
    if (!personDocIds.empty()) {
        std::set_intersection(wordDocIds.begin(), wordDocIds.end(),
                              personDocIds.begin(), personDocIds.end(),
                              std::back_inserter(intersection));
    }
    //performs intersection with org ID's if org-docId's set is not empty
    if (!orgDocIds.empty()) {
        std::set_intersection(intersection.begin(), intersection.end(),
                              orgDocIds.begin(), orgDocIds.end(),
                              std::back_inserter(intersection));
    }
    //creates the final search result
    set<long> searchResult;
    std::set_difference(intersection.begin(), intersection.end(), notWordDocIds.begin(), notWordDocIds.end(),
                        std::inserter(searchResult, searchResult.end()));
    cout << "SEARCH RESULTS FROM QUERY: " << query << endl;
    //todo - add calculation from ranking (print out sorted ID map) - final set to print out with the correct rankings goes here
    ///qp.getWordList(); <-- list
    ///searchResult
    //TODO - RANK DOCUMENTS BY RELEVANCY //rankByTFIDF(words, searchResult, wordDocIds); //todo - words vector same as qp.getWordList()
//    //print out search results
//    for (long const &Id: searchResult) { std::cout << Id << ' '; }
//    cout << std::endl;
    for (long const &Id: searchResult) { std::cout << "[" << Id << "]" << " " << documentIDAndTitle[Id] << ", " << documentIDAndName[Id] << endl; }
    //todo - enable if above incorrect
//    for (long const &Id: wordDocIds) { std::cout << Id << ' '; }
//    cout << std::endl;

}

set<long> Index::getDocIds(vector<string> words, bool isAnd, AVLTree<string, set<long>> &tree, vector<string> &notWords,
                           set<long> &notWordDocIds) {
    set<long> result;
    set<long> localNotWordIds;
    vector<long> intersection;
    vector<long> notIntersection;
    if (words.size() > 0) {
        result = tree.searchTreeCall(words.at(0));
    }
    //checks not words vector contents
    if (notWords.size() > 0) {
        //check if tree for notWords //todo - notWordDocId's should be kept a global variable & a local var should do this
        localNotWordIds = tree.searchTreeCall(notWords.at(0));
    }
    //continue to check for words, person, or orgs ID's
    for (int i = 1; i < words.size(); i++) {
        set<long> wordDocIds = tree.searchTreeCall(words.at(i));
        //what to do with wordDocs according to andBool
        if (isAnd) {//todo - why does 9 show up here when the query is - YEAR AND people PERSON michelle bachelet
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
        if (isAnd) {
            std::set_intersection(localNotWordIds.begin(), localNotWordIds.end(),
                                  wordDocIds.begin(), wordDocIds.end(), //todo - change to correct sets here
                                  std::back_inserter(notIntersection));
            // need to save for next call through - clear result to replace with contents of intersection vector
            result.clear();
            for (int k = 0; k < notIntersection.size(); k++) {//replace with contents of intersection vector
                localNotWordIds.insert(notIntersection.at(k));
            }
        }
        //if doc ID was retrieved & and bool does not happen then simply merge doc ID's without intersection
        else {
            localNotWordIds.merge(wordDocIds); // or
        }
    }
    //add wordDocId's to notWordDocId's set
//todo - check if notWordDocId's updates correctly
  std::set_union(std::begin(notWordDocIds), std::end(notWordDocIds),
                   std::begin(localNotWordIds), std::end(localNotWordIds),
                   std::inserter(notWordDocIds, std::begin(notWordDocIds)));
    //return result of passed in word, person, or org vector
    return result; //1, 6, 9 for year AND people
}

Index::Index() {
    //default constructor todo - initialize private data members of index???

}

//void Index::rankByTFIDF(vector<string> &words, set<long> &searchResults, set<long>& wordDocIds) {
//    map<long, int> didRank; //map to hold document ID & tfIDF rank
//    vector<long> docIDs;
//    //put set of word docIds into a vector
//    docIDs.assign(wordDocIds.begin(), wordDocIds.end());
//    //do ranking logic for each document in searchResults
//    set<long>::iterator itr; //itr for searchResults
//    int i = 0;
//    for (itr = searchResults.begin(); itr != searchResults.end(); itr++){//go through each search result
//        for(int j = 0; j < words.size(); j++) {//go through each word in each search result
//            //iterator to retrieve value from wordFreqMap
//            std::map<string, long>::iterator fm;
//            //retrieve values out of each map
//            fm = wordFreqMap.find(*itr);
//            //use itr for each document ID
//            int tfIDF = wordFreqMap.size() / idfMap.size(); //calculate TfIDF //todo - check that levels make sense
//            didRank.insert(pair(docIDs.at(i), tfIDF));
//            i++;
//        }
//    }
//
//}
