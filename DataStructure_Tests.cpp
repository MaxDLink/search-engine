

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
TEST_CASE("Testing Templated AVL tree"){

    //AVL obj
    AVLTreeTemplated<int> tree;
    AVLTreeTemplated<std::string> stringTree;
    SECTION("insert test"){
        tree.insert(5);
        tree.insert(6);
        tree.insert(7);
        tree.insert(8);
        tree.print();
    }SECTION("Deletion test"){
        std::cout << "DELETION TEST" << std::endl;
        tree.insert(5);
        tree.insert(6);
        tree.insert(7);
        tree.insert(8);
        std::cout << std::endl << "Print before deletion: " <<std::endl;
        tree.print();
        tree.chopDownTree();
        std::cout << std::endl << "print after deletion call: " << std::endl;
        tree.print();
    }SECTION("Testing AVLTree search function"){
        tree.insert(5);
        int found = tree.searchTreeCall(5);
        //REQUIRE(found == true);
        REQUIRE(found == 5);
        int secondFind = tree.searchTreeCall(6);
        //REQUIRE(secondFind == false);
        REQUIRE(secondFind == 0);
        //std::string stringSearch = stringTree.searchTreeCall("hello");
        //REQUIRE(stringSearch == " ");
    }

}

TEST_CASE("Testing stem"){
    SECTION("Testing stemming of word"){
        std::string wordToStem = "Running";
        //REQUIRE(Porter2Stemmer::stem(wordToStem) == "Run");
       //Porter2Stemmer::stem(wordToStem);
    }
}
