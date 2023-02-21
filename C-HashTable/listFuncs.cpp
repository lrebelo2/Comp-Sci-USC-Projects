// Name:Lucas Rebelo  
// Loginid:rebelo@usc.edu
// CSCI 455 PA5
// Spring 2017


#include <iostream>

#include <cassert>

#include "listFuncs.h"

using namespace std;

Node::Node(const string &theKey, int theValue) {
	key = theKey;
	value = theValue;
	next = NULL;
}

Node::Node(const string &theKey, int theValue, Node *n) {
	key = theKey;
	value = theValue;
	next = n;
}

//*************************************************************************
// put the function definitions for your list functions below

void insertFront(ListType &list, string key, int val) {
	list = new Node(key,val,list);
}

bool printList(ListType list, ostream &out)  {
	if (list != NULL) {

		Node *p = list;
		while (p != NULL) {
			out << "key: " << p->key << " | value: " << p-> value << endl;
			p = p->next;
		}
		return true;
	}else{
		return false;
	}
}

bool removeFromList (ListType &list, string key) {
	if(list != NULL){
		Node *p = list;
		if(p->next == NULL){
			if(p->key == key){
				delete list;
				list=NULL;
				return true;
			}else{
				return false;
			}
		}else{
			if(p->key == key){
				Node* dead = p;
				list=p->next;
				delete dead;
				return true;
			}else{
				
				while (p->next !=NULL) {
					if(p->next->key == key){
						Node* dead = p->next;
						p->next = p->next->next;
						delete dead;
						return true;

					}else{
						p = p->next;
					}
				}
			}
		}
	}
	return false;
}

bool isEmpty(ListType list) {
	if(list == NULL){
		return true;
	}
	return false;
}

int listCount (ListType list) {
	int sum = 0;
	if(list!=NULL){
		Node *p = list;
		while(p!=NULL){
			sum++;
			p=p->next;
		}
	}
	return sum;
}

int * findInList(ListType list, string key){
	if (list != NULL) {
		Node *p = list;
		while (p != NULL) {
			if(p->key == key){
				return &(p->value);
			}else{
				p = p->next;
			}
		}
		return NULL;
	}else{
		return NULL;
	}
}
