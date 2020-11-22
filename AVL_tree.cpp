#include<iostream>

#include "AVL_tree.h"

node::node(int k) {
    key = k; 
    left = right = 0; 
    h = 1; 
}

unsigned char node::height() {
	return this ? h : 0;
}

int node::bfactor() {
	return right->height()-left->height();
}


void node::fixheight() {
	unsigned char hl = left->height();
	unsigned char hr = right->height();
	h = (hl > hr ? hl : hr) + 1;
}


node* node::rotateright() {
	node* q = left;
	left = q->right;
	q->right = this;
	this->fixheight();
	q->fixheight();
	return q;
}

node* node::rotateleft() {
	node* p = right;
	right = p->left;
	p->left = this;
	this->fixheight();
	p->fixheight();
	return p;
}


node* node::balance() {
	this->fixheight();
	if(this->bfactor() == 2) {
		if(right->bfactor() < 0)
			right = right->rotateright();
		return this->rotateleft();
	}
	if(this->bfactor() == -2) {
		if(left->bfactor() > 0)
			left = left->rotateleft();
		return this->rotateright();
	}
	return this; 
}


node* node::insert(int k) {
	if(!this) return new node(k);
	if(k < key)
		left = left->insert(k);
	else
		right = right->insert(k);
	return this->balance();
}


node* node::findmin() {
	return left ? left->findmin() : this;
}


node* node::removemin() {
	if(left == 0)
		return right;
	left = left->removemin();
	return balance();
}


node* node::remove(int k) {
	if(!this) return 0;
	if(k < key)
		left = left->remove(k);
	else if(k > key)
		right = right->remove(k);	
	else
	{
		node* q = left;
		node* r = right;
		delete this;
		if(!r) return q;
		node* min = r->findmin();
		min->right = r->removemin();
		min->left = q;
		return min->balance();
	}
	return balance();
}


node* node::find(int k) {
	if(!this) return 0;
	if(k < key)
		return left->find(k);
	else if(k > key)
		return right->find(k);
	else return this;

}


node* node::clear() {
	if(!this) return 0;
	if (!left && !right) {
		delete this;
		return 0;
	} else {
		left = left->clear();
		right = right->clear();
		delete this;
		return 0;
	}

}