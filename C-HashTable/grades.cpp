// Name:Lucas Rebelo  
// Loginid:rebelo@usc.edu
// CSCI 455 PA5
// Spring 2017

/*
 * grades.cpp
 * A program to test the Table class.
 * How to run it:
 *      grades [hashSize]
 * 
 * the optional argument hashSize is the size of hash table to use.
 * if it's not given, the program uses default size (Table::HASH_SIZE)
 *
 */

#include "Table.h"

// cstdlib needed for call to atoi
#include <cstdlib>
#include <iostream>

void help() {
  cout << "List of available commands:" << endl;
  cout << "insert <name> <score>:      Inserts student with name <name> and respective <score> in the grade table" << endl;
  cout << "change <name> <newscore>:   Change the score of student with name <name> in the grade table to <newscore>" << endl;
  cout << "lookup <name>:              Looks up the student with name <name> in the grade table and prints the respective score" << endl;
  cout << "remove <name>:              Removes student with name <name> grom the grade table" << endl;
  cout << "print:                      Prints contents of grade table" << endl;
  cout << "size:                       Prints the size of the grade table" << endl;
  cout << "stats:                      Prints statistics about the hash table at this point" << endl;
  cout << "help:                       Prints a list of available commands" << endl;
  cout << "quit:                       Quits the program" << endl;

}
void insert(Table* grades){
  string name="";
  cin >> name;
  if(cin.fail()){
    cout<<"ERROR: Missing arguments!" << endl;
    return;
  }
  int value = 0;
  cin >> value;
  if(!cin.fail()){
    bool insert = grades->insert(name,value);
    if(insert ==false){
      cout <<"Student " << name << " is already present. No changes" << endl;
    }
  }else{
    cout<<"ERROR: Missing arguments!" << endl;
  }
}
void change(Table* grades){
  string name="";
  cin >> name;
  if(cin.fail()){
    cout << "ERROR: Missing arguments!" << endl;
    return;
  }
  int value = 0;
  cin >> value;
  if(!cin.fail()){
    int *oldScore = grades->lookup(name);
    if(oldScore == NULL){
      cout << "Student " << name << " is not present. No changes" << endl;
    }else{
      *oldScore = value;
    }
  }else{
    cout<<"ERROR: Missing arguments!" << endl;
  }
}
void lookup(Table* grades){
  string name="";
  cin >> name;
  if(!cin.fail()){
    int *score = grades->lookup(name);
    if(score == NULL){
      cout << "Student " << name << " is not present." << endl;
    }else{
      cout << name <<"'s score: " << *score << endl;
    }
  }else{
    cout<<"ERROR: Missing arguments!" << endl;
  }
}
void removeL(Table* grades){
  string name="";
  cin >> name;
  if(!cin.fail()){
    bool remove = grades->remove(name);
    if(remove == false){
      cout << "Student " << name << " is not present. No changes" << endl;
    }
  }else{
    cout<<"ERROR: Missing arguments!" << endl;
  }
}

int main(int argc, char * argv[]) {

  // gets the hash table size from the command line
  
  int hashSize = Table::HASH_SIZE;

  Table * grades;  // Table is dynamically allocated below, so we can call
                   // different constructors depending on input from the user.

  if (argc > 1) {
    hashSize = atoi(argv[1]);  // atoi converts c-string to int

    if (hashSize < 1) {
      cout << "Command line argument (hashSize) must be a positive number" << endl;
      return 1;
    }

    grades = new Table(hashSize);

  }
  else {   // no command line args given -- use default table size
    grades = new Table();
  }

  cout << "% grades " << hashSize << endl;
  grades->hashStats(cout);

  // add more code here
  // Reminder: use -> when calling Table methods, since grades is type Table*
 
  string command;
  cout << "cmd> ";
  cin >> command;
  while(command != "quit"){
    if(command == "help"){
      help();
    }else if (command == "insert"){
      insert(grades);

    }else if (command == "change"){
      change(grades);
    }else if (command == "lookup"){
      lookup(grades);
    }else if (command == "remove"){
      removeL(grades);
    }else if (command == "print"){
      cout << "Grade table entries: " << endl;
      grades->printAll();
    }else if (command == "size"){
      cout << "Size of grade table: " << grades->numEntries() << endl;
    }else if (command == "stats"){
      cout << "% grades " << hashSize << endl;
      grades->hashStats(cout);
    }else{
      cout << "ERROR: invalid command." << endl;
      help();
    }
    cout << "cmd> ";
    cin >> command;
  }

  return 0;
}
