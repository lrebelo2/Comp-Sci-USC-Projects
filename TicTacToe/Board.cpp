#include "Board.h"

Board::Board()
{
	board = new vector< vector<char> >(3,vector<char>(3,'-'));
	
}
Board::Board(const Board &b){
	board = new vector< vector<char> >(3,vector<char>(3,'-'));
	
}
Board::~Board(){
	
}
void Board::play(){
	this->print(cout);
	//determine who starts
	this->action(true);

}
void Board::action(bool player){
	if(player){
		pair<int,int> pAction=getPlayerAction();
		(*board)[pAction.first][pAction.second]='X';
		print(cout);
		if(checkWin(pAction.first,pAction.second,'X')){
			cout <<"Congratulations! You won the game!!!\n You don't suck.\n";
			return;
		}else if(checkTie()){
			cout<<"It's a tie! Better luck next time!\n";
			return;
		}else{
			action(!player);
		}
	}else{
		cout<<"\nMaking my move...\n";
		tuple< int,pair<int,int> > ai=minimax(*board,-100,100,true,-1,-1);
		pair<int,int> aiAction=get<1>(ai);
		cout<<get<0>(ai)<<'\n';
		if (aiAction.first != -1){
			cout<<aiAction.first<<" , "<<aiAction.second<<'\n';
			(*board)[aiAction.first][aiAction.second]='O';
			print(cout);
			if(checkWin(aiAction.first,aiAction.second,'O')){
				cout <<"You lost...";
				return;
			}
			action(!player);
		}else if(checkTie()){
			cout<<"It's a tie! Better luck next time!\n";
			return;
		}else{
			action(!player);
		}
		
	}
}
void Board::print(ostream &stream){
	vector< vector<char> >::iterator it1;
	vector<char>::iterator it2;
	int i=0;
	stream<<"\n\n";
	stream<<"\t  A B C";
	for(it1=board->begin();it1!=board->end();++it1){
		stream<<"\n\t"<<i + 1;
		for(it2=it1->begin();it2!=it1->end();++it2){
			stream<<"|"<<*it2;
		}
		stream<<"|";
		i++;
	}
    stream<<"\n\n";
}
set< pair<int,int> > Board::actions(vector< vector<char> > &board){
	set< pair<int,int> > acts;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]=='-'){
				acts.insert(pair<int,int>(i,j));
			}
		}
	}
	return acts;
}
int Board::evaluate(vector< vector<char> > &b)
{
	char player='O';
	char opponent='X';
 
    for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==player)
                return +10;
            else if (b[row][0]==opponent)
                return -10;
        }
    }
 

    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==player)
                return +10;
 
            else if (b[0][col]==opponent)
                return -10;
        }
    }
 
    
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==player)
            return +10;
        else if (b[0][0]==opponent)
            return -10;
    }
 
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==player)
            return +10;
        else if (b[0][2]==opponent)
            return -10;
    }
    return 0;
}


tuple< int,pair<int,int> > Board::minimax(vector< vector<char> > b,int alpha,int beta, bool turn,int i, int j){
	
	tuple< int,pair<int,int> > r;
	set< pair<int,int> > acts= actions(b);
	if(acts.empty()) {
		int e=evaluate(b);
		if(e==10) return tuple<int,pair<int,int> >(e,pair<int,int>(i,j));
		else if(e==-10) return tuple<int,pair<int,int> >(e,pair<int,int>(i,j));
		else return tuple<int,pair<int,int> >(0,pair<int,int>(i,j));
	}
	if(turn){
		int v=-100;
		for(auto& x: acts){
				b[x.first][x.second]='O';
				tuple< int,pair<int,int> > newNode = minimax(b,alpha,beta,!turn,x.first,x.second);
				int ns=get<0>(newNode);
				if (v < ns){
					v = ns;
					r = newNode;
				}
				alpha=max(alpha,v);
				if (beta <= alpha){
					return r;
				}
				
		}
		return r;
	}else{
		int v=100;
		for(auto& x: acts){
				b[x.first][x.second]='X';
				tuple< int,pair<int,int> > newNode = minimax(b,alpha,beta,!turn,x.first,x.second);
				int ns=get<0>(newNode);
				if (ns < v){
					v = ns;
					r = newNode;
				}
				beta = min(beta,v);
				if (beta <= alpha){
					return r;
				}
		}
		return r;
	}
	
}


bool Board::checkWin(int row,int col,char c){
	//since the board is always of size 3, let's simplify a bit with some ugly code (not representative):
	auto bRef=*board;
	if(bRef[row][0]==c && bRef[row][1]==c && bRef[row][2]==c) return true;
	else if(bRef[0][col]==c && bRef[1][col]==c && bRef[2][col]==c) return true;
	else if(!(row+col==1 || row+col==3)){
		if(bRef[0][0]==c && bRef[1][1]==c && bRef[2][2]==c)return true;
		else if (bRef[2][0]==c && bRef[1][1]==c && bRef[0][2]==c)return true;
	}
	return false;
}

bool Board::checkWin(vector< vector<char> > &bRef,int row,int col,char c){
	
	if(bRef[row][0]==c && bRef[row][1]==c && bRef[row][2]==c) return true;
	else if(bRef[0][col]==c && bRef[1][col]==c && bRef[2][col]==c) return true;
	else if(!(row+col==1 || row+col==3)){
		if(bRef[0][0]==c && bRef[1][1]==c && bRef[2][2]==c)return true;
		else if (bRef[2][0]==c && bRef[1][1]==c && bRef[0][2]==c)return true;
	}
	return false;
	
}
pair<int,int> Board::getPlayerAction(){
	string raw;
	char colChar;
	int row,col;
	bool fail=true;
	do{
		cout<<"Choose a spot. Examples: A1, B3, etc.."<<endl;
		
		cin>>raw;
		//match raw to regex[abcABC][0-2]
		if(regex_match(raw,regex("[abcABC][1-3]"))){
			colChar=raw[0];
			row=raw[1]-49;
		
			if(colChar=='a' || colChar== 'A'){
				col=0;
			}
			else if(colChar=='b' || colChar== 'B'){
				col=1;
			}
			else if(colChar=='c' || colChar== 'C'){
				col=2;
			}
			if((*board)[row][col]!='-'){
				cout<<"Invalid action!\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		    }else fail=false;	
			
		}else{
			cout<<"Invalid action!\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}while(fail);
	return pair<int,int>(row,col);
}

bool Board::checkTie(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if((*board)[i][j]=='-') return false;
		}
	}
	return true;
}
