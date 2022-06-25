

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

TEST_CASE("Testing Templated AVL tree"){

    //AVL obj
    AVLTreeTemplated<int> tree;

    SECTION("insert test"){//todo - add tree at function for testing
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
    }

}
