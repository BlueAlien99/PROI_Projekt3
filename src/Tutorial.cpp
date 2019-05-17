#include "../include/Tutorial.h"

#include <iostream>
#include <limits>

using namespace std;

void Tutorial::run(){
	void (*fun[])() = {page_zero, setup, pawn, rook, knight, bishop, queen,
					king, check, checkmate, stalemate, castling, enpassant};
	int pages = (sizeof(fun)/sizeof(fun[0]))-1;
	int i = 0;
	while(i >= 0 && i <= pages){
		system("clear");
		cout<<"Page "<<i<<" out of "<<pages<<endl;
		cout<<endl;
		(*fun[i])();
		cout<<endl;
		char c;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get(c);
		if(c == 'q'){
			break;
		} else if(c == 'n'){
			++i;
		} else if(c == 'p'){
			--i;
		}
	}
}

void Tutorial::page_zero(){
	cout<<"This tutorial is based on:"<<endl;
	cout<<"https://www.instructables.com/id/Playing-Chess/"<<endl;
	cout<<endl;
	cout<<"Navigation:"<<endl;
	cout<<"n - next page"<<endl;
	cout<<"p - previous page"<<endl;
	cout<<"q - quit"<<endl;
}

void Tutorial::setup(){
	cout<<"  Board setup"<<endl;
	cout<<endl;
	cout<<"  r n b q k b n r"<<endl;
	cout<<"  p p p p p p p p"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  P P P P P P P P"<<endl;
	cout<<"  R N B Q K B N R"<<endl;
	cout<<endl;
	cout<<"- White always moves first"<<endl;
	cout<<"- Players can only move one piece at a time"<<endl;
	cout<<"- Only pawns attack differently than they move"<<endl;
	cout<<"- Pieces cannot move through other pieces (except for knights)"<<endl;
}

void Tutorial::pawn(){
	cout<<"  Pawn"<<endl;
	cout<<endl;
	cout<<"  First move"<<endl;
	cout<<endl;
	cout<<"  - - x - -"<<endl;
	cout<<"  - - x - -"<<endl;
	cout<<"  - - P - -"<<endl;
	cout<<"  - - - - -"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"  All other moves"<<endl;
	cout<<endl;
	cout<<"  - - - - -"<<endl;
	cout<<"  - - x - -"<<endl;
	cout<<"  - - P - -"<<endl;
	cout<<"  - - - - -"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"  Attack"<<endl;
	cout<<endl;
	cout<<"  - - - - -"<<endl;
	cout<<"  - x - x -"<<endl;
	cout<<"  - - P - -"<<endl;
	cout<<"  - - - - -"<<endl;
	cout<<endl;
	cout<<"- Once a pawn reaches the opposite side,"<<endl;
	cout<<"  it is promoted to a higher piece (except for king)"<<endl;
}

void Tutorial::rook(){
	cout<<"  Rook"<<endl;
	cout<<endl;
	cout<<"  Movement and attack"<<endl;
	cout<<endl;
	cout<<"  - - x - -"<<endl;
	cout<<"  - - x - -"<<endl;
	cout<<"  x x R x x"<<endl;
	cout<<"  - - x - -"<<endl;
	cout<<"  - - x - -"<<endl;
}

void Tutorial::knight(){
	cout<<"  Knight"<<endl;
	cout<<endl;
	cout<<"  Movement and attack"<<endl;
	cout<<endl;
	cout<<"  - x - x -"<<endl;
	cout<<"  x - - - x"<<endl;
	cout<<"  - - N - -"<<endl;
	cout<<"  x - - - x"<<endl;
	cout<<"  - x - x -"<<endl;
}

void Tutorial::bishop(){
	cout<<"  Bishop"<<endl;
	cout<<endl;
	cout<<"  Movement and attack"<<endl;
	cout<<endl;
	cout<<"  x - - - x"<<endl;
	cout<<"  - x - x -"<<endl;
	cout<<"  - - B - -"<<endl;
	cout<<"  - x - x -"<<endl;
	cout<<"  x - - - x"<<endl;
}

void Tutorial::queen(){
	cout<<"  Queen"<<endl;
	cout<<endl;
	cout<<"  Movement and attack"<<endl;
	cout<<endl;
	cout<<"  x - - x - - x"<<endl;
	cout<<"  - x - x - x -"<<endl;
	cout<<"  - - x x x - -"<<endl;
	cout<<"  x x x Q x x x"<<endl;
	cout<<"  - - x x x - -"<<endl;
	cout<<"  - x - x - x -"<<endl;
	cout<<"  x - - x - - x"<<endl;
}

void Tutorial::king(){
	cout<<"  King"<<endl;
	cout<<endl;
	cout<<"  Movement and attack"<<endl;
	cout<<endl;
	cout<<"  - - - - -"<<endl;
	cout<<"  - x x x -"<<endl;
	cout<<"  - x K x -"<<endl;
	cout<<"  - x x x -"<<endl;
	cout<<"  - - - - -"<<endl;
	cout<<endl;
	cout<<"- King cannot move to a square that is under attack"<<endl;
}

void Tutorial::check(){
	cout<<"  Check"<<endl;
	cout<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - - - - q"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - K - - -"<<endl;
	cout<<endl;
	cout<<"- King is in check when it can be attacked"<<endl;
	cout<<"- In such situation player must:"<<endl;
	cout<<"  a) move their king out of check"<<endl;
	cout<<"  b) block the check"<<endl;
	cout<<"  c) capture the attacking piece"<<endl;
	cout<<"- Player cannot move their king into check"<<endl;
}

void Tutorial::checkmate(){
	cout<<"  Checkmate"<<endl;
	cout<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  P - - - - -"<<endl;
	cout<<"  K - - - - -"<<endl;
	cout<<"  - q - - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - n - - -"<<endl;
	cout<<endl;
	cout<<"- The only way to win the game"<<endl;
	cout<<"- King is in checkmate if it is in check,"<<endl;
	cout<<"  and nothing can be done to get out of it"<<endl;
}

void Tutorial::stalemate(){
	cout<<"  Stalemate"<<endl;
	cout<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - - - q -"<<endl;
	cout<<"  - - - - - p"<<endl;
	cout<<"  - - - - - K"<<endl;
	cout<<"  - - - - - P"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<endl;
	cout<<"- Uppercase's turn"<<endl;
	cout<<"- Stalemate is a tie"<<endl;
	cout<<"- Achieved if there are no legal moves to make,"<<endl;
	cout<<"  and the king is not in check"<<endl;
}

void Tutorial::castling(){
	cout<<"  Special move: Castling"<<endl;
	cout<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  R - - - K - - R"<<endl;
	cout<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  R - - - - R K -"<<endl;
	cout<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - - - - - - -"<<endl;
	cout<<"  - - K R - - - R"<<endl;
	cout<<endl;
	cout<<"- The only move that allows two pieces to move"<<endl;
	cout<<"- King moves two spaces towards the rook"<<endl;
	cout<<"  that it will castle with,"<<endl;
	cout<<"  and the rook jumps to the other side"<<endl;
}

void Tutorial::enpassant(){
	cout<<"  Special move: En Passant"<<endl;
	cout<<endl;
	cout<<"  p p p p p p"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - P - - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  P - P P P P"<<endl;
	cout<<endl;
	cout<<"  p p - p p p"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - P p - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  P - P P P P"<<endl;
	cout<<endl;
	cout<<"  p p - p p p"<<endl;
	cout<<"  - - P - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  - - - - - -"<<endl;
	cout<<"  P - P P P P"<<endl;
	cout<<endl;
	cout<<"- Only pawns attacking pawns"<<endl;
	cout<<"- Only if your opponent moves a pawn two spaces,"<<endl;
	cout<<"  and its destination space is next to your pawn"<<endl;
}
