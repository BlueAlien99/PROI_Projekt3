#include "../include/IOHandler.h"

#include "../include/Interface.h"
#include "../include/Quiz.h"

#include <algorithm>
#include <climits>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

void IOHandler::cleanup(){
	remove("problems.txt");
	remove("solutions.txt");
	remove("solutions_visualised.txt");
	remove("scoreboard.txt");
	cout<<endl<<"Done!"<<endl;
}

void IOHandler::genProblemsTxt(){
	ofstream file("problems.txt");
	if(!file.is_open()){
		cout<<endl<<"This should NOT have happened! (IOHandler::genProblemsTxt)";
		return;
	}
	file<<"# Each config must be entered in a new line"<<endl;
	file<<"# Lines starting with '#' will be omitted"<<endl;
	file<<"# All numbers must be non-negative integers"<<endl;
	file<<"# Following info is required (separated by space):"<<endl;
	file<<"# Width Height Pawns Rooks Bishops Queens Knights Kings"<<endl;
	file<<"# W H P R B Q N K"<<endl;
	file<<endl;
	file.close();
}

void IOHandler::solveProblems(bool brute){
	ifstream file("problems.txt");
	if(!file.is_open()){
		cout<<endl<<"Could not find \"problems.txt\"..."<<endl;
		return;
	}
	string line;
	while(!file.eof()){
		getline(file, line);
		if(line[0] == '#' || line.size() == 0){
			continue;
		}
		bool error = 0;
		int data[8] = {0};
		size_t pos = 0;
		for(int i = 0; i < 8; ++i){
			size_t p;
			try{
				if(pos < line.size()){
					data[i] = stoi(line.substr(pos), &p, 10);
				}
			} catch(...){
				error = 1;
				break;
			}
			if(data[i] < 0){
				error = 1;
				break;
			}
			pos += p;
		}
		if(!error){
			Interface board(data[0], data[1], data[2], data[3],
							data[4], data[5], data[6], data[7]);
			cout<<board.getConfigStr();
			if(brute){
				board.algorithm(1, 1);
			} else{
				board.algorithm(0, 1);
			}
		}
	}
	file.close();
}

void IOHandler::findSolution(string config, vector<int> *board){
	bool found = 0;
	ifstream file("solutions.txt");
	if(!file.is_open()){
		string str = "ERROR: Could not open file!";
		throw str;
	}
	string line;
	while(!file.eof()){
		getline(file, line);
		if(config == line && !file.eof()){
			found = 1;
			getline(file, line);
			break;
		}
	}
	if(found && line.size() && line[0] == '}'){
		throw 100;
	}
	size_t dim;
	int x = stoi(config, &dim, 10);
	int y = stoi(config.substr(dim), nullptr, 10);
	size_t pos = 0;
	for(int i = 0; i < x*y; ++i){
		size_t p;
		try{
			if(pos < line.size()){
				board->push_back(stoi(line.substr(pos), &p, 10));
			} else{
				throw 404;
			}
		} catch(...){
			throw 404;
		}
		pos += p;
	}
	file.close();
}

void IOHandler::saveSolution(bool result, std::string config, std::string board){
	bool input = 1;
	bool found = 0;
	ifstream fileIn("solutions.txt");
	if(!fileIn.is_open()){
		input = 0;
	}
	ofstream fileOut("IOHandler.temp", ios::trunc);
	if(!fileOut.is_open()){
		cout<<endl<<"This should NOT have happened! (IOHandler::saveSolution)";
		return;
	}
	if(input){
		string line;
		while(!fileIn.eof()){
			getline(fileIn, line);
			fileOut<<line;
			if(!fileIn.eof()){
				fileOut<<endl;
			}
			if(config == line && !fileIn.eof()){
				found = 1;
				getline(fileIn, line);
				if(result){
					fileOut<<board<<endl;
				}
				if(line.size() == 0 || line[0] == '}'){
					fileOut<<'}'<<endl;
				} else if(line.size() && line[0] == '{'){
					fileOut<<'}'<<endl;
					fileOut<<'{'<<endl;
				}
			}
		}
		fileIn.close();
	}
	if(!found){
		fileOut<<endl;
		fileOut<<'{'<<endl;
		fileOut<<config<<endl;
		if(result){
			fileOut<<board<<endl;
		}
		fileOut<<'}';
	}
	fileOut.close();
	remove("solutions.txt");
	rename("IOHandler.temp", "solutions.txt");
}

void IOHandler::exportVisualised(bool result, string config, string board){
	ofstream file("solutions_visualised.txt", ios::app);
	if(!file.is_open()){
		cout<<endl<<"This should NOT have happened! (IOHandler::exportVisualised)";
		return;
	}
	file<<"**** SOLUTION ****"<<endl;
	time_t t = time(nullptr);
	file<<put_time(localtime(&t), "%Y-%m-%d %H:%M:%S")<<endl;
	file<<config;
	if(!result){
		file<<endl<<"Placement impossible!"<<endl;
	} else{
		file<<board;
	}
	file<<endl<<"**** ######## ****"<<endl;
	file<<endl<<endl;
	file.close();
}

void IOHandler::saveQuizScore(string name, uint correct, uint total,
												int time, int score){
	ofstream file("scoreboard.txt", ios::app);
	if(!file.is_open()){
		cout<<endl<<"This should NOT have happened! (IOHandler::saveQuizScore)";
		return;
	}
	if(name.size()){
		file<<"{"<<endl;
		file<<"Name="<<name<<";"<<endl;
		file<<"Correct="<<correct<<";"<<endl;
		file<<"Total="<<total<<";"<<endl;
		file<<"Time="<<time<<";"<<endl;
		file<<"Score="<<score<<";"<<endl;
		file<<"}"<<endl;
		file<<endl;
	}
}

void IOHandler::printScoreboard(){
	ifstream file("scoreboard.txt");
	if(!file.is_open()){
		cout<<endl<<"No records to display!"<<endl;
		return;
	}
	vector<struct Player*> players;
	while(!file.eof()){
		struct Player *player = new struct Player();
		if(importPlayerStats(player, &file)){
			players.push_back(player);
		} else{
			delete player;
		}
	}
	file.close();
	sort(players.begin(), players.end(), PtrCmp());
	if(players.size()){
		system("clear");
		cout<<endl;
		cout<<setw(4)<<"##"<<setw(18)<<"Player name"<<setw(10)<<"Correct";
		cout<<setw(10)<<"Time"<<setw(10)<<"Score"<<endl<<endl;
	} else{
		cout<<endl<<"No records to display!";
	}
	for(uint i = 0; i < players.size(); ++i){
		cout<<setw(4)<<i+1<<setw(18)<<players[i]->name.substr(0, 16);
		string ques = to_string(players[i]->correctQues);
		ques += " / " + to_string(players[i]->totalQues);
		cout<<setw(10)<<ques;
		cout<<setw(10)<<fixed<<setprecision(2)<<players[i]->time/(double)1000;
		cout<<setw(10)<<players[i]->score<<endl;
		delete players[i];
	}
	cout<<endl;
}

bool IOHandler::importPlayerStats(struct Player *player, ifstream *file){
	string line;
	getline(*file, line);
	if(line[0] != '{'){
		return 0;
	}
	getline(*file, line);
	player->name = extractString("Name", line);
	if(player->name == ""){
		return 0;
	}
	getline(*file, line);
	player->correctQues = extractUint("Correct", line);
	if(player->correctQues == INT_MAX){
		return 0;
	}
	getline(*file, line);
	player->totalQues = extractUint("Total", line);
	if(player->totalQues == INT_MAX){
		return 0;
	}
	getline(*file, line);
	player->time = extractUint("Time", line);
	if(player->time == INT_MAX){
		return 0;
	}
	getline(*file, line);
	player->score = extractUint("Score", line);
	if(player->score == INT_MAX){
		return 0;
	}
	getline(*file, line);
	if(line[0] != '}'){
		return 0;
	}
	return 1;
}

string IOHandler::extractString(string key, string data){
	string ret = "";
	if(data.size() && key == data.substr(0, key.size())){
		size_t beg = data.find("=");
		size_t end = data.find(";");
		if(beg != string::npos && end != string::npos && end-beg > 1){
			ret = data.substr(beg+1, (end-beg)-1);
		}
	}
	return ret;
}

uint IOHandler::extractUint(string key, string data){
	string str = extractString(key, data);
	int ret = -1;
	try{
		ret = stoi(str);
	} catch(...){
		ret = INT_MAX;
	}
	if(ret < 0){
		ret = INT_MAX;
	}
	return ret;
}
