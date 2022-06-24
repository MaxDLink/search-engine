//
// Created by Max Link on 6/22/22.
// code for rapidjson filesystem readin https://rapidjson.org/md_doc_stream.html
//

#include "ReadInData.h"
#include "rapidjson/filereadstream.h"
#include <chrono>
#include <set>
#include <algorithm>
#include <map>
#include <string>

/**
 * example code for how to traverse the filesystem using std::filesystem
 * @param path an absolute or relative path to a folder containing files
 * you want to parse.
 */

void ReadInData::indexAllFiles(const char *path) {
    auto start = std::chrono::steady_clock::now();

    //recursive_director_iterator used to "access" folder at parameter -path-
    //we are using the recursive iterator so it will go into subfolders.
    auto it = std::filesystem::recursive_directory_iterator(path);
    //make stopwords vector
    //vector<string> stopWords;
    std::set<std::string> stopWords;

    ifstream stopWordsFile("own_file_data_sample/stopwords.txt");
    if (!stopWordsFile.is_open()) {
        cout << "Error opening stopWordsFile" << endl;
    }
    char stopWordsBuffer[500];
    //while (stopWordsFile.getline(stopWordsBuffer, 500)) {
    while (!stopWordsFile.eof()) {
        stopWordsFile.getline(stopWordsBuffer, 500);
        string buffer = stopWordsBuffer;
        stopWords.insert(buffer); //fills stopWords vector with the list of stopwords from the stopWords.txt file
    }

    stopWordsFile.close();
    //loop over all the entries.
    for (const auto &entry: it) {
//        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            readJsonFile(entry.path().c_str(), stopWords); //call to readJsonFile function
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Total parsing elapsed time: " << elapsed_seconds.count() << "s\n";
}

/**
 * example code that reads and parses a json file and extracts the title and person
 * entities.
 * @param fileName filename with relative or absolute path included.
 */
void ReadInData::readJsonFile(const char *fileName, set<string> stopWords) {

    auto start = std::chrono::steady_clock::now();


//    https://en.cppreference.com/w/cpp/chrono


    FILE *fp = fopen(fileName, "r");

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);
    fclose(fp);


    auto val = d["title"].GetString();
//    cout << "Title: " << val << endl;

    auto persons = d["entities"]["persons"].GetArray();
//    cout << "  Person Entities:" << endl;
    for (auto &p: persons) {
//        cout << "    > " << setw(30) << left << p["name"].GetString()
//             << setw(10) << left << p["sentiment"].GetString() << endl;
    }

    auto orgs = d["entities"]["organizations"].GetArray();
//    cout << "Organization Entities:" << endl;
    for (auto &org: orgs) {
//        cout << "    > " << setw(30) << left << org["name"].GetString()
//             << setw(10) << left << org["sentiment"].GetString() << endl;
    }

    //vector<string> stopWords;
    vector<string> textContent;

    lowerCaseAndRemovePunct(d, textContent);

    //removeStopWords(stopWords, textContent);

///    testPrintOutput(textContent);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "jsonFileParse elapsed time: " << elapsed_seconds.count() << "s\n";
}

void ReadInData::lowerCaseAndRemovePunct(Document &d, vector<string> &textContent) {
    ///compare vector of stopwords to vector of text & only print text that is not in stopwords vector
    //get text as a string
    auto text = d["text"].GetString();
    std::istringstream ss(text);
    string word;
    while (ss >> word) {//push all text into a vector to compare to stopwords vector
        string lowerWord;
        for (int i = 0; i < word.size(); i++) {
            //todo - include numbers in for word concatination???
            //if(tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z' || tolower(word.at(i)) >= '0' && tolower(word.at(i)) <= '9'){//lowercases words
            if (tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z') {
                lowerWord += tolower(word.at(i));
            } else {//continues if punctuation
                continue;
            }
        }
        //removes punctuation from string
        for (int i = 0; i < word.size(); i++) {
            if (ispunct(word.at(i))) {
                word = word.erase(i, 1); //erases any punctuation from word
            }
        }
        if (lowerWord != "") {//check for empty in lowerWord
            textContent.push_back(lowerWord);
        }

    }
}

void ReadInData::removeStopWords(set<string> &stopWords, vector<string> &text) {

    //loop through and erase stopwords that are found in text vector
        for (int j = 0; j < text.size(); j++) {
            if (stopWords.count(text.at(j))) {
                text.at(j) = " ";
            }
        }

//bool result = std::equal(stopWords.begin(), stopWords.end(), text.begin());
//if(result){
//    text.erase
//}

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

