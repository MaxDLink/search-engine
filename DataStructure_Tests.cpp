

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
#include <set>
#include "AVLTree.h"
#include "stemmer.h"
using namespace std;

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

TEST_CASE("Testing AVLTree class"){
    AVLTree <std::string, int> Tree;
    AVLTree<int, int> intTree;
    SECTION("testing insert with AVLTree"){

    }SECTION("Testing AVL Tree balancing R-R case"){///done - height is correctly calculated
//        Tree.insert("a", 0);
//        Tree.insert("b", 1);
//        Tree.insert("c", 2);
    }SECTION("Testing AVL Tree balancing L-L case"){///done - height is correctly calculated
//        Tree.insert("c", 0);
//        Tree.insert("b", 1);
//        Tree.insert("a", 2);
    }SECTION("Testing AVL Tree balancing L-R case"){
        intTree.insert(30, 0);
        intTree.insert(20, 1);
        intTree.insert(25, 2);
    }SECTION("Testing AVL Tree balancing R-L case"){
//        Tree.insert("a", 0);
//        Tree.insert("b", 1);
//        Tree.insert("c", 2);
//        Tree.insert("b", 1);
//        Tree.insert("a", 2);
    }
}
//
//TEST_CASE("Testing stem") {
//    SECTION("Testing stemming of word") {
//        std::string wordToStem = "Running";
//        std::string stemmedWord = Porter2Stemmer::stem(wordToStem);
//        REQUIRE(Porter2Stemmer::stem(wordToStem) == "Run");
//    }
//}
