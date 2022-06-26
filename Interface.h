//
// Created by Max Link on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_INTERFACE_H
#define INC_22SU_SEARCH_ENGINE_INTERFACE_H

#include <set>
class Interface {
private:

public:
    std::vector<std::string> userInterface(std::set<std::string> &stopWords);
};


#endif //INC_22SU_SEARCH_ENGINE_INTERFACE_H
