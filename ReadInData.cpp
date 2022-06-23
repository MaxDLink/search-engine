//
// Created by Max Link on 6/22/22.
//

#include "ReadInData.h"

/**
 * example code that reads and parses a json file and extracts the title and person
 * entities.
 * @param fileName filename with relative or absolute path included.
 */
void ReadInData::testReadJsonFile(const char *fileName) {

    //open an ifstream on the file of interest and check that it could be opened.
    ifstream input(fileName);
    if (!input.is_open())
        std::cerr << "cannot open file" << endl;

    //Create a RapidJSON IStreamWrapper using the file input stream above.
    IStreamWrapper isw(input);

    //Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    Document d;
    d.ParseStream(isw);

    //Now that the document is parsed, we can access different elements the JSON using
    //familiar subscript notation.

    //This accesses the -title- element in the JSON. Since the value associated with title is a string (rather than
    // an array or something else), we call the GetString() function to return the actual title of the article
    // as a c-string.
    //
    auto val = d["title"].GetString();
    cout << "Title: " << val << endl;

    //The Persons entity for which you're building a specific inverted index is contained in
    // top level -entities- element.  So that's why we subscript with ["entities"]["persons"].
    // The value associated with entities>persons is an array.  So we call GetArray() to get
    // an iterable collection of elements
    auto persons = d["entities"]["persons"].GetArray();

    //We iterate over the Array returned from the line above.  Each element kind of operates like
    // a little JSON document object in that you can use the same subscript notation
    // to access particular values.
    cout << "  Person Entities:" << endl;
    for (auto &p: persons) {
        cout << "    > " << setw(30) << left << p["name"].GetString()
             << setw(10) << left << p["sentiment"].GetString() << endl;
    }
    //grabs organization entities
    auto orgs = d["entities"]["organizations"].GetArray();
    cout << "Organization Entities:" << endl;
    for (auto &org: orgs) {
        cout << "    > " << setw(30) << left << org["name"].GetString()
             << setw(10) << left << org["sentiment"].GetString() << endl;
    }

    //todo - break up this function & organize it better
    vector<string> stopWords;
    vector<string> textContent;
    ///compare vector of stopwords to vector of text & only print text that is not in stopwords vector
    //get text as a string
    auto text = d["text"].GetString();
    std::istringstream ss(text);
    string word;
    while (ss >> word) {//push all text into a vector to compare to stopwords vector
        string lowerWord;
        for(int i = 0; i < word.size(); i++){
            //todo - lower into var here first then push to vector if good
            if(tolower(word.at(i)) >= 'a' || tolower(word.at(i)) <= 'z'){//lowercases words
                lowerWord += tolower(word.at(i));
            }else{//continues if punctuation
                continue;
            }
        }
        //todo - remove punctuation from string
        for(int i = 0; i < word.size(); i++) {
            if (ispunct(word.at(i))) {
               lowerWord = word.erase(i, 1); //erases any punctuation from word fixme
            }
        }
        textContent.push_back(lowerWord);
    }
    input.close();

    ifstream stopWordsFile("own_file_data_sample/stopwords.txt");
    if (!stopWordsFile.is_open()) {
        cout << "Error opening stopWordsFile" << endl;
    }
    char stopWordsBuffer[500];
    //while (stopWordsFile.getline(stopWordsBuffer, 500)) {
    while (!stopWordsFile.eof()) {
        stopWordsFile.getline(stopWordsBuffer, 500);
        stopWords.push_back(
                stopWordsBuffer); //fills stopWords vector with the list of stopwords from the stopWords.txt file
    }

    stopWordsFile.close();
    std::ofstream outputBeforeErase("data/outputBeforeErase.txt");
    if(!outputBeforeErase.is_open()){
        cout << "Output file before erase failed to open" << endl;
    }
    for(auto& i : textContent){
        outputBeforeErase << i << endl;
    }

    outputBeforeErase.close();
    //loop through and erase stopwords that are found in textContent vector
    for (int i = 0; i < stopWords.size(); i++) {
        for (int j = 0; j < textContent.size(); j++) {
            if (textContent.at(j) == stopWords.at(i)) {
                textContent.erase(textContent.begin() + j);
            }
        }
    }

    std::ofstream textErased;
    textErased.open("data/output.txt");
    if(!textErased.is_open()){
        cout << "outputfile failed to open" << endl;
    }
    for(auto & i : textContent){
        textErased << i << endl;
    }

    textErased.close();
    ///print text after stop word removal
//    for(auto t: textContent){
//        cout << "text after stopWord removal: " << t << endl;
//    }


}


/**
 * example code for how to traverse the filesystem using std::filesystem
 * @param path an absolute or relative path to a folder containing files
 * you want to parse.
 */




void ReadInData::testFileSystem(const char *path) {

    //recursive_director_iterator used to "access" folder at parameter -path-
    //we are using the recursive iterator so it will go into subfolders.
    auto it = std::filesystem::recursive_directory_iterator(path);

    //loop over all the entries.
    for (const auto &entry: it) {

        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;

        //We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            testReadJsonFile(entry.path().c_str());
        }

    }


}