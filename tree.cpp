#include<iostream>
#include<utility>
#include <chrono>
#include <cmath>
#include<cstdlib>
#include<vector>


struct node {
    int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { 
        key = k; 
        left = right = 0; 
        height = 1; 
    }
};


unsigned char height(node* p) {
	return p ? p->height : 0;
}

int bfactor(node* p) {
	return height(p->right)-height(p->left);
}


void fixheight(node* p) {
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}


node* rotateright(node* p) {
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) {
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}


node* balance(node* p) {
	fixheight(p);
	if(bfactor(p) == 2) {
		if(bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if(bfactor(p) == -2) {
		if(bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}


node* insert(node* p, int k) {
	if(!p) return new node(k);
	if(k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}


node* findmin(node* p) {
	return p->left ? findmin(p->left) : p;
}


node* removemin(node* p) {
	if(p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}


node* remove(node* p, int k) {
	if(!p) return 0;
	if(k < p->key)
		p->left = remove(p->left, k);
	else if(k > p->key)
		p->right = remove(p->right, k);	
	else
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if(!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

node* find(node* p, int k) {
	if(!p) return 0;
	if(k < p->key)
		return find(p->left, k);
	else if(k > p->key)
		return find(p->right, k);
	else return p;

}


node* clear(node* p) {
	if(!p) return 0;
	if (!p->left && !p->right) {
		delete p;
		return 0;
	} else {
		p->left = clear(p->left);
		p->right = clear(p->right);
		delete p;
		return 0;
	}

}

using namespace std::chrono;


void exp_insert(std::vector<node*> &arr, int N) {
	steady_clock::time_point start, end;
	microseconds time;

    for(int i = 0; i < N; i++) {

	    start = steady_clock::now();
	    for(int j = 1; j < 5 + i * 5; j++) {
			insert(arr[i], rand());
	    }
		end = steady_clock::now();
		time = duration_cast<microseconds>(end - start);
		std::cout << time.count() << std::endl;
		clear(arr[i]);
   }
}

void exp_remove(std::vector<node*> &arr, int N) {
	steady_clock::time_point start, end;
	microseconds time;
	int r, k;

	for(int i = 0; i < N; i++) {
	    for(int j = 1; j < 5 + i * 5; j++) {
			r = rand();
			insert(arr[i], r);
			if (j == 5 + i / 2 * 5) k = r;
	    }
		start = steady_clock::now();
		remove(arr[i], k);
		end = steady_clock::now();
		time = duration_cast<microseconds>(end - start);
		std::cout << time.count() << std::endl;
		clear(arr[i]);
   }
}

void exp_find(std::vector<node*> &arr, int N) {
	steady_clock::time_point start, end;
	microseconds time;
	int r, k;

	for(int i = 0; i < N; i++) {
	    for(int j = 1; j < 5 + i * 5; j++) {
			r = rand();
			insert(arr[i], r);
			if (j == 5 + i / 2 * 5) k = r;
	    }
		start = steady_clock::now();
		find(arr[i], k);
		end = steady_clock::now();
		time = duration_cast<microseconds>(end - start);
		std::cout << time.count() << std::endl;
		clear(arr[i]);
   }
}



int main() {
	srand(system_clock::now().time_since_epoch().count());

	int N = 1000;
	std::vector<node*> arr (N);

	for (int i = 0; i < N; i++) {
		arr[i] = new node(rand());
	}

	exp_insert(arr, N);



}