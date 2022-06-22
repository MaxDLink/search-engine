

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

TEST_CASE("DSVector of Integers", "[DSVec_Int]"){

    /**
     * Things that are at the top of a test case but not inside a section are re-declared before the running of
     * each section.
     */
    DSVector<int> empty_vector;
    DSVector<int> test_vector;
    test_vector.pushBack(10);
    test_vector.pushBack(20);

    SECTION("Testing Empty Vector") {
        REQUIRE(empty_vector.getSize() == 0);
        REQUIRE(test_vector.getSize() != 0);
    }

    SECTION("Testing 10 at first pos and 20 at second") {
        REQUIRE(test_vector[0] == 10);
        REQUIRE(test_vector[1] == 20);
    }

    SECTION("Testing that after pushing back a new element, it is in pos 3") {
        test_vector.pushBack(30);
        CHECK(test_vector[2] == 30);
    }

}