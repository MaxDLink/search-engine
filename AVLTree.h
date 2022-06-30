//
// Created by Max Link on 6/25/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_AVLTREE_H
#define INC_22SU_SEARCH_ENGINE_AVLTREE_H


//
// Created by Max Link on 6/23/22.
//baed AVL tree off of https://github.com/Ekan5h/AVLtree.git

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template<typename K, typename V>
class AVLTree {
    //todo - rule of three for dynamic mem - copy constructor, overloaded assignment op, desturctor (postorder trav delete)
private:
    //copy constructor
    ///todo - declare in private so that tree never shallow copies
    AVLTree(const AVLTree &obj){}; //todo - enable copy constructor declaration later to prevent shallow copies
    class AVLNode {

    public:
        K key;
        V val;
        AVLNode *left = nullptr;
        AVLNode *right = nullptr;
        int height = 0;

        //constructor for AVLNode
        AVLNode(); //todo - check if appropriate to make constructor inside AVLNode class
        AVLNode(AVLNode * t);
        //assignment operator for AVLNode
        ///V &operator=(const AVLNode *&other); //todo - fixme

        //destructor for AVLNode
        ///~AVLTree(); //todo - fixme
        //overloaded constructor for AVLNode class //todo - check if appropriate for overloading in AVLNode class
        AVLNode(K &keyArg, V &valArg, AVLNode *&leftArg, AVLNode *&rightArg, int &heightArg);

        V copyNodes(AVLNode *t);
    };

    //constructor for AVLNode class
    //AVLNode(V val, AVLNode *left, AVLNode *right, int height) : val(val), left(left), right(right), height(height);
    AVLNode *root = nullptr; //root of the tree
    //print function private
    void print(AVLNode *curr);

public:
    AVLTree();

    void chopDownTree();

    void chopDownTree(AVLNode *&curr);

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

    V searchTree(AVLNode *&root, K &key);

    V searchTreeCall(K key);

    AVLTree<K,V> operator=( const AVLTree & rhs );
};

//overloaded constructor for AVLNode class
template<typename K, typename V>
AVLTree<K, V>::AVLNode::AVLNode(K &keyArg, V &valArg, AVLTree::AVLNode *&leftArg,
                                AVLTree::AVLNode *&rightArg,
                                int &heightArg) {
    //initalizes values to passed in args
    key = keyArg;
    val = valArg;
    left = leftArg;
    right = rightArg;
    height = heightArg;
}

template<typename K, typename V>
AVLTree<K, V>::AVLNode::AVLNode() {
    //initialize all values to null in default constructor & height to zero
    //val; //todo - initialize val  here?
    left = nullptr;
    right = nullptr;
    height = 0;
}

template <typename K, typename V>
V AVLTree<K, V>::AVLNode::copyNodes(AVLNode * t){
    if ( t != NULL )
    {
        AVLNode* left = copyNodes( t->left );
        AVLNode* right = copyNodes( t->right );
        return new AVLNode(t->element, left, right, t->height);
    }
    else
    {
        return NULL;
    }
}

//template<typename K, typename V> //todo - fixme
//V &AVLTree<K, V>::operator=(const AVLTree::AVLNode *&other) {
////    AVLNode* newLeft = nullptr;
////    AVLNode* newRight = nullptr;
////
////    try{
////        newLeft = new AVLNode(*other.left);
////        newRight = new AVLNode(*other.right);
////    }
////    catch(...){
////        //clean up temp objects if there was a problem in try
////        delete newLeft;
////        delete newRight;
////        throw;
////    }
////    //todo - fix block
////    val = other.val;
////    std::swap(left, newLeft);
////    std::swap(right, newRight);
////
////    //now that copied over delete old data
////    delete newLeft;
////    delete newRight;
////
////    return *this;
//    //todo - fix swap
//    other.swap(*this);
//
//    return *this;
//}

//template<typename K, typename V> //todo - fixme
//AVLTree<K, V>::AVLNode::~AVLTree() {
//    //chopDownTree(root);
//
//    //todo - rebalance tree after deletion?
//}

template<typename K, typename V>
void AVLTree<K, V>::print(AVLNode *curr) {
    if (curr != nullptr) {
        print(curr->left);
        cout << curr->key << " ";
        //cout << curr->val[0] << " ";
        std::for_each(curr->val.begin(),
                      curr->val.end(),
                      [](const int &e) {
                          std::cout << e << " ";
                      });
        cout << endl;
        print(curr->right);
    }
}

template<typename K, typename V>
void AVLTree<K, V>::chopDownTree() {
    chopDownTree(root); //todo - delete key value in chopDownTree
}

template<typename K, typename V>
void AVLTree<K, V>::chopDownTree(AVLNode *&curr) {//todo - check if this works as destructor
    if (curr == nullptr) {
        return;
    }
    chopDownTree(curr->left);
    chopDownTree(curr->right);

    delete curr;
    curr = nullptr; //todo - is this null needed?

}

template<typename K, typename V>
void AVLTree<K, V>::print() {
    print(root);
}

template<typename K, typename V>
void AVLTree<K, V>::insert(K key, V val) {
    insert(root, key, val);
}

template<typename K, typename V>
int AVLTree<K, V>::getHeight(AVLNode *curr) {//todo - key value include in getHeight?
    if (curr == nullptr) {
        return -1; //todo - change from -1 to different value to work with all types?
    } else {
        return curr->height;
    }
}

template<typename K, typename T>
void AVLTree<K, T>::insert(AVLNode *&curr, K key, T val) {
    if (curr == nullptr) {//found where new node goes. Base case.
        //curr = new AVLNode(nullptr, nullptr, nullptr, 0);
        curr = new AVLNode;
        curr->key = key;
        curr->val = val;
    } else if (key < curr->key) {//doing both in terms of less than operator
        insert(curr->left, key, val);
        //todo - height correct
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        // balancing stuff here - stack unwinding here after new node was inserted
        // inserting from the left so subtract left side from right side
        if (getHeight(curr->left) - getHeight(curr->right) == 2) {
            //figure out if case 1 or case 2 with > or <
            if (key < curr->left->key) { ; //case 1 rotate with left child
                rotateWithLeftChild(curr);
            } else { ; // case 2 double rotate with left child
                //todo - case 2 rotation
                doubleWithLeftChild(curr);
                //doubleWithRightChild(curr);
                //curr = doubleWithLeftChild;
            }
        }
    } else if (curr->key < key) {
        insert(curr->right, key, val);
        //todo - correct height
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        if (getHeight(curr->right) - getHeight(curr->left) == 2) {
            if (curr->right->key < key)//todo - change back to if tree problems originally: curr->right->key < key
                rotateWithRightChild(curr);
            else
                doubleWithRightChild(curr);
        }
    } else { // key is already in the tree
        // update the value to the new passed in val V
        // januari 1
        // januari 1,2
        // januari 1,2,...
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        curr->val = val;
//        std::cout << "KEY " << curr->key;
//        for (std::set<long>::iterator s = curr->val.begin(); s != curr->val.end(); s++) {
//            cout << ' ' << *s << ' ';
//        }
//        std::cout << std::endl;
    }
}

template<typename K, typename T>
//todo - rename to leftRotation?
void AVLTree<K, T>::rotateWithRightChild(AVLNode *&k1) {//right-right imbalance
    AVLNode *k2 = k1->right; //k2 like temp variable in a swap function
    k1->right = k2->left; //k1's right pointer point to k2's left child
    k2->left = k1;
    //getHeight compares k1->left height & k2->right height & returns greatest height & adds one to account for being one level deeper than lowest child
    //know that max height can only be one level deeper than lowest child in a balanced tree so add one to max height
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1; //+1 because one level deeper than lowest children
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1 = k2; //move k1 into the place of alpha
}

template<typename K, typename T>
//todo - fixme
void AVLTree<K, T>::doubleWithRightChild(AVLNode *&k1) { //L-R imbalance
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
    //    rotateWithLeftChild(k1);
//    rotateWithRightChild(k1->right); ///fixed
    //rotateWithLeftChild(k1);
//    rotateWithLeftChild(k1); //converts case 3 into case 4
//    rotateWithRightChild(k1); //do case 4 rotation
//
//    rotateWithRightChild(k3->left);
//    rotateWithLeftChild(k3);
}

template<typename K, typename T>
//todo - rename to rightRotation?
void AVLTree<K, T>::rotateWithLeftChild(AVLNode *&k2) {//left-left imbalance
//    //magic part 1
    AVLNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = 0;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1; //+1 because one level deeper than lowest children
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k2 = k1;


}

template<typename K, typename T>
void AVLTree<K, T>::doubleWithLeftChild(AVLNode *&k3) {///done
//    rotateWithLeftChild(k3->right); //converts case 3 into case 4 ///test 2
//    rotateWithRightChild(k3); //do case 4 rotation ///test 1
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template<typename K, typename T>
int AVLTree<K, T>::max(int a, int b) {
    return (a < b) ? b : a;
}

template<typename K, typename V>
AVLTree<K, V>::AVLTree() {} //todo - take out this constructor?

template<typename K, typename T>
T AVLTree<K, T>::searchTree(AVLTree::AVLNode *&root, K &key) {
    if (root == nullptr) {
        T obj;
        return obj; //returns empty object of type T
    } else if (root->key == key) {
        return root->val;
    } else if (root->key > key) {
        return searchTree(root->left, key);
    } else {
        return searchTree(root->right, key);
    }

}

template<typename K, typename T>
T AVLTree<K, T>::searchTreeCall(K key) {
    return searchTree(root, key);
}

template <typename K, typename V>
AVLTree<K, V> AVLTree<K,V>::operator=( const AVLTree & rhs ){
    AVLTree copy = rhs;
    //std::swap( *this, copy);
    //copyNodes();
    return *this;
}


#endif //INC_22SU_SEARCH_ENGINE_AVLTREE_H
