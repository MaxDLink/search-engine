//
// Created by Max Link on 6/26/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_PROJECTTIMINGDEMO_H
#define INC_22SU_SEARCH_ENGINE_PROJECTTIMINGDEMO_H

#include <string>
#include <set>
#include "AVLTree.h"
using namespace std;

class ProjectTimingDemo {

private:
    AVLTree<std::string, std::set<long>> textTree;
    AVLTree<std::string, std::set<long>> emptyTree;

public:
    ProjectTimingDemo(std::string query, std::string absolutePathToDataFilesDir);


};


#endif //INC_22SU_SEARCH_ENGINE_PROJECTTIMINGDEMO_H
