// Name:Lucas Rebelo  


// Table.cpp  Table class implementation


/*
 * Modified 11/22/11 by CMB
 *   changed name of constructor formal parameter to match .h file
 */

#include "Table.h"
#include <iostream>
#include <string>
#include <cassert>


// listFuncs.h has the definition of Node and its methods.  -- when
// you complete it it will also have the function prototypes for your
// list functions.  With this #include, you can use Node type (and
// Node*, and ListType), and call those list functions from inside
// your Table methods, below.

#include "listFuncs.h"


//*************************************************************************


Table::Table() {
	hashSize = HASH_SIZE;
	data = new ListType[hashSize];
	for(int i=0;i<hashSize;i++){
		data[i]=NULL;
	}
	
	numEnt =0;
	nEBuckets = 0;
	longestChain = 0;
}

Table::Table(unsigned int hSize) {
	hashSize = hSize;
	data = new ListType[hashSize];
	for(int i=0;i<hashSize;i++){
		data[i]=NULL;
	}
	numEnt =0;
	nEBuckets = 0;
	longestChain = 0;
}

int * Table::lookup(const string &key) {
  int index = hashCode(key);
  return findInList(data[index],key);  
}

bool Table::remove(const string &key) { 
  //check if present
  if(lookup(key)!=NULL){
  	int index = hashCode(key);
  	bool remove = removeFromList (data[index], key);
  	if(remove == false){//means the entry wasn't there for some reason
  		return false;
  	}else{
  		//update values after removing
  		numEnt--;
  		if(listCount(data[index])==0){
  			nEBuckets--;
  		}
  		longestChain = computeLongestChain();
  		return true;
  	}
  	

  }
  return false;  
}

bool Table::insert(const string &key, int value) { 
  
  //check if present
  if(lookup(key)==NULL){
  	int index = hashCode(key);
  	insertFront(data[index],key, value);
  	int sizeOfList = listCount(data[index]);
  	if(sizeOfList>longestChain){ 
  		longestChain=sizeOfList;
  	}
  	if(sizeOfList==1){
  		nEBuckets++;
  	}
  	numEnt++;
  	return true;
  }else{
  	return false;
  }
}

int Table::numEntries() const {
	return numEnt;
	      
}


void Table::printAll() const { 
	bool empty = true;
	for(int i=0;i<hashSize;i++){
		if(printList(data[i],cout) == true){//printList will handle NULL cases
			empty= false;
		}
	}
	if(empty == true){
		cout << "Table is empty" << endl;
	}
}

void Table::hashStats(ostream &out) const {
   out << "number of buckets: " << hashSize << endl;
   out << "number of entries: " << numEnt << endl;
   out << "number of non-empty buckets: " << nEBuckets << endl;
   out << "longest chain: " << longestChain << endl;
}


// add definitions for your private methods here
unsigned int Table::computeLongestChain() const{
	int longC = 0;
	for(int i=0;i<hashSize;i++){
		int count = listCount(data[i]);//listCount will handle NULL cases
		if(count>longC){
			longC=count;
		}
	}
	return longC;
}
