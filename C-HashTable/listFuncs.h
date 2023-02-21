// Name:Lucas Rebelo  
// Loginid:rebelo@usc.edu
// CSCI 455 PA5
// Spring 2017


//*************************************************************************
// Node class definition 
// and declarations for functions on ListType

// Note: we don't need Node in Table.h
// because it's used by the Table class; not by any Table client code.


#ifndef LIST_FUNCS_H
#define LIST_FUNCS_H
  
using namespace std;

struct Node {
  string key;
  int value;

  Node *next;

  Node(const string &theKey, int theValue);

  Node(const string &theKey, int theValue, Node *n);
};


typedef Node * ListType;

//*************************************************************************
//add function headers (aka, function prototypes) for your functions
//that operate on a list here (i.e., each includes a parameter of type
//ListType or ListType&).  No function definitions go in this file.


//Inserts key and value pair in a list
void insertFront(ListType &list, string key,int val); 

//Prints all members of the list in the given stream
// returns false if list is empty
bool printList(ListType list, ostream &out) ;

//Removes the entry corresponding toi the key from the List
// Returns false iff the key wasn't present on the list (returns true otherwise)
bool removeFromList (ListType &list, string key);

//Returns true if list is empty
bool isEmpty(ListType list);

//Returns number of entries in the list
int listCount (ListType list) ;

//Returns the address of the value of corresponding key inside the given list
//returns false iff key not found
int * findInList(ListType list, string key);
// keep the following line at the end of the file
#endif
