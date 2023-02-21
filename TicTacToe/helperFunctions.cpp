
 
#include "main.h"


void displayMenu(){
	cout<<"\nMenu:    1: Play!"<<endl;
	cout<<"         0: End Session"<<endl;
}

int getCommand(){
	int command=-1;
	do{
		
		displayMenu();
		cin>>command;
		if(cin.fail()){
			cout<<"Invalid command.\n\n";
			cin.clear(); // reset failbit
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if(command==1 || command==0){
			return command;
		}
		else{
			cout<<"Invalid command.\n\n";
		}
	}while(true);
	return command;
}

