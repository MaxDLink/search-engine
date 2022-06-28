6/22/22 

worked on program terminal userInterface 
worked on parsing words from documents

references:
* stopwords list from https://gist.github.com/larsyencken/1440509
* stringstream string splitting:https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/


6/23/22
* AVL test code
* json parsing
* code for `rapidjson` filesystem readin https://rapidjson.org/md_doc_stream.html

6/24/22
* created templated avl tree class with reference from 

6/25/22
* created search function for AVL tree templated class 
* worked on stemming words



### graveyard 6/26
``` 
    // trim
//        string trimmed;
//        size_t first = lowerWord.find_first_not_of(' ');
//        if (string::npos == first) {
//            trimmed = lowerWord;
//        } else {
//            size_t last = lowerWord.find_last_not_of(' ');
//            trimmed = lowerWord.substr(first, (last - first + 1));
//        }
    //cout << trimmed << endl;

//        for (int i = 0; i < lowerWord.size(); i++) {
//
//            if (tolower(lowerWord.at(i)) >= 'a' && tolower(lowerWord.at(i)) <= 'z' ||
//                tolower(lowerWord.at(i)) >= '0' && tolower(lowerWord.at(i)) <= '9') {
//                lowerWord += tolower(lowerWord.at(i));
//            } else {//continues if punctuation
//                continue;
//            }
//        }
//
//    lowerCaseAndRemovePunct(d, textContent, textTree, documentId, stopWords);
//
//    // removeStopWords(stopWords, textContent, textTree);
//
//    //todo - implement stemming
//    //stemWords(textContent, textTree);
/////    testPrintOutput(textContent);
//
//    //putting words in avl tree
//    //todo - 3 different avl trees (person, org, & text)
//    for (int i = 0; i < textContent.size(); i++) {
//        string key = textContent.at(i);
//        if (key == " ") continue; // stop words are now set to " " so skip
//        set<long> docIds = textTree.searchTreeCall(key);
//        docIds.insert(documentId);
//        textTree.insert(key, docIds);
//    }
//
//    auto end = std::chrono::steady_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end - start;
//    std::cout << "Time to read json files: " << elapsed_seconds.count() << "s\n";
//}

void ReadInData::lowerCaseAndRemovePunct(Document &d, vector<string> &textContent, AVLTree<string, set<long>> &textTree,
                                         long documentId, set<string> &stopWords) {
    ///compare vector of stopwords to vector of text & only print text that is not in stopwords vector
    //get text as a string
    auto start = std::chrono::steady_clock::now();
    auto text = d["text"].GetString();
    std::istringstream ss(text);
    string lowerWord;
    while (ss >> lowerWord) {//push all text into a vector to compare to stopwords vector
        for (int i = 0; i < lowerWord.size(); i++) {//todo - check lower casing for correct words being recorded
            //if(tolower(word.at(i)) >= 'a' && tolower(word.at(i)) <= 'z' || tolower(word.at(i)) >= '0' && tolower(word.at(i)) <= '9'){//lowercases words
            if (tolower(lowerWord.at(i)) >= 'a' && tolower(lowerWord.at(i)) <= 'z' ||
                tolower(lowerWord.at(i)) >= '0' && tolower(lowerWord.at(i)) <= '9') {
                lowerWord += tolower(lowerWord.at(i));
            } else {//continues if punctuation
                continue;
            }
        }
        //removes punctuation from string
//        for (int i = 0; i < lowerWord.size(); i++) {
//            if (ispunct(lowerWord.at(i))) {
//                lowerWord = lowerWord.erase(i, 1); //erases any punctuation from word
//            }
//        }
        //remove stop words
        if (stopWords.count(lowerWord)) {
            lowerWord = " "; //todo - filter out blank spaces from text on file writing
        }
        //stemming
        Porter2Stemmer::stem(lowerWord);
        if (lowerWord != " ") {//check for empty in lowerWord
            textContent.push_back(lowerWord);
            //textTree.insert(lowerWord, documentId); //inserts lower cased words to tree with given documentId
            //todo - avl tree instead of textContent vector
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Time to clean text: " << elapsed_seconds.count() << "s\n";
    }
//    ///print text content to console
//    for(int i = 0; i < textContent.size(); i++){
//        cout << "WORD: " << textContent.at(i) << endl;
//    }
}

void ReadInData::removeStopWords(set<string> &stopWords, vector<string> &text, AVLTree<string, set<long>> &textTree) {

    //loop through and erase stopwords that are found in text vector
    for (int j = 0; j < text.size(); j++) {
        if (stopWords.count(text.at(j))) {
            text.at(j) = " "; //todo - filter out blank spaces from text on file writing

        }
    }

//bool result = std::equal(stopWords.begin(), stopWords.end(), text.begin());
//if(result){
//    text.erase
//}

```

## graveyard 2 6/27/2022
```
/*
cd /Users/maxlink/Desktop/22su-search-engine-max

#build debug
/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/maxlink/Desktop/22su-search-engine-max/cmake-build-debug --target 22su_search_engine
run debug
clear; time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-10
clear; time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-221
clear; time ./cmake-build-debug/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-6000

#build release
/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/maxlink/Desktop/22su-search-engine-max/cmake-build-release --target 22su_search_engine
run release
clear; time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-10
clear; time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-221
clear; time ./cmake-build-release/22su_search_engine year /Users/maxlink/Desktop/sample_data_sets/size-6000

# timer
#  https://en.cppreference.com/w/cpp/chrono

auto start = std::chrono::steady_clock::now();

auto end = std::chrono::steady_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::cout << "FileReadStream: " << elapsed_seconds.count() << "s\n";

 6000 test
 ./cmake-build-release/22su_search_engine year   408.10s user 0.97s system 99% cpu 6:50.44 total

 */
```