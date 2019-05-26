#include <../include/Quiz.h>

#include <../include/IOHandler.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

#define QUIZ_LENGTH 8
#define BASE_POINTS 1000
#define BASE_TIME 10000

using namespace std;

bool PtrCmp::operator()(const Player *p1, const Player *p2){
	if(p1->score != p2->score){
		return p1->score > p2->score;
	} else{
		return p1->time < p2->time;
	}
}

void Quiz::run(){
	system("clear");
	cout<<endl;
	cout<<"----  RULES  ----"<<endl;
	cout<<endl;
	cout<<"- Answers must be in lower case"<<endl;
	cout<<"- English articles (a, an, the) must be omitted"<<endl;
	cout<<endl;
	cout<<"Press enter to start..."<<endl;
	string xd;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, xd);
	vector<pair<string, string> > ques;
	generator(&ques);
	uint quesCount = ques.size();
	struct Player player(quesCount);
	string ans = "";
	int dur = 0;
	while(!ques.empty()){
		system("clear");
		cout<<endl;
		cout<<ans<<endl;
		cout<<dur/(double)1000<<" sec"<<endl;
		cout<<endl;
		cout<<"Question "<<quesCount-ques.size()+1<<" of "<<quesCount<<endl;
		cout<<endl;
		auto begin = chrono::steady_clock::now();
		bool ok = question(ques[0].first, ques[0].second);
		auto end = chrono::steady_clock::now();
		dur = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		player.time += dur;
		if(ok){
			ans += "1";
			player.correctQues++;
			int pts = BASE_POINTS * (BASE_TIME - dur) * (8 / (double)quesCount);
			player.score += max(0, pts) / 1000;
		} else{
			ans += "0";
		}
		ques.erase(ques.begin());
	}
	system("clear");
	cout<<endl;
	cout<<ans<<endl;
	cout<<dur/(double)1000<<" sec"<<endl;
	cout<<endl;
	cout<<"----  SUMMARY  ----"<<endl;
	cout<<endl;
	string cor = to_string(player.correctQues) + " / " + to_string(player.totalQues);
	cout<<setw(12)<<"Correct: "<<setw(6)<<cor<<endl;
	cout<<setw(12)<<"Time: "<<setw(6)<<player.time/(double)1000<<" sec"<<endl;
	cout<<setw(12)<<"Score: "<<setw(6)<<player.score<<" pts"<<endl;
	cout<<endl;
	cout<<"What's your name? (max 16 chars)"<<endl;
	string name;
	getline(cin, name);
	player.name = name.substr(0, 16);
	IOHandler::saveQuizScore(player.name, player.correctQues, player.totalQues,
												player.time, player.score);
	cout<<endl<<"Press enter to continue..."<<endl;
	getline(cin, xd);
}

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
	getline(cin, str);
	if(str == a){
		return 1;
	} else{
		return 0;
	}
}
