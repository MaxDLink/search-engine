//
// Created by Max Link on 6/22/22.
//

#include "Interface.h"
#include "Index.h"
#include "iostream"
#include "stemmer.h"
#include "QueryParser.h"
#include <sstream>
#include <vector>
#include <set>

using namespace std;

void Interface::userInterface(string &path, set<string> &stopWords, Index &index) {

    string userInput = "1";
    while (userInput != "0") { //userInterface menu in a while loop
        cout << "1. Clear" << endl << "2. Save" << endl
             << "3. Index all Files" << endl << "4. Load" << endl
             << "5. Enter Query (Search)" << endl << "6. Output Statistics" << endl << "0. Quit"
             << endl;

        getline(cin, userInput);

        if (userInput == "1") {//clears the index
            cout << "Clear (clearing index)" << endl;
            index.clear();
        } else if (userInput == "2") {//saves index
            cout << "Save (persist index)" << endl;
            index.save();
        } else if (userInput == "3") {//Indexes all files
            cout << "Index All Files (parsing to populate index)" << endl;
            index.indexAllFiles(path, stopWords);
        } else if (userInput == "4") {//loads file
            cout << "Load (parsing to read from persistence file)" << endl;
            index.load();
        } else if (userInput == "5") {//takes user query
            cout << "enter query here: " << flush;
            string query;
            getline(cin, query);
            index.search(query, stopWords);
        } else if (userInput == "6") {//outputs stats like total number of words & documents parsed
            cout << "Outputting Stats" << endl;
            index.stats();
        }
        cout << endl;
    }
    cout << "exiting program" << endl;
}