/**
 * Summer 2022 Search Engine Template
 * includes some example code related to 2341 final project for summer 2022
 */
/*
 * code references:
 * stopwords list from https://gist.github.com/larsyencken/1440509
 * stringstream string splitting: https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
 *
 */
#include "SearchEngine.h"

using namespace std;

int main(int argc, char *argv[]) {
    string absolutePathToDataFilesDir = argv[1];
    SearchEngine ptd(absolutePathToDataFilesDir); //gives search engine the file path
    return 0;
}