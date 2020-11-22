#ifndef CHECK_H
#define CHECK_H

#include<vector>

#include"AVL_tree.h"

class Checker {
private:
    node* tree = 0;
    int N, step, k;
public:
    Checker(int n, int s);
    void assembling(int n);
    void check_insert();
    void check_remove();
    void check_find();
};

#endif //CHECK_H