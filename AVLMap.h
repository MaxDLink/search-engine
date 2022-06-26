//
// Created by Max Link on 6/25/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_AVLMAP_H
#define INC_22SU_SEARCH_ENGINE_AVLMAP_H


//
// Created by Max Link on 6/23/22.
//baed AVL tree off of https://github.com/Ekan5h/AVLtree.git

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template<typename K, typename V>
class AVLMap {
    //todo - rule of three for dynamic mem - copy constructor, overloaded assignment op, desturctor (postorder trav delete)
private:
    class AVLNode {

    public:
        K key;
        V val;
        AVLNode *left = nullptr;
        AVLNode *right = nullptr;
        int height = 0;

        //constructor for AVLNode
        AVLNode(); //todo - check if appropriate to make constructor inside AVLNode class
        //overloaded constructor for AVLNode class //todo - check if appropriate for overloading in AVLNode class
        AVLNode(K &keyArg, V &valArg, AVLNode *&leftArg, AVLNode *&rightArg, int &heightArg);

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

    void insert(K key, V val);

    int getHeight(AVLNode *curr);

    //basic insert for a binary search tree
    void insert(AVLNode *&curr, K Key, V Val);

    void rotateWithRightChild(AVLNode *&k1);

    void doubleWithRightChild(AVLNode *&k1);

    void rotateWithLeftChild(AVLNode *&k2);

    void doubleWithLeftChild(AVLNode *&k3);

    int max(int a, int b);

    V searchTree(AVLNode*& root, K& key);

    V searchTreeCall(K key);
};

//overloaded constructor for AVLNode class
template<typename K, typename V>
AVLMap<K, V>::AVLNode::AVLNode(K &keyArg, V &valArg, AVLMap::AVLNode *&leftArg,
                               AVLMap::AVLNode *&rightArg,
                               int &heightArg) {
    //initalizes values to passed in args
    key = keyArg;
    val = valArg;
    left = leftArg;
    right = rightArg;
    height = heightArg;
}

template<typename K, typename V>
AVLMap<K, V>::AVLNode::AVLNode() {
    //initialize all values to null in default constructor & height to zero
    //val; //todo - initialize val  here?
    left = nullptr;
    right = nullptr;
    height = 0;
}

template<typename K, typename V>
void AVLMap<K, V>::print(AVLNode *curr) {
    if (curr != nullptr) {
        print(curr->left);
        cout << curr->key << " ";
        cout << curr->val << " ";
        cout << endl;
        print(curr->right);
    }
}

template<typename K, typename V>
void AVLMap<K, V>::chopDownTree() {
    chopDownTree(root); //todo - delete key value in chopDownTree
}

template<typename K, typename V>
void AVLMap<K, V>::chopDownTree(AVLNode *&curr) {//todo - check if this works as destructor
    if (curr == nullptr) {
        return;
    }
    chopDownTree(curr->left);
    chopDownTree(curr->right);

    delete curr;
    curr = nullptr; //todo - is this null needed?

}


template<typename K, typename V>
void AVLMap<K, V>::print() {
    print(root);
}

template<typename K, typename V>
void AVLMap<K, V>::insert(K key, V val) {
    insert(root, key, val);
}

template<typename K, typename V>
int AVLMap<K, V>::getHeight(AVLNode *curr) {//todo - key value include in getHeight?
    if (curr == nullptr) {
        return -1; //todo - change from -1 to different value to work with all types?
    } else {
        return curr->height;
    }
}

template<typename K, typename T>
void AVLMap<K, T>::insert(AVLNode *&curr, K key, T val) {
    if (curr == nullptr) {//found where new node goes. Base case.
        //curr = new AVLNode(nullptr, nullptr, nullptr, 0);
        curr = new AVLNode;
        curr->key = key;
        curr->val = val;
    } else if (key < curr->key) {//doing both in terms of less than operator
        insert(curr->left, key, val);
       // balancing stuff here - stack unwinding here after new node was inserted
       // inserting from the left so subtract left side from right side
        if (getHeight(curr->left) - getHeight(curr->right) == 2) {
            //figure out if case 1 or case 2 with > or <
            if (key < curr->left->key) { ; //case 1 rotate with left child
            } else { ; // case 2 double rotate with left child
                //todo - case 2 rotation
                doubleWithLeftChild(curr);
            }
        }
    } else if (curr->key < key) {
        insert(curr->right, key, val);
        if (getHeight(curr->right) - getHeight(curr->left) == 2) {
            if (curr->right->key < key)
                rotateWithRightChild(curr);
            else
                doubleWithRightChild(curr);
        }
    } else { ; //todo - handle duplicates here
        //what is in cur?
        //if it is existing, curr->val += val
        // januari 1
        // januari 1,2
        // januari 1,2,...
        cout << curr->key << ":" << curr->val << ", " << val << endl;

        // curr->val += val; //todo - array push
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
    }
}

template<typename K, typename T>
void AVLMap<K, T>::rotateWithRightChild(AVLNode *&k1) {//pointers by reference into the tree
    AVLNode *k2 = k1->right; //k2 like temp variable in a swap function
    k1->right = k2->left; //k1's right pointer point to k2's left child
    k2->left = k1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1; //+1 because one level deeper than lowest children
    k2->height = max(getHeight(k2->right), k1->height) + 1;
    k1 = k2; //move k1 into the place of alpha
}

template<typename K, typename T>
void AVLMap<K, T>::doubleWithRightChild(AVLNode *&k1) {
    rotateWithLeftChild(k1->right); //converts case 3 into case 4
    rotateWithRightChild(k1); //do case 4 rotation
}

template<typename K, typename T>
void AVLMap<K, T>::rotateWithLeftChild(AVLNode *&k2) {
    //magic part 1 //todo - finish rotateWithLeftChild

}

template<typename K, typename T>
void AVLMap<K, T>::doubleWithLeftChild(AVLNode *&k3) {
    //magic part 2 //todo - finish doubleWithLeftChild
}

template<typename K, typename T>
int AVLMap<K, T>::max(int a, int b) {
    return (a < b) ? b : a;
}

template<typename K, typename T>
T AVLMap<K, T>::searchTree(AVLMap::AVLNode *&root, K& key) {
    if(root == nullptr){
        //return false;
        return NULL; //todo - return 0 ok here? or should return different value? throw exception when val not found to keep generic?
    }else if(root->key == key){
        //return true;
        return root->val;
    }else if(root->key > key){
        return searchTree(root->left, key);
    }else{
        return searchTree(root->right, key);
    }

}

template<typename K, typename T>
T AVLMap<K, T>::searchTreeCall(K key) {
    return searchTree(root, key);
}


#endif //INC_22SU_SEARCH_ENGINE_AVLMAP_H
