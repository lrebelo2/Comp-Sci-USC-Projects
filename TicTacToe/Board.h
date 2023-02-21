#ifndef BOARD_H
#define BOARD_H


#include "main.h"

class Board{

	vector< vector<char> > *board;

public:
	Board();
	Board(const Board &b);
	~Board();
	void play();
private:
	void print(ostream &stream);
	void action(bool player);
	tuple< int,pair<int,int> >  minimax(vector< vector<char> > b, int a, int c, bool max,int i, int j);
	bool checkWin(int row,int col,char c);
	bool checkWin(vector< vector<char> > &b,int row,int col,char c);
	pair<int,int> getPlayerAction();
	bool checkTie();
	int evaluate(vector< vector<char> > &b);
	set< pair<int,int> > actions(vector< vector<char> > &board);
};



#endif // BOARD_H
