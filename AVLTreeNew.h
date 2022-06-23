//
// Created by Max Link on 6/23/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_AVLTREENEW_H
#define INC_22SU_SEARCH_ENGINE_AVLTREENEW_H

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class AVLIntTree {//todo - implement AVL class into binarySearchTree.h
private:
    class AVLNode {
    public:
        int val;
        AVLNode *left = nullptr;
        AVLNode *right = nullptr;
        int height = 0;
    };

    AVLNode *root = nullptr; //root of the tree
    //print function
    void print(AVLNode *curr) {
        if (curr != nullptr) {
            print(curr->left);
            cout << curr->val << " ";
            print(curr->right);
        }
    }

    int getHeight(AVLNode *curr) {
        if (curr == nullptr) {
            return -1;
        } else {
            return curr->height;
        }
    }

    //basic insert for a binary search tree
    void insert(AVLNode *&curr, int x) {
        if (curr == nullptr) {//found where new node goes. Base case.
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

    void rotateWithRightChild(AVLNode *&k1) {//pointers by reference into the tree
        AVLNode *k2 = k1->right; //k2 like temp variable in a swap function
        k1->right = k2->left; //k1's right pointer point to k2's left child
        k2->left = k1;
        k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1; //+1 because one level deeper than lowest children
        k2->height = max(getHeight(k2->right), k1->height) + 1;
        k1 = k2; //move k1 into the place of alpha
    }

    void doubleWithRightChild(AVLNode *&k1) {
        rotateWithLeftChild(k1->right); //converts case 3 into case 4
        rotateWithRightChild(k1); //do case 4 rotation
    }

    void rotateWithLeftChild(AVLNode*& k2){
        //magic part 1

    }

    void doubleWithLeftChild(AVLNode*& k3){
        //magic part 2
    }
    int max(int a, int b) {
        (a < b) ? b : a;
    }

public:
    void print() {//todo - separate definition & header in actual implementation
        print(root);
    }

    void insert(int x) {
        insert(root, x);
    }
};


#endif //INC_22SU_SEARCH_ENGINE_AVLTREENEW_H
