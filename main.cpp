#include<iostream>
#include<chrono>

#include"AVL_tree.h"
#include"check.h"



int main() {
    srand(std::chrono::system_clock::now().time_since_epoch().count());

    int N, step;
    std::cin >> N >> step;

    Checker test(N, step);
    test.check_insert();

}

