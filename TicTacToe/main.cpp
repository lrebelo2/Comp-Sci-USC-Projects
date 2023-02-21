

#include "main.h"


int main()
{
	
	int command;
	cout<<"Hello! Welcome to Tic-Tac-Toe!"<<std::endl;
	command=getCommand();
	while (command!=0){
		Board gameBoard;
		gameBoard.play();
		command=getCommand();
	}
	cout<<"\n\nGood-bye!!!"<<"\n\n";
	getchar();
	return 0;
}
