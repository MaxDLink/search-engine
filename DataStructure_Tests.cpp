

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

    SECTION("insert test"){
        tree.insert(5);
        tree.print();
    }SECTION("Deletion test"){


    }

}
