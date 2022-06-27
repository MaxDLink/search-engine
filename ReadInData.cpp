//
// Created by Max Link on 6/22/22.
// code for rapidjson filesystem readin https://rapidjson.org/md_doc_stream.html
//code for chrono clocks https://en.cppreference.com/w/cpp/chrono

#include "ReadInData.h"
#include "rapidjson/filereadstream.h"
#include <chrono>
#include <set>
#include <algorithm>
#include <map>
#include <string>
#include "AVLTree.h"

/**
 * example code for how to traverse the filesystem using std::filesystem
 * @param path an absolute or relative path to a folder containing files
 * you want to parse.
 */

void
ReadInData::indexAllFiles(const char *path, set<std::string> &stopWords, AVLTree<string, set<long>> &personTree,
                          AVLTree<string, set<long>> &orgTree, AVLTree<string, set<long>> &textTree,
                          set<string> &documentIDAndName) {
//    auto start = std::chrono::steady_clock::now();
    auto start = std::chrono::steady_clock::now();

    //recursive_director_iterator used to "access" folder at parameter -path-
    //we are using the recursive iterator so it will go into subfolders.
    auto it = std::filesystem::recursive_directory_iterator(path);
    //make stopwords vector
    //vector<string> stopWords;
    //std::set<std::string> stopWords;
    //creation of AVLTrees to hold persons, orgs, & text

    // readInStopWords(stopWords);
//    ifstream stopWordsFile("own_file_data_sample/stopwords.txt");
//    if (!stopWordsFile.is_open()) {
//        cout << "Error opening stopWordsFile" << endl;
//    }
//    char stopWordsBuffer[500];
//    //while (stopWordsFile.getline(stopWordsBuffer, 500)) {
//    while (!stopWordsFile.eof()) {
//        stopWordsFile.getline(stopWordsBuffer, 500);
//        string buffer = stopWordsBuffer;
//        stopWords.insert(buffer); //fills stopWords vector with the list of stopwords from the stopWords.txt file
//    }
//
//    stopWordsFile.close();
    //loop over all the entries & store document ID & .json file link in map
    long documentId = 0; //todo - uncomment documentID&Name if errors
    //map<int, std::string> documentIdAndName;
    for (const auto &entry: it) {
//        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            string jsonLink = entry.path().c_str();
//            cout << ".json file: " << jsonLink << endl;
            documentId++;
            documentIDAndName.insert(jsonLink); //put documentID & file.json into map
            //documentId++; //todo - enable documentId++ again here?
            readJsonFile(entry.path().c_str(), stopWords, personTree, orgTree, textTree,
                         documentId); //call to readJsonFile function

        }
    }

//    todo chrono
//    auto end = std::chrono::steady_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end-start;
//    std::cout << "Total parsing elapsed time: " << elapsed_seconds.count() << "s\n";

//    cout << "PERSON TREE" << endl;
//    personTree.print();
//    cout << endl;
//    cout << "ORG TREE: " << endl;
//    //orgTree.print();
//    cout << endl;
//    cout << "TEXT TREE: " << endl;
    //textTree.print();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time to index all files: " << elapsed_seconds.count() << "s\n";
}

/**
 * example code that reads and parses a json file and extracts the title and person
 * entities.
 * @param fileName filename with relative or absolute path included.
 */
void ReadInData::readJsonFile(const char *fileName, set<string> stopWords, AVLTree<string, set<long>> &personTree,
                              AVLTree<string, set<long>> &orgTree,
                              AVLTree<string, set<long>> &textTree, long &documentId) {
    FILE *fp = fopen(fileName, "r");

    char readBuffer[128000];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    fclose(fp);

// toto enable title
//    auto val = d["title"].GetString();
//    cout << "Title: " << val << endl;

// todo PERSONS
//    auto persons = d["entities"]["persons"].GetArray();
////    cout << "  Person Entities:" << endl;
//    for (auto &p: persons) {
////        cout << "    > " << setw(30) << left << p["name"].GetString()
////             << setw(10) << left << p["sentiment"].GetString() << endl;
//        string key = p["name"].GetString();
//        set<long> docIds = personTree.searchTreeCall(key);
//        docIds.insert(documentId);
//        personTree.insert(key, docIds); // no operation noop when same; inserts if new    //insert person names into person tree
//    }

    // TODO enable orgs
//    auto orgs = d["entities"]["organizations"].GetArray();
//    cout << "Organization Entities:" << endl;
//    for (auto &org: orgs) {
//        cout << "    > " << setw(30) << left << org["name"].GetString()
//             << setw(10) << left << org["sentiment"].GetString() << endl;
//        string key = p["name"].GetString();
//        set<long> docIds = personTree.searchTreeCall(key);
//        docIds.insert(documentId);
//        personTree.insert(key, docIds);
//        orgTree.insert(org["name"].GetString(), documentId); //insert org names into org tree
//    }

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
            //Porter2Stemmer::trim(lowerWord); //todo - take stemming away? enable after speed check?
            set<long> docIds = textTree.searchTreeCall(lowerWord);
            docIds.insert(documentId);
            textTree.insert(lowerWord, docIds);
//            cout << lowerWord << endl;
        }
    }
}

void ReadInData::testPrintOutput(vector<string> &text) {
    std::ofstream outputBeforeErase("data/outputBeforeErase.txt");
    if (!outputBeforeErase.is_open()) {
        cout << "Output file before erase failed to open" << endl;
    }
    //writes to output file
    for (auto &i: text) {
        outputBeforeErase << i << endl;
    }

    outputBeforeErase.close();


    std::ofstream textErased;
    textErased.open("data/output.txt");
    if (!textErased.is_open()) {
        cout << "outputfile failed to open" << endl;
    }
    //writes to output file
    for (auto &i: text) {
        textErased << i << endl;
    }

    textErased.close();
    ///print text after stop word removal
//    for(auto t: text){
//        cout << "text after stopWord removal: " << t << endl;
//    }
}

void ReadInData::readInStopWords(std::set<std::string> &stopWords) {
    ifstream stopWordsFile("data/stopwords.txt");
    if (!stopWordsFile.is_open()) {
        cout << "Error opening stopWordsFile" << endl;
    }
    char stopWordsBuffer[500];

    while (!stopWordsFile.eof()) {
        stopWordsFile.getline(stopWordsBuffer, 500);
        string buffer = stopWordsBuffer;
        stopWords.insert(buffer); //fills stopWords vector with the list of stopwords from the stopWords.txt file
    }

    stopWordsFile.close();
}

void ReadInData::wordRetrieveViaQuery(vector<std::string> &query, AVLTree<string, set<long>> &tree, set<string> &documentIdAndName) {
    for (int i = 0; i < query.size(); i++) { //todo - put in org tree & text tree
        set<long> docId = tree.searchTreeCall(query.at(i));
        //std::cout << query.at(i) << ": ";
        std::cout << "Query: " << query.at(i);
        //todo - enable id print again here?
//        for (long const &Id: docId) {
//            std::cout << Id << ' ';
//        }
        cout << std::endl;

        for (const auto &d : documentIdAndName) {//todo - change documentIdAndName back to map after speed test to correlate long id & filepath?
            std::cout << "Document: " << d << '\n';
        }

        //cout << std::endl;
    }
}