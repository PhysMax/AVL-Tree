#ifndef AVL_TREE_H
#define AVL_TREE_H


#include<iostream>


class node {
private:
    int key;
    unsigned char h;
public:
    node* left;
    node* right;
    node(int k);
    unsigned char height();
    int bfactor();
    void fixheight();
    node* rotateright();
    node* rotateleft();
    node* balance();
    node* insert(int k);
    node* findmin();
    node* removemin();
    node* remove(int k);
    node* find(int k);
    node* clear(); 
};

#endif //AVL_TREE_H