cmake_minimum_required(VERSION 3.14)
project(22su_search_engine)

set(CMAKE_CXX_STANDARD 20)
set(input01 "data/stopwords.txt")
# The configure_file statements below ensure that files are copied into the data
# folder that will be created in the build folder.
file(COPY sample_data/ DESTINATION sample_data/)
file(COPY own_file_data_sample/ DESTINATION own_file_data_sample)
file(COPY data/stopWords2.txt DESTINATION data/stopWords2.txt)
foreach(file IN LISTS input01)
    configure_file(${file} ${file} COPYONLY)
endforeach()
# This target is for the main project.  Add in any additional files you need or that you're copying
# over from a previous project.
add_executable(22su_search_engine main.cpp DSVector.h Interface.cpp Interface.h stemmer.cpp stemmer.h ReadInData.cpp ReadInData.h BinarySearchTree.h AVLTreeNew.h AVLTreeTemplated.h tempTestAVLTree.h AVLTemplatedMap.h)

# this is the testing target.  Don't include your main driver.cpp file in this target.
add_executable(22su_search_engine_tests DSVector.h catch.hpp catch_setup.cpp DataStructure_Tests.cpp catch_setup.h BinarySearchTree.h AVLTreeTemplated.h AVLTemplatedMap.h)