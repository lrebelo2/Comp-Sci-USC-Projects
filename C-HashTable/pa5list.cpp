// Name:Lucas Rebelo  
// Loginid:rebelo@usc.edu
// CSCI 455 PA5
// Spring 2017

// pa5list.cpp
// a program to test the linked list code necessary for a hash table chain

// You are not required to submit this program for pa5.

// We gave you this starter file for it so you don't have to figure
// out the #include stuff.  The code that's being tested will be in
// listFuncs.cpp, which uses the header file listFuncs.h

// The pa5 Makefile includes a rule that compiles these two modules
// into one executable.

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#include "listFuncs.h"
void testEmpty() {
	ListType list;
	list=NULL;
	cout << endl;
	cout << endl;
	cout << "Testing an empty list:"<<endl;
	cout << endl;
    cout << "Is list empty? : " << isEmpty(list) << endl;
    cout << "Number of entries in the list: " << listCount(list) << endl;
    cout << "Printing List:" <<endl;
    printList(list,cout);
    cout << "Attempting to remove key 'foo' :" << removeFromList(list,"foo") << endl;
}

void insertOne() {
	ListType list;
	list = NULL;
	cout << endl;
	cout << endl;
	cout << "Testing list with one entry:"<<endl;
	cout << endl;
	cout << "Inserting 'foo' -> 3 in list" <<endl;
	insertFront(list,"foo",3);
	cout << "Is list empty? : " << isEmpty(list) << endl;
    cout << "Number of entries in the list: " << listCount(list) << endl;
    cout << "Printing List:" <<endl;
    printList(list,cout);
    cout << "Attempting to remove key 'bar' :" << removeFromList(list,"bar") << endl;
    printList(list,cout);
    cout << "Attempting to remove key 'foo' :" << removeFromList(list,"foo") << endl;
    printList(list,cout);


}

void insertMany() {
	ListType list;
	list = NULL;
	cout << endl;
	cout << endl;
	cout << "Testing list with many entries:"<<endl;
	cout << endl;
	cout << "Inserting 'foo' -> 3 in list" <<endl;
	insertFront(list,"foo",3);
	cout << "Inserting 'poop' -> 5 in list" <<endl;
	insertFront(list,"poop",5);
	cout << "Inserting 'pikachu' -> 25 in list" <<endl;
	insertFront(list,"pikachu",25);
	cout << "Inserting 'Joe' -> 1 in list" <<endl;
	insertFront(list,"Joe",1);
		cout << "Inserting 'joe' -> 1 in list" <<endl;
	insertFront(list,"joe",1);
	cout << "Is list empty? : " << isEmpty(list) << endl;
    cout << "Number of entries in the list: " << listCount(list) << endl;
    cout << "Printing List:" <<endl;
    printList(list,cout);
    cout << "Attempting to remove key 'foo' :" << removeFromList(list,"foo") << endl;
    printList(list,cout);
    cout << "Attempting to remove key 'bar' :" << removeFromList(list,"bar") << endl;
    printList(list,cout);
    cout << "Attempting to remove key 'Joe' :" << removeFromList(list,"Joe") << endl;
    printList(list,cout);
    cout << "Attempting to remove key 'joe' :" << removeFromList(list,"joe") << endl;
    printList(list,cout);
    cout << "Attempting to remove key 'poop' :" << removeFromList(list,"poop") << endl;
    printList(list,cout);
    cout << "Attempting to remove key 'pikachu' :" << removeFromList(list,"pikachu") << endl;
    printList(list,cout);
    cout << "Attempting to remove key 'joe' :" << removeFromList(list,"joe") << endl;
    printList(list,cout);


}

int main() {

	//Create empty List and test isEmpty,listCount,printList,removeFromList
	testEmpty();
	//Insert one element in list and test and test isEmpty,listCount,printList,removeFromList (on valid and invalid keys)
	insertOne();
	//Insert a few more elements in list and test isEmpty,listCount,printList,removeFromList (on valid and invalid keys)
	insertMany();
  return 0;
}

