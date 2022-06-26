

/**
 * This file contains some simple tests.
 *
 * DO NOT add the #define CATCH_CONFIG_RUNNER to this file.
 * It is already in catch_setup.cpp
 *
 * Note that you can have more than one cpp file with tests in them.
 * For example, you could have a test file for your DSString and a
 * separate one for your DSVector.
 */
#include "catch.hpp"
#include "DSVector.h"
#include "AVLTreeTemplated.h"
#include "stemmer.h"
#include "string"
#include "AVLMap.h"

//TEST_CASE("Testing Templated AVL tree") {
//    //AVL obj
//    AVLTreeTemplated<int> tree;
//    AVLTreeTemplated<std::string> stringTree;
//    SECTION("insert test") {
//        tree.insert(5);
//        tree.insert(6);
//        tree.insert(7);
//        tree.insert(8);
//        tree.print();
//    }SECTION("Deletion test") {
//        std::cout << "DELETION TEST" << std::endl;
//        tree.insert(5);
//        tree.insert(6);
//        tree.insert(7);
//        tree.insert(8);
//        std::cout << std::endl << "Print before deletion: " << std::endl;
//        tree.print();
//        tree.chopDownTree();
//        std::cout << std::endl << "print after deletion call: " << std::endl;
//        tree.print();
//    }SECTION("Testing AVLTree search function") {
//        tree.insert(5);
//        int found = tree.searchTreeCall(5);
//        //REQUIRE(found == true);
//        REQUIRE(found == 5);
//        int secondFind = tree.searchTreeCall(6);
//        //REQUIRE(secondFind == false);
//        REQUIRE(secondFind == 0);
//        //std::string stringSearch = stringTree.searchTreeCall("hello");
//        //REQUIRE(stringSearch == " ");
//    }SECTION("testing insertion of strings into avl tree") {
//       // stringTree.insert("hello");
//       // REQUIRE(stringTree.searchTreeCall("hello") == "hello");
//    }
//
//}

TEST_CASE("Testing AVLMap class"){
    AVLMap <int, std::string> mapTree;

    SECTION("testing insert with AVLMap"){
        int docId = 100;
        std::string word = "tree";
        //int val = 1;
        //mapTree.insert(docId, word); //todo - fix string insertion (getHeight issue?)
        mapTree.insert(docId, word);
        mapTree.insert(101, word);
        std::string found = mapTree.searchTreeCall(docId);
        REQUIRE(found == "tree"); //retrieve val via ID
//        mapTree.insert(5, 8);

    }
}

TEST_CASE("Testing stem") {
    SECTION("Testing stemming of word") {
        std::string wordToStem = "Running";
        //REQUIRE(Porter2Stemmer::stem(wordToStem) == "Run");
        //Porter2Stemmer::stem(wordToStem);
    }
}
