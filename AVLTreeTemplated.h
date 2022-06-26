//
// Created by Max Link on 6/23/22.
//baed AVL tree off of https://github.com/Ekan5h/AVLtree.git

#ifndef INC_22SU_SEARCH_ENGINE_AVLTREENEW_H
#define INC_22SU_SEARCH_ENGINE_AVLTREENEW_H

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template<typename T>
class AVLTreeTemplated {
    //todo - rule of three for dynamic mem - copy constructor, overloaded assignment op, desturctor (postorder trav delete)
private:
    class AVLNode {

    public:
        T val;
        AVLNode *left = nullptr;
        AVLNode *right = nullptr;
        int height = 0;

        //constructor for AVLNode
        AVLNode(); //todo - check if appropriate to make constructor inside AVLNode class
        //overloaded constructor for AVLNode class //todo - check if appropriate for overloading in AVLNode class
        AVLNode(T &valArg, AVLNode *&leftArg, AVLNode *&rightArg, int &heightArg);

    };

    //constructor for AVLNode class
    //AVLNode(V val, AVLNode *left, AVLNode *right, int height) : val(val), left(left), right(right), height(height) {}

    AVLNode *root = nullptr; //root of the tree
    //print function private
    void print(AVLNode *curr);

public:
    void chopDownTree();
    void chopDownTree(AVLNode *&curr);
    //void chopDownTree();
    //todo - overloaded assignment operator, copy constructor

    void print();

    void insert(T x);

    T getHeight(AVLNode *curr);

    //basic insert for a binary search tree
    void insert(AVLNode *&curr, T x);

    void rotateWithRightChild(AVLNode *&k1);

    void doubleWithRightChild(AVLNode *&k1);

    void rotateWithLeftChild(AVLNode *&k2);

    void doubleWithLeftChild(AVLNode *&k3);

    T max(T a, T b);

    T searchTree(AVLNode*& root, T valKey);

    T searchTreeCall(T key);
};

//overloaded constructor for AVLNode class
template<typename T>
AVLTreeTemplated<T>::AVLNode::AVLNode(T &valArg, AVLTreeTemplated::AVLNode *&leftArg,
                                      AVLTreeTemplated::AVLNode *&rightArg,
                                      int &heightArg) {
    //initalizes values to passed in args
    val = valArg;
    left = leftArg;
    right = rightArg;
    height = heightArg;
}

template<typename T>
AVLTreeTemplated<T>::AVLNode::AVLNode() {
    //initialize all values to null in default constructor & height to zero
    //val; //todo - initialize val  here?
    left = nullptr;
    right = nullptr;
    height = 0;
}

template<typename T>
void AVLTreeTemplated<T>::print(AVLNode *curr) {
    if (curr != nullptr) {
        print(curr->left);
        cout << curr->val << " ";
        print(curr->right);
    }
}

template<typename T>
void AVLTreeTemplated<T>::chopDownTree() {
    chopDownTree(root);
}

template<typename T>
void AVLTreeTemplated<T>::chopDownTree(AVLNode *&curr) {//todo - check if this works as destructor
    if (curr == nullptr) {
        return;
    }
    chopDownTree(curr->left);
    chopDownTree(curr->right);

    delete curr;
    curr = nullptr; //todo - is this null needed?

}


template<typename T>
void AVLTreeTemplated<T>::print() {
    print(root);
}

template<typename T>
void AVLTreeTemplated<T>::insert(T x) {
    insert(root, x);
}

template<typename T>
T AVLTreeTemplated<T>::getHeight(AVLNode *curr) {
    if (curr == nullptr) {
        return NULL; //todo - change back to -1?
    } else {
        return curr->height;
    }
}

template<typename T>
void AVLTreeTemplated<T>::insert(AVLNode *&curr, T x) {
    if (curr == nullptr) {//found where new node goes. Base case.
        //curr = new AVLNode(nullptr, nullptr, nullptr, 0);
        curr = new AVLNode;
        curr->val = x;
    } else if (x < curr->val) {//doing both in terms of less than operator
        insert(curr->left, x);
        //balancing stuff here - stack unwinding here after new node was inserted
        //inserting from the left so subtract left side from right side
        if (getHeight(curr->left) - getHeight(curr->right) == 2) {
            //figure out if case 1 or case 2 with > or <
            if (x < curr->left->val) { ; //case 1 rotate with left child
            } else { ; // case 2 double rotate with left child
                //todo - case 2 rotation
                doubleWithLeftChild(curr);
            }
        }
    } else if (curr->val < x) {
        insert(curr->right, x);
        if (getHeight(curr->right) - getHeight(curr->left) == 2) {
            if (curr->right->val < x)
                rotateWithRightChild(curr);
            else
                doubleWithRightChild(curr);
        }
    } else { ; //todo - handle duplicates here
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
    }
}

template<typename T>
void AVLTreeTemplated<T>::rotateWithRightChild(AVLNode *&k1) {//pointers by reference into the tree
    AVLNode *k2 = k1->right; //k2 like temp variable in a swap function
    k1->right = k2->left; //k1's right pointer point to k2's left child
    k2->left = k1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1; //+1 because one level deeper than lowest children
    k2->height = max(getHeight(k2->right), k1->height) + 1;
    k1 = k2; //move k1 into the place of alpha
}

template<typename T>
void AVLTreeTemplated<T>::doubleWithRightChild(AVLNode *&k1) {
    rotateWithLeftChild(k1->right); //converts case 3 into case 4
    rotateWithRightChild(k1); //do case 4 rotation
}

template<typename T>
void AVLTreeTemplated<T>::rotateWithLeftChild(AVLNode *&k2) {
    //magic part 1 //todo - finish rotateWithLeftChild

}

template<typename T>
void AVLTreeTemplated<T>::doubleWithLeftChild(AVLNode *&k3) {
    //magic part 2 //todo - finish doubleWithLeftChild
}

template<typename T>
T AVLTreeTemplated<T>::max(T a, T b) {
    (a < b) ? b : a;
}

template<typename T>
T AVLTreeTemplated<T>::searchTree(AVLTreeTemplated::AVLNode *&root, T valKey) {
    if(root == nullptr){
        //return false;
        return NULL; //todo - return 0 ok here? or should return different value? throw exception when val not found to keep generic?
    }else if(root->val == valKey){
        //return true;
        return root->val;
    }else if(root->val > valKey){
        return searchTree(root->left, valKey);
    }else{
        return searchTree(root->right, valKey);
    }

}

template<typename T>
T AVLTreeTemplated<T>::searchTreeCall(T key) {
    return searchTree(root, key);
}


#endif //INC_22SU_SEARCH_ENGINE_AVLTREENEW_H
