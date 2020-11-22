#include<iostream>
#include<fstream>
#include<chrono>
#include<vector>
#include<cstdlib>
#include<fstream>

#include"check.h"
#include"AVL_tree.h"



using namespace std::chrono;


Checker::Checker(int n, int s) {
    step = s;
    N = n;

}

void Checker::assembling(int n) {
    int r;
    tree = tree->clear();
    for(int i = 0; i < n; i++) {
        r = rand();
        tree = tree->insert(r);
        if (i == n / 2) k = r;
    }

}

void Checker::check_insert() {
    steady_clock::time_point start, end;
	nanoseconds time;

    std::ofstream fout;
    fout.open("data.txt");


    for (int i = 1; i <= N; i++) {
        assembling(i * step);

        start = steady_clock::now();
        tree = tree->insert(rand());
        end = steady_clock::now();

        time = duration_cast<nanoseconds>(end - start);
        fout << time.count() << std::endl;                   
    }
    fout.close();
}

void Checker::check_find() {
    steady_clock::time_point start, end;
	nanoseconds time;

    std::ofstream fout;
    fout.open("data.txt");


    for (int i = 1; i <= N; i++) {
        assembling(i * step);

        start = steady_clock::now();
        tree->find(k);
        end = steady_clock::now();

        time = duration_cast<nanoseconds>(end - start);
        fout << time.count() << std::endl;                   
    }
    fout.close();
}

void Checker::check_remove() {
    steady_clock::time_point start, end;
	nanoseconds time;

    std::ofstream fout;
    fout.open("data.txt");


    for (int i = 1; i <= N; i++) {
        assembling(i * step);

        start = steady_clock::now();
        tree = tree->remove(k);
        end = steady_clock::now();

        time = duration_cast<nanoseconds>(end - start);
        fout << time.count() << std::endl;                   
    }
    fout.close();
}