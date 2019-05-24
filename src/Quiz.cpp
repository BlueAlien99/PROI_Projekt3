#include <../include/Quiz.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#define QUIZ_LENGTH 8

using namespace std;

void Quiz::generator(vector<pair<string, string> > *ques){
	vector<pair<string, string> > bank;

	string movement = "\n\nEnter a sum of allowed moves' values:";
	movement += "\n1 - vertically\n2 - horizontally\n4 - diagonally";
	movement += "\n8 - jumping over";

	string q1 = "Which color moves first?";
	string a1 = "white";
	bank.push_back(make_pair(q1, a1));

	string q2 = "Which piece attacks differently than it moves?";
	string a2 = "pawn";
	bank.push_back(make_pair(q2, a2));

	string q3 = "How does rook move?";
	q3 += movement;
	string a3 = "3";
	bank.push_back(make_pair(q3, a3));

	string q4 = "How does knight move?";
	q4 += movement;
	string a4 = "8";
	bank.push_back(make_pair(q4, a4));

	string q5 = "How does bishop move?";
	q5 += movement;
	string a5 = "4";
	bank.push_back(make_pair(q5, a5));

	string q6 = "How does queen move?";
	q6 += movement;
	string a6 = "7";
	bank.push_back(make_pair(q6, a6));

	string q7 = "Can a pawn be promoted to any piece?";
	string a7 = "no";
	bank.push_back(make_pair(q7, a7));

	string q8 = "Which piece should be always covered?";
	string a8 = "king";
	bank.push_back(make_pair(q8, a8));

	string q9 = "Name a situation when the king can be attacked";
	q9 += "\nbut the player can still make a move...";
	string a9 = "check";
	bank.push_back(make_pair(q9, a9));

	string q10 = "Name a situation when the king can be attacked";
	q10 += "\nbut the player cannot make any legal move...";
	string a10 = "checkmate";
	bank.push_back(make_pair(q10, a10));

	string q11 = "Name a situation when the king CANNOT be attacked";
	q11 += "\nand the player cannot make any legal move...";
	string a11 = "stalemate";
	bank.push_back(make_pair(q11, a11));

	string q12 = "In other words: a tie || a draw...";
	string a12 = "stalemate";
	bank.push_back(make_pair(q12, a12));

	string q13 = "A situation which ends the game && there is a winner...";
	string a13 = "checkmate";
	bank.push_back(make_pair(q13, a13));

	string q14 = "Special move for pawns attacking pawns...";
	string a14 = "en passant";
	bank.push_back(make_pair(q14, a14));

	string q15 = "The only move that allows two pieces to move...";
	string a15 = "castling";
	bank.push_back(make_pair(q15, a15));

	string q16 = "What are the dimensions of a chess board? (AxB)";
	string a16 = "8x8";
	bank.push_back(make_pair(q16, a16));

	uint quizLen = min(QUIZ_LENGTH, (int)bank.size());
	while(quizLen){
		uint q = rand() % bank.size();
		ques->push_back(bank[q]);
		bank.erase(bank.begin()+q);
		--quizLen;
	}
}

bool Quiz::question(string q, string a){
	cout<<q<<endl;
	cout<<endl;
	string str;
	cin>>str;
	if(str == a){
		return 1;
	} else{
		return 0;
	}
}
